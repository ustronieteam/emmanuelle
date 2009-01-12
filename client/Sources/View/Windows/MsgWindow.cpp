#include "MsgWindow.h"

///
/// Konstruktor.
/// @param[in] controller Kontroler.
///
MsgWindow::MsgWindow(Controller * controller, const std::string & name) 
	: Window(controller, WIN_MSG)
{
	// Inicjalizacja loggera.
	_logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("MsgWindow"));
	_logger->setLevel(log4cxx::Level::getAll());

	_contactName = name;
	_talk = NULL;
	_showLast = true;

	std::string wname;

	wname.append(WIN_MSG);
	wname.append("(");
	wname.append(_contactName);
	wname.append(")");

	this->SetName(wname);
}

///
/// Renderowanie okienka.
/// @param[in] o Strumien do ktorego renderujemy obraz.
///
void MsgWindow::Render(std::ostream & out)
{
	boost::mutex::scoped_lock sl(_mxRender);

	out	<< HEADLINE
		<< SIDE << "^ Rozmowa z ~" << this->_contactName << "\n" << SIDE << '\n';

	_mxTalk->lock();

		if ( _talk != NULL )
		{
			if ( _talk->size() != 0 )
			{
				int k = 0;
				for(std::list<MYMESSAGE>::iterator i = _talk->begin(); (i != _talk->end()) && ((k < MSG_MAX_SEE_MSG && _showLast) || !_showLast); ++i, ++k)
				{
					out << SIDE << (*i).sender << " [" << (*i).time << "]\n"
						<< SIDE << (*i).content << '\n' << SIDE << '\n';
				}
			}
			else
			{
				out << SIDE << MSG_INF_NO_MSG << '\n';
			}
		}

	_mxTalk->unlock();

	out << SIDE << '\n' << LINE;

	if ( ! this->GetMsg().empty() )
	{
		out << SIDE << this->GetMsg() << '\n';
		this->ClearMsg();
	}

	out << PROMPT;
}

///
/// Komenda przekazana do okna.
/// @param[in] cmd Komenda.
///
void MsgWindow::Command(std::string & cmd)
{
	int result;
	std::string mcmd;
	MYMESSAGE msg;

	// Wyslanie wiadomosci.
	if ( !cmd.compare("snd") )
	{
		// Pobranie ca�e linii wiadomosci.
		std::cin.getline(this->_singleMsg, MSG_MAX_MSG_LEN-1);

		// Komunikat o wysylaniu wiadomosci.
		std::cout << MSG_INF_SND_MSG;

		LOG4CXX_DEBUG(this->_logger, "Wysylanie wiadomosci... Adresat: " << _contactName.c_str() << " Tresc: " << _singleMsg);

		// !!! Wywolanie na kontrolerze.
		bool result = this->GetController()->SendMessageToClient(_singleMsg, _contactName.c_str());

		LOG4CXX_DEBUG(this->_logger, "Rezultat wysylania wiadomosci: " << result);

		if ( result )
		{
			msg.content = std::string(this->_singleMsg);
			msg.time	= boost::posix_time::second_clock::local_time();
			msg.sender	= this->GetController()->GetOwnName();
			
			_mxTalk->lock();
				_talk->push_front(msg);
			_mxTalk->unlock();
		}
		// Jesli nie mozna bylo wyslac wiadomosci.
		else
			this->SetMsg(MSG_ER_SND_MSG);
	}
	// Wyswietlenie wszystkich.
	else if ( !cmd.compare("all") )
	{
		this->_showLast = false;
		this->SetMsg(MSG_INF_SHOW_A);
	}
	// Wyswietlenie ostatnich.
	else if ( !cmd.compare("last") )
	{
		this->_showLast = true;
		this->SetMsg(MSG_INF_SHOW_L);
	}
	// Odswiezenie.
	else if ( !cmd.compare("r") )
	{
		; // Pusta operacja.
	}
	// Nieznana instrukcja.
	else
		this->SetMsg(ER_NO_COMMAND);
}

///
/// Ustawia rozmowe.
/// @param[in] talk Wskaznik na rozmowe.
///
void MsgWindow::SetTalk(std::list<MYMESSAGE> * talk)
{
	this->_talk = talk;
}

///
/// Ustawia mutex na rozmowe.
/// @param[in] mxTalk Wskaznik na mutex do rozmowy.
///
void MsgWindow::SetMutexTalk(boost::mutex * mxTalk)
{
	this->_mxTalk = mxTalk;
}