#include "ConfigWindow.h"

///
/// Konstruktor.
/// @param[in] controller Kontroler.
///
ConfigWindow::ConfigWindow(Controller * controller) : Window(controller)
{

}

///
/// Renderowanie okienka konfiguracji.
/// @param[in] o Strumien do ktorego renderujemy obraz.
///
void ConfigWindow::Render(std::ostream & out)
{
	out	<< HEADLINE
		<< SIDE << "^ Konfiguracja\n"
		<< SIDE << std::endl << SIDE << "Serwer:\t\t\t";

	if ( this->_serverAddress.empty() )
		out << "NIE PODLACZONO";
	else
		out << _serverAddress;;

	out << "\t[srv]\n";


	out << SIDE << "Data podlaczenia:\t\t2009.01.10\n";
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

	out << ">> ";
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

		if ( !mcmd.compare("srv") )
		{
			std::cin >> this->_serverAddress;
			this->SetMsg("^^ Adres serwera zostal zmieniony.");
		}
		else
			this->SetMsg("!@# Brak takiego parametru.");
	}
	else
		this->SetMsg(NO_COMMAND);
}