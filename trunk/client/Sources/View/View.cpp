#include "View.h"

View * View::GetInstance()
{
	static View * _instance = new View();

	return _instance;
}

View::View() 
{
	// Inicjalizacja loggera.
	_logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("View"));
	_logger->setLevel(LOGLEVEL);

	// Zerowanie niektorych skladowych.
	_information.inMsgCount		= 0;
	_information.connected		= false;
}

View::~View() 
{
	// Usuniecie okien.
	for(std::list<Window *>::iterator i = _windows.begin(); i != _windows.end(); i++)
		delete *i;

	// Usuniecie rozmow.
	for(std::map<std::string, std::list<MYMESSAGE> *>::iterator i = _talks.begin(); i != _talks.end(); i++)
		delete (*i).second;

	// Usuniecie mutexow.
	for(std::map<std::string, boost::mutex *>::iterator i = _mxsTalks.begin(); i != _mxsTalks.end(); i++)
		delete (*i).second;
}

void View::Run()
{
	// Komenda.
	std::string cmd;
	// Aktualne okno.
	std::list<Window *>::iterator tmp;
	// Podreczna lista okien.
	std::list<Window *> tmpWindows;

	// Stworzenie powitalnego okna i ustawienie go jako aktywnego.
	SetActiveWindow(AddWindow(new WelcomeWindow(_controller)));

	int p = 0;
	// Petla pobierania instrukcji od uzytkownika.
	while(true)
	{
		// Czyszczenie ekranu.
		p = system(CLSCMD);

		// Czyszczenie ostatniej komendy.
		cmd.clear();

		// Renderowanie okna konfiguracji.
		(*GetActiveWindow())->Render(std::cout);

		// Pobranie instrukcji.
		std::cin >> cmd;

		// Zmiana okna.
		if (!cmd.compare(CHANGE_WINDOW))
		{
			ChangeActiveWindow();
		}
		// Wyjscie z aplikacji.
		else if (!cmd.compare(EXIT_APP))
		{
			if ( _information.connected )
			{
				LOG4CXX_DEBUG(this->_logger, "Rozlaczanie przy wyjsciu z aplikacji...");
				int result = this->GetController()->Disconnect();
				LOG4CXX_DEBUG(this->_logger, "Rezultat rozlaczania przy wyjsciu z aplikacji: " << result);
			}

			// TODO: Wywo³anie czegos na kontrolerze.
			LOG4CXX_DEBUG(this->_logger, "Uzytkownik zakonczyl program.");

			break;
		}
		// Otwarcie nowego okna.
		else if (!cmd.compare(OPEN_WINDOW))
		{
			cmd.clear();
			std::cin >> cmd;

			// Okno powitalne.
			if (!cmd.compare(WIN_WELCOME))
			{
				SetActiveWindow(AddWindow(new WelcomeWindow(_controller)));
			}
			// Okno pomocy.
			else if (!cmd.compare(WIN_HELP))
			{
				SetActiveWindow(AddWindow(new HelpWindow(_controller)));
			}
			// Okno konfiguracji.
			else if (!cmd.compare(WIN_CONF))
			{
				SetActiveWindow(AddWindow(new ConfigWindow(_controller, &_information)));
			}
			// Okno kontaktow.
			else if (!cmd.compare(WIN_CONTACT))
			{
				SetActiveWindow(AddWindow(new ContactWindow(_controller)));
			}
			// Okno rozmowy.
			else if (!cmd.compare(WIN_MSG))
			{
				cmd.clear();

				// Pobrana nazwa uzytkownika z listy kontaktow.
				std::cin >> cmd;

				this->_mxCreateTalks.lock();

					// Pobranie wszystkich okien.
					tmpWindows = GetAllWindows();

					// Sprawdzenie czy nie otwarto juz okna do tej rozmowy.
					for(tmp = tmpWindows.begin(); tmp != tmpWindows.end(); tmp++)
						if ( (*tmp)->GetName().find(cmd, 0) != string::npos )
							break;
					
					// Nie znaleziono takiej rozmowy/
					if ( tmp == tmpWindows.end() )
					{
						// Stworzenie okna.
						MsgWindow * msgWin = new MsgWindow(_controller, cmd);

						// Jesli nie istniala rozmowa.
						if ( _talks.find(cmd) == _talks.end() )
						{
							_talks[cmd]	= new std::list<MYMESSAGE>();
							_mxsTalks[cmd] = new boost::mutex();
						}

						msgWin->SetTalk(_talks[cmd]);
						msgWin->SetMutexTalk(_mxsTalks[cmd]);

						SetActiveWindow(AddWindow(msgWin));
					}
					// Znaleziono taka rozmowe.
					else
					{
						// Otwarcie tego okna.
						SetActiveWindow(tmp);
					}

				this->_mxCreateTalks.unlock();
			}
			// Nie ma takiego okna.
			else
				(*GetActiveWindow())->SetMsg(ER_WIN_NO_WIN);
		}
		// Zamykanie okna.
		else if (!cmd.compare(CLOSE_WINDOW))
		{
			// Jesli jest to ostatnie okno.
			if ( this->_windows.size() == 1 )
				(*GetActiveWindow())->SetMsg(ER_WIN_LAST_WIN);
			else
			{
				tmp = GetActiveWindow();

				// Ustawienie nowego aktywnego okna.
				ChangeActiveWindow();

				//Zwolnenie pamieci.
				delete *tmp;

				// Usuniecie z listy okien.
				DelWindow(tmp);
			}
		}
		// Lista okien
		else if (!cmd.compare(LIST_WIN))
		{
			std::string windows("Otwarte okna: ");

			tmpWindows = GetAllWindows();

			for(tmp = tmpWindows.begin(); tmp != tmpWindows.end(); tmp++)
			{
				windows.append("[");

				if ( *tmp == *(GetActiveWindow()) )
					windows.append("!");

				windows.append((*tmp)->GetName());
				windows.append("]");
			}

			(*GetActiveWindow())->SetMsg(windows);
		}
		// Podlaczenie sie do serwera.
		else if (!cmd.compare(CONNECT))
		{
			if ( _information.connected )
				(*GetActiveWindow())->SetMsg(ER_CONN_IS_CONN);
			else if ( this->GetController()->GetServerAddress() == NULL )
				(*GetActiveWindow())->SetMsg(ER_CONN_NO_SERVE);
			else if ( this->GetController()->GetOwnName().empty() )
				(*GetActiveWindow())->SetMsg(ER_CONN_NO_UNAME);
			else
			{
				// Mamy wszystkie parametry do podlaczenia.

				std::cout << PROMPT << INFO_CONN_STILL << _controller->GetServerAddress();

				LOG4CXX_DEBUG(this->_logger, "Podlaczanie do serwera...");

				// !!! Podlaczenie od serwera.
				bool result = _controller->ConnectToServer();

				LOG4CXX_DEBUG(this->_logger, "Rezultat podlaczenie do serwera: " << result);

				// Nie udalo sie podlaczyc.
				if ( !result )
					(*GetActiveWindow())->SetMsg(ER_CONN_NO_CONN);
				else
				{
					_information.connected = true;
					_information.connectedDate = boost::posix_time::second_clock::local_time();

					(*GetActiveWindow())->SetMsg(INFO_CONN_CONN_OK);

					// Rejestracja obserwatorow.
					LOG4CXX_DEBUG(this->_logger, "Rejestracja obserwatorow!");

					_controller->AddRemoteObserver(new MessageObserver(this), MESSAGE);
					_controller->AddRemoteObserver(new FileObserver(this), FFILE);
					_controller->AddDataObserver(new StatusObserver(this));
				}
			}
		}
		// Odlaczanie
		else if (!cmd.compare(DISCONNECT))
		{
			if ( !_information.connected )
				(*GetActiveWindow())->SetMsg(ER_DCONN_NO_CONN);
			else
			{
				// Mozemy rozlaczac.

				std::cout << PROMPT << INFO_DCONN_STILL;

				LOG4CXX_DEBUG(this->_logger, "Odlaczanie od serwera...");

				// !!! Rozlaczenie sie od serwera.
				int result = _controller->Disconnect();

				LOG4CXX_DEBUG(this->_logger, "Rezultat odlaczania od serwera: " << result);

				// Nie udalo sie rozlaczyc.
				if ( result < 0 )
					(*GetActiveWindow())->SetMsg(ER_DCONN_CANT);
				else
				{
					_information.connected = false;
					
					(*GetActiveWindow())->SetMsg(INFO_DCONN_DCONN_OK);

					_information.connectedDate = boost::posix_time::ptime();
				}
			}
		}
		// Tymczasowa komenda
		else if (!cmd.compare("cc"))
		{
			std::cin >> cmd;

			LOG4CXX_DEBUG(this->_logger, "START - testowanie klienta");
			_controller->testClient(cmd);
			LOG4CXX_DEBUG(this->_logger, "END - testowanie klienta");

			(*GetActiveWindow())->SetMsg("Wywolano conntroller->testClient()!");
		}
		else
		{
			// Przekazanie komendy do okna.
			(*GetActiveWindow())->Command(cmd);
		}
	}
}

Controller * View::GetController() 
{
    return this->_controller;
}

void View::SetController(Controller * controller) 
{
	this->_controller = controller;
}

void View::SetActiveWindow(std::list<Window *>::iterator window)
{
	boost::mutex::scoped_lock sl(_mxActiveWindow);

	this->_activeWindow = window;
}

std::list<Window *>::iterator View::GetActiveWindow()
{
	boost::mutex::scoped_lock sl(_mxActiveWindow);

	return this->_activeWindow;
}

void View::ChangeActiveWindow()
{
	boost::mutex::scoped_lock sl(_mxActiveWindow);

	std::list<Window *>::iterator old = _activeWindow;

	// Zmiana okna.
	if ( ++_activeWindow == _windows.end() )
		this->_activeWindow = _windows.begin();

	// Przepisanie wiadomosci.
	if ( old != _activeWindow )
		if ( ! (*old)->GetMsg().empty() )
			(*_activeWindow)->SetMsg((*old)->GetMsg());
}

std::list<Window *>::iterator View::AddWindow(Window * window)
{
	boost::mutex::scoped_lock sl(_mxWindows);

	this->_windows.push_front(window);

	return this->_windows.begin();
}

bool View::DelWindow(std::list<Window *>::iterator window)
{
	boost::mutex::scoped_lock sl(_mxWindows);

	this->_windows.erase(window);

	return true;
}

std::list<Window *> View::GetAllWindows()
{
	boost::mutex::scoped_lock sl(_mxWindows);

	// Kopiuje aktualna liste okien.
	return this->_windows;
}

void View::Obsrv_ReciveMessage(const DomainData::User & senderAddress, const DomainData::Message & message)
{
	MYMESSAGE						msg;
	std::list<Window *>				tmpWindows;
	std::list<Window *>::iterator	tmp;
	std::list<MYMESSAGE>			* ptrTalk;
	MsgWindow						* msgWin;
	boost::mutex					* ptrMx;

	LOG4CXX_DEBUG(this->_logger, "Widok otrzymal wiadomosc. Adresat.Name: " << senderAddress.name.in() << " Message.Content: " << message.content.in() ); 

	if( senderAddress.name.in() == NULL )
	{
		LOG4CXX_ERROR(this->_logger, "NULL'owy adresat !" );
		return;
	}

	if( message.content.in() == NULL ) 
	{
		LOG4CXX_ERROR(this->_logger, "NULL'owa wiadomosc !" );
		return;
	}

	// Szukanie czy taka rozmowa sie odbywa.
	this->_mxCreateTalks.lock();

		// Pobranie wszystkich okien.
		tmpWindows = GetAllWindows();

		// Sprawdzenie czy nie otwarto juz okna do tej rozmowy.
		for(tmp = tmpWindows.begin(); tmp != tmpWindows.end(); tmp++)
			if ( (*tmp)->GetName().find(senderAddress.name.in(), 0) != string::npos )
				break;
		
		// Nie znaleziono takiego okna.
		if ( tmp == tmpWindows.end() )
		{
			LOG4CXX_DEBUG(this->_logger, "Nie znaleziono okna rozmowy." );
		
			// Stworzenie okna.
			msgWin = new MsgWindow(_controller, senderAddress.name.in());

			// Jesli nie istniala rozmowa.
			if ( _talks.find(senderAddress.name.in()) == _talks.end() )
			{
				LOG4CXX_DEBUG(this->_logger, "Nie znaleziono rozmowy. Stworzenie... " );

				_talks[senderAddress.name.in()]	= new std::list<MYMESSAGE>();
				_mxsTalks[senderAddress.name.in()] = new boost::mutex();
			}

			msgWin->SetTalk( ptrTalk = _talks[senderAddress.name.in()] );
			msgWin->SetMutexTalk( ptrMx = _mxsTalks[senderAddress.name.in()] );

			LOG4CXX_DEBUG(this->_logger, "Dodanie okna rozmowy." );

			AddWindow(msgWin);
		}
		// Znaleziono takie okno.
		else
		{
			LOG4CXX_DEBUG(this->_logger, "Znaleziono okno rozmowy." );

			// Musi istniec rozmowa.
			msgWin	= (MsgWindow *)(*tmp);
			ptrTalk = _talks[senderAddress.name.in()];
			ptrMx	= _mxsTalks[senderAddress.name.in()];
		}

	this->_mxCreateTalks.unlock();

	msg.content = message.content.in();
	msg.time	= boost::posix_time::second_clock::local_time();
	msg.sender	= senderAddress.name.in();

	// Dodanie wiadomosci do rozmowy.
	LOG4CXX_DEBUG(this->_logger, "Dodanie wiadomosci do rozmowy." );

	ptrMx->lock();
		ptrTalk->push_front(msg);
	ptrMx->unlock();

	// Zwiekszenie licznika otrzymanych wiadomosci.
	++_information.inMsgCount;

	// Otwarte jest okno rozmowy z gosciem ktory przyslal wiadomosc.
	if ( (*GetActiveWindow()) == msgWin )
	{
		LOG4CXX_DEBUG(this->_logger, "Aktualnie otwarte okno rozmowy. Odswiezamy." );
		
		int p = 0;
		// Czyszczenie ekranu.
		p = system(CLSCMD);

		// Odswiezamy okno.
		(*GetActiveWindow())->Render(std::cout);
	}
	// Otwarte jest inne okno.
	else
	{
		std::string shortMsg(INFO_GET_NEW_MSG);
		shortMsg.append(msg.sender);

		LOG4CXX_DEBUG(this->_logger, "Nie aktywne okno rozmowy. Ustawiamy powiadomienie." );

		// Ustawienie wiadomosci.
		(*GetActiveWindow())->SetMsg(shortMsg);
	}

	LOG4CXX_DEBUG(this->_logger, "Widok skonczyl przetwarzac wiadomosc." );
}

void View::Obsrv_StatusChanged(const ContactRecord & contact)
{
	LOG4CXX_DEBUG(this->_logger, "Widok otrzymal zmiane statusu. Contact.User.Name: " << contact.userDesc.name.in() << " Contact.Status: " << contact.isAvailable );

	std::string shortMsg(INFO_GET_NEW_STAT1);
	shortMsg.append(contact.userDesc.name.in());
	shortMsg.append(INFO_GET_NEW_STAT2);
	shortMsg.append(contact.isAvailable ? "dostepny" : "niedostepny");

	LOG4CXX_DEBUG(this->_logger, "Ustawienie powiadomienia: " << shortMsg.c_str() );

	// Ustawienie wiadomosci.
	(*GetActiveWindow())->SetMsg(shortMsg);
}

void View::Obsrv_File(const char * userName, const char * fileName)
{
	LOG4CXX_DEBUG(this->_logger, "Widok otrzymal plik.");

	std::string shortMsg(INFO_GET_FILE1);
	shortMsg.append(userName);
	shortMsg.append(INFO_GET_FILE2);
	shortMsg.append(fileName);

	LOG4CXX_DEBUG(this->_logger, "Ustawienie powiadomienia: " << shortMsg.c_str() );

	// Ustawienie wiadomosci.
	(*GetActiveWindow())->SetMsg(shortMsg);
}
