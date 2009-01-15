#include "WelcomeWindow.h"

WelcomeWindow::WelcomeWindow(Controller * controller) : Window(controller, WIN_WELCOME)
{

}

void WelcomeWindow::Render(std::ostream & out)
{
	out << HEADLINE
		<< SIDE << '\n'
		<< SIDE << "\t+-------+\n"
		<< SIDE << "\t|       |\tEmmanuelle\n"
		<< SIDE << "\t|  [----+\n"
		<< SIDE << "\t|  |	   \tSystem\n"
		<< SIDE << "\t|  [--+  \t  Wymiany\n"
		<< SIDE << "\t|  [--+  \t     Komunikatow\n"
		<< SIDE << "\t|  |\n"
		<< SIDE << "\t|  [----+\tWpisz 'op help' aby\n"
		<< SIDE << "\t|       |\t  usyskac pomoc.\n"
		<< SIDE << "\t+-------+\n"
		<< SIDE << '\n'
		<< SIDE << "\t Autorzy: \tMarian Szczykulski\n"
		<< SIDE << "\t\t\tMateusz Kolodziejczyk\n"
		<< SIDE << "\t\t\tWojciech Grzeskowiak\n"
		<< LINE;

		if ( ! this->GetMsg().empty() )
		{
			out << SIDE << this->GetMsg() << '\n';
			this->ClearMsg();
		}

		out << PROMPT;
}

void WelcomeWindow::Command(std::string & cmd)
{
	this->SetMsg(ER_NO_COMMAND);
}