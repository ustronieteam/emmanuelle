#include "View.h"

///
/// Zwraca instancje. Singleton.
///
View * View::GetInstance()
{
	static View * _instance = new View();

	return _instance;
}

///
/// Konstruktor.
/// Prywatny bo Singleton.
///
View::View() 
{
	// Zerowanie niektorych skladowych.
	_configuration.userNumber	= 0;
	_information.inMsgCount		= 0;
	_information.outMsgCount	= 0;
	_information.connected		= false;

	// DANE WPISANE DO TESTOWANIA.
	_configuration.serverAddress	= "server";
	_configuration.serverPort		= 8080;
	_configuration.userName			= "user";
	_configuration.userNumber		= 8;
}

///
/// Destruktor.
///
View::~View() 
{
	// Usuniecie okien.
	for(std::list<Window *>::iterator i = _windows.begin(); i != _windows.end(); i++)
		delete *i;

	// Usuniecie rozmow.
	for(std::map<std::string, std::list<MYMESSAGE> *>::iterator i = _talks.begin(); i != _talks.end(); i++)
		delete (*i).second;
}

///
/// Uruchamia widok.
///
void View::Run()
{
	// Komenda.
	std::string cmd;
	// Aktualne okno.
	std::list<Window *>::iterator activeWindow, tmp;

	// Stworzenie glowny okien.
	_windows.push_front(new WelcomeWindow(_controller));

	// Ustawienie aktywnego okna na pierwszego z listy.
	activeWindow = _windows.begin();

	// Petla pobierania instrukcji od uzytkownika.
	while(true)
	{
		// Czyszczenie ekranu.
		system("CLS");

		// Czyszczenie ostatniej komendy.
		cmd.clear();

		// Renderowanie okna konfiguracji.
		(*activeWindow)->Render(std::cout);

		// Pobranie instrukcji.
		std::cin >> cmd;

		// Zmiana okna.
		if (!cmd.compare(CHANGE_WINDOW))
		{
			// Zmiana okna.
			if ( ++activeWindow == _windows.end() )
				activeWindow = _windows.begin();
		}
		// Wyjscie z aplikacji.
		else if (!cmd.compare(EXIT_APP))
		{
			// TODO: Wywo³anie czegos na kontrolerze.

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
				this->_windows.push_front(new WelcomeWindow(_controller));
				activeWindow = _windows.begin();
			}
			// Okno pomocy.
			else if (!cmd.compare(WIN_HELP))
			{
				this->_windows.push_front(new HelpWindow(_controller));
				activeWindow = _windows.begin();
			}
			// Okno konfiguracji.
			else if (!cmd.compare(WIN_CONF))
			{
				this->_windows.push_front(new ConfigWindow(_controller, &_configuration, &_information));
				activeWindow = _windows.begin();
			}
			// Okno kontaktow.
			else if (!cmd.compare(WIN_CONTACT))
			{
				this->_windows.push_front(new ContactWindow(_controller, &_contacts));
				activeWindow = _windows.begin();
			}
			// Okno rozmowy.
			else if (!cmd.compare(WIN_MSG))
			{
				cmd.clear();

				// Pobrana nazwa uzytkownika z listy kontaktow.
				std::cin >> cmd;

				// Sprawdzenie czy nie otwarto juz okna do tej rozmowy.
				for(tmp = _windows.begin(); tmp != _windows.end(); tmp++)
					if ( (*tmp)->GetName().find(cmd, 0) != string::npos )
						break;
				
				// Nie znaleziono takiej rozmowy/
				if ( tmp == _windows.end() )
				{
					// Stworzenie okna.
					MsgWindow * msgWin = new MsgWindow(_controller, cmd);

					// Jesli juz istniala rozmowa.
					if ( _talks.find(cmd) != _talks.end() )
						msgWin->SetTalk(_talks[cmd]);
					// Nowa rozmowa.
					else
						msgWin->SetTalk(_talks[cmd] = new std::list<MYMESSAGE>());

					_windows.push_front(msgWin);

					activeWindow = _windows.begin();
				}
				// Znaleziono taka rozmowe.
				else
				{
					// Otwarcie tego okna.
					activeWindow = tmp;
				}
			}
			// Nie ma takiego okna.
			else
				(*activeWindow)->SetMsg(ER_WIN_NO_WIN);
		}
		// Zamykanie okna.
		else if (!cmd.compare(CLOSE_WINDOW))
		{
			// Jesli jest to ostatnie okno.
			if ( this->_windows.size() == 1 )
				(*activeWindow)->SetMsg(ER_WIN_LAST_WIN);
			else
			{
				//Zwolnenie pamieci.
				delete *activeWindow;

				// Usuniecie z listy okien.
				this->_windows.erase(activeWindow);

				// Ustawienie nowego okna.
				activeWindow = this->_windows.begin();
			}
		}
		// Lista okien
		else if (!cmd.compare(LIST_WIN))
		{
			std::string windows("Otwarte okna: ");
			for(tmp = _windows.begin(); tmp != _windows.end(); tmp++)
			{
				windows.append("[");

				if ( tmp == activeWindow )
					windows.append("!");

				windows.append((*tmp)->GetName());
				windows.append("]");
			}

			(*activeWindow)->SetMsg(windows);
		}
		// Podlaczenie sie do serwera.
		else if (!cmd.compare(CONNECT))
		{
			if ( _information.connected )
				(*activeWindow)->SetMsg(ER_CONN_IS_CONN);
			else if ( _configuration.serverAddress.empty() )
				(*activeWindow)->SetMsg(ER_CONN_NO_SERVE);
			else if ( _configuration.userName.empty() )
				(*activeWindow)->SetMsg(ER_CONN_NO_UNAME);
			else if ( _configuration.userNumber == 0 )
				(*activeWindow)->SetMsg(ER_CONN_NO_UNUMB);
			else
			{
				// Mamy wszystkie parametry do podlaczenia.

				std::cout << PROMPT << INFO_CONN_STILL;

				// !!! Podlaczenie od serwera.
				bool result = _controller->ConnectToServer();

				// Nie udalo sie podlaczyc.
				if ( !result )
					(*activeWindow)->SetMsg(ER_CONN_NO_CONN);
				else
				{
					_information.connected = true;

					(*activeWindow)->SetMsg(INFO_CONN_CONN_OK);

					_information.connectedDate = boost::posix_time::second_clock::local_time();
				}
			}
		}
		// Odlaczanie
		else if (!cmd.compare(DISCONNECT))
		{
			if ( !_information.connected )
				(*activeWindow)->SetMsg(ER_DCONN_NO_CONN);
			else
			{
				// Mozemy rozlaczac.

				std::cout << PROMPT << INFO_DCONN_STILL;

				// !!! Rozlaczenie sie od serwera.
				int result = _controller->Disconnect();

				// Nie udalo sie rozlaczyc.
				if ( result < 0 )
					(*activeWindow)->SetMsg(ER_DCONN_CANT);
				else
				{
					_information.connected = false;
					
					(*activeWindow)->SetMsg(INFO_DCONN_DCONN_OK);

					_information.connectedDate = boost::posix_time::ptime();
				}
			}
		}
		else
		{
			// Przekazanie komendy do okna.
			(*activeWindow)->Command(cmd);
		}
	}
}

///
/// Zwraca kontroler.
/// @return Kontroler.
///
Controller * View::GetController() 
{
    return this->_controller;
}

///
/// Ustawia kontroler.
/// @param[in] controller Kontroler.
///
void View::SetController(Controller * controller) 
{
	this->_controller = controller;
}