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
	_windows.push_back(new WelcomeWindow(_controller));
	_windows.push_back(new ConfigWindow(_controller));

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

		// Jesli wcisnieto ENTER -> zmiana okna.
		if (cmd.compare(CHANGE_WINDOW) == 0)
		{
			// Czyszczenie ekranu.
			system("CLS");

			// Zmiana okna.
			if ( ++activeWindow == _windows.end() )
				activeWindow = _windows.begin();
		}
		else
		{
			// Przekazanie komendy do okna.
			(*activeWindow)->Command(cmd);

			// Czyszczenie ekranu.
			system("CLS");
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