#include "ConfigWindow.h"

ConfigWindow::ConfigWindow(Controller * controller, INFO * information) 
	: Window(controller, WIN_CONF)
{
	_information = information;
}

void ConfigWindow::Render(std::ostream & out)
{
	out	<< HEADLINE
		<< SIDE << "^ Konfiguracja\n"
		<< SIDE << std::endl << SIDE << "Serwer [srv]:\t\t";

	if ( this->GetController()->GetServerAddress() == NULL )
		out << "NIE USTALONO";
	else
		out << this->GetController()->GetServerAddress();

	out << '\n' << SIDE << "Tryb [mode:a|p]:\t\t\t";

	if ( this->GetController()->getOwnMode() == DomainData::active )
		out << "Aktywny";
	else if ( this->GetController()->getOwnMode() == DomainData::passiv )
		out << "Passywny";
	else
		out << "BLAD!";

	out << '\n' << SIDE << "Nazwa uzytkownika [uname]:\t";

	if ( this->GetController()->GetOwnName().size() == 0 )
		out << "NIE USTALONO";
	else
		out << this->GetController()->GetOwnName();

	out << '\n' << SIDE << '\n' << SIDE << "^ Informacje:\n" << SIDE << '\n';

	out << SIDE << "Data podlaczenia:\t\t";
	
	if ( this->_information->connectedDate.is_not_a_date_time() )
		out << "NIE PODLACZONO\n";
	else
		out << this->_information->connectedDate << '\n';

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

void ConfigWindow::Command(std::string & cmd)
{
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
		// Tryb
		else if ( !mcmd.compare("mode") )
		{
			std::cin >> mcmd;
			
			if ( !mcmd.compare("a") )
			{
				this->GetController()->setOwnMode(DomainData::active); // Ustaw aktywny
			}
			else if ( !mcmd.compare("p") )
			{
				this->GetController()->setOwnMode(DomainData::passiv); // Ustaw niekatywny
			}
		}
		// Nazwa uzytkownika.
		else if ( !mcmd.compare("uname") )
		{
			std::cin >> mcmd;

			this->GetController()->SetOwnName(mcmd.c_str());

			this->SetMsg(INF_NEW_UNAME);
		}
		else
			this->SetMsg(ER_NO_PARAM);
	}
	else
		this->SetMsg(ER_NO_COMMAND);
}