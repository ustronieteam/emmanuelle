#include "HelpWindow.h"

HelpWindow::HelpWindow(Controller * controller) : Window(controller, WIN_HELP)
{

}

void HelpWindow::Render(std::ostream & out)
{
	out << HEADLINE
		<< SIDE << "^ Pomoc\n|\n"
		<< SIDE << "* Po uruchomieniu aplikacji znajdujesz sie w oknie powitalnym\n"
		<< SIDE << "* Okna otwiera sie poleceniem 'op nazwa_okna parametry'\n"
		<< SIDE << "* Aby przelaczyc sie miedzy otwartymi oknami uzyj '`' oraz Enter\n"
		<< SIDE << "* Aby zamknac okno nalezy je wybrac i wpisac polecenie 'cl'\n"
		<< SIDE << "* Jedno okno zawsze musi byc otwarte!\n"
		<< SIDE << "* Lista okien pod poleceniem 'wins'\n"
		<< SIDE << "* Dostepne okna: 'welcome', 'help', 'conf', 'con'\n"
		<< SIDE << "* Dodanie kontaktu w oknie 'con': 'add nazwa numer'\n"
		<< SIDE << "* Usuniecie kontaktu w oknie 'con': 'del nazwa'\n"
		<< SIDE << "* Aby podlaczyc sie do serwera uzyj 'conn', rozlaczyc 'dcon'\n"
		<< SIDE << "* Zawsze mozna zakonczyc aplikacje poleceniem 'exit'\n"
		<< LINE;

		if ( ! this->GetMsg().empty() )
		{
			out << SIDE << this->GetMsg() << '\n';
			this->ClearMsg();
		}

		out << PROMPT;
}

void HelpWindow::Command(std::string & cmd)
{
	this->SetMsg(ER_NO_COMMAND);
}