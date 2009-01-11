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

}

///
/// Destruktor.
///
View::~View() 
{
	for(std::list<Window *>::iterator i = _windows.begin(); i != _windows.end(); i++)
		delete *i;
}

///
/// Uruchamia widok.
///
void View::Run()
{
	// Komenda.
	std::string cmd;
	// Aktualne okno.
	std::list<Window *>::iterator activeWindow;

	// Stworzenie glowny okien.
	_windows.push_front(new WelcomeWindow(_controller));

	// Ustawienie aktywnego okna na pierwszego z listy.
	activeWindow = _windows.begin();

	// Petla pobierania instrukcji od uzytkownika.
	while(true)
	{
		// Czyszczenie ostatniej komendy.
		cmd.clear();

		// Renderowanie okna konfiguracji.
		(*activeWindow)->Render(std::cout);

		// Pobranie instrukcji.
		std::cin >> cmd;

		// Zmiana okna.
		if (!cmd.compare(CHANGE_WINDOW))
		{
			// Czyszczenie ekranu.
			system("CLS");

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
				this->_windows.push_front(new ConfigWindow(_controller));
				activeWindow = _windows.begin();
			}
			// Nie ma takiego okna.
			else
				(*activeWindow)->SetMsg(ER_NO_WIN);
		}
		// Zamykanie okna.
		else if (!cmd.compare(CLOSE_WINDOW))
		{
			// Jesli jest to ostatnie okno.
			if ( this->_windows.size() == 1 )
				(*activeWindow)->SetMsg(ER_LAST_WIN);
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
			for(std::list<Window *>::iterator i = _windows.begin(); i != _windows.end(); i++)
			{
				windows.append((*i)->GetName());
				windows.append(", ");
			}

			(*activeWindow)->SetMsg(windows);
		}
		else
		{
			// Przekazanie komendy do okna.
			(*activeWindow)->Command(cmd);
		}

		// Czyszczenie ekranu.
		system("CLS");
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

///
/// Dodanie okna.
/// @param[in] window Okno jakie nalezy dodac.
///
void View::AddWindow(Window * window)
{
	this->_windows.push_back(window);
}

///
/// Usuniecie okna.
/// @param[in] window Okno jakie nalezy usunac.
///
void View::DelWindow(Window * window)
{
	this->_windows.remove(window);
}