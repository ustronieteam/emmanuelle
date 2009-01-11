#include "ConfigWindow.h"

///
/// Konstruktor.
/// @param[in] controller Kontroler.
///
ConfigWindow::ConfigWindow(Controller * controller) : Window(controller, WIN_CONF)
{
	_userNumber = 0;
}

///
/// Renderowanie okienka konfiguracji.
/// @param[in] o Strumien do ktorego renderujemy obraz.
///
void ConfigWindow::Render(std::ostream & out)
{
	out	<< HEADLINE
		<< SIDE << "^ Konfiguracja\n"
		<< SIDE << std::endl << SIDE << "Serwer [srv]:\t\t\t";

	if ( this->_serverAddress.empty() )
		out << "NIE PODLACZONO";
	else
		out << _serverAddress;

	out << '\n' << SIDE << "Nazwa uzytkownika [uname]:\t";

	if ( this->_userName.empty() )
		out << "NIE USTALONO";
	else
		out << _userName;

	out << '\n' << SIDE << "Numer uzytkownika [unum]:\t";

	if ( this->_userNumber == 0 )
		out << "NIE USTALONO";
	else
		out << _userNumber;

	out << '\n'<< SIDE << "Data podlaczenia:\t\t2009.01.10\n";
	out << SIDE << "Ilosc kontaktow:\t\t0\n";	
	out << SIDE << "Wyslanych wiadomosci:\t\t0\n";	
	out << SIDE << "Odebranych wiadomosci:\t0\n";	
	out << SIDE << '\n';
	out << LINE;

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
void ConfigWindow::Command(std::string & cmd)
{
	std::string mcmd;

	if ( !cmd.compare("set") )
	{
		std::cin >> mcmd;

		// Adres serwera.
		if ( !mcmd.compare("srv") )
		{
			std::cin >> this->_serverAddress;
			this->SetMsg(INF_NEW_SRV);
		}
		// Nazwa uzytkownika.
		else if ( !mcmd.compare("uname") )
		{
			std::cin >> this->_userName;
			this->SetMsg(INF_NEW_UNAME);
		}
		// Numer uzytkownika.
		else if ( !mcmd.compare("unum") )
		{
			std::cin >> this->_userNumber;
			this->SetMsg(INF_NEW_UNUM);
		}
		else
			this->SetMsg(ER_NO_PARAM);
	}
	else
		this->SetMsg(NO_COMMAND);
}