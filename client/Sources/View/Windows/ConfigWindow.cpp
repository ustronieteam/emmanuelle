#include "ConfigWindow.h"

///
/// Konstruktor.
/// @param[in] controller Kontroler.
///
ConfigWindow::ConfigWindow(Controller * controller, CONFIGURATION * configuration, INFO * information) 
	: Window(controller, WIN_CONF)
{
	_configuration = configuration;
	_information = information;
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

	if ( this->GetController()->GetServerAddress() == NULL )
		out << "NIE USTALONO";
	else
		out << this->GetController()->GetServerAddress();

	out << '\n' << SIDE << "Port [port]:\t\t\t";

	if ( this->GetController()->GetPortNumber() == 0 )
		out << "NIE USTALONO";
	else
		out << this->GetController()->GetPortNumber();

	out << '\n' << SIDE << "Nazwa uzytkownika [uname]:\t";

	if ( this->GetController()->GetOwnName().size() == 0 )
		out << "NIE USTALONO";
	else
		out << this->GetController()->GetOwnName();

	out << '\n' << SIDE << "Numer uzytkownika [unum]:\t";

	if ( this->GetController()->GetOwnNumber() == 0 )
		out << "NIE USTALONO";
	else
		out << this->GetController()->GetOwnNumber();

	out << '\n' << SIDE << '\n' << SIDE << "^ Informacje:\n" << SIDE << '\n';

	out << SIDE << "Data podlaczenia:\t\t";
	
	if ( this->_information->connectedDate.is_not_a_date_time() )
		out << "NIE PODLACZONO\n";
	else
		out << this->_information->connectedDate << '\n';

	out << SIDE << "Wyslanych wiadomosci:\t\t"	<< this->_information->outMsgCount << '\n';
	out << SIDE << "Odebranych wiadomosci:\t"	<< this->_information->inMsgCount << '\n';
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
	int tmp;
	std::string mcmd;

	if ( !cmd.compare("set") )
	{
		std::cin >> mcmd;

		// Adres serwera.
		if ( !mcmd.compare("srv") )
		{
			std::cin >> mcmd;
			this->GetController()->SetServerAddress(mcmd.c_str());
			this->SetMsg(INF_NEW_SRV);
		}
		// Port
		else if ( !mcmd.compare("port") )
		{
			std::cin >> tmp;
			
			/* Sprawdzanie poprawnosci. */
			if ( std::cin.fail() )
			{
				this->SetMsg(INF_ER_NEW_PORT);
				std::cin.clear( std::cin.rdstate() & ~std::ios::failbit );

				// Pobranie smieci.
				std::cin >> mcmd;
			}
			else
			{
				this->GetController()->SetPortNumber(tmp);
				this->SetMsg(INF_NEW_PORT);
			}
		}
		// Nazwa uzytkownika.
		else if ( !mcmd.compare("uname") )
		{
			std::cin >> mcmd;

			this->GetController()->SetOwnName(mcmd.c_str());
			//this->_configuration->userName = mcmd;

			this->SetMsg(INF_NEW_UNAME);
		}
		// Numer uzytkownika.
		else if ( !mcmd.compare("unum") )
		{
			std::cin >> tmp;

			this->GetController()->SetOwnNumber(tmp);
			//this->_configuration->userNumber = tmp;

			/* Sprawdzanie poprawnosci. */
			if ( std::cin.fail() )
			{
				this->SetMsg(INF_ER_NEW_UNUM);
				std::cin.clear( std::cin.rdstate() & ~std::ios::failbit );

				// Pobranie smieci.
				std::cin >> mcmd;
			}
			else
				this->SetMsg(INF_NEW_UNUM);
		}
		else
			this->SetMsg(ER_NO_PARAM);
	}
	else
		this->SetMsg(ER_NO_COMMAND);
}