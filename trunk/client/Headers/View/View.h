#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>
#include <list>

#include "ViewData.h"
#include "Window.h"
#include "ConfigWindow.h"
#include "WelcomeWindow.h"
#include "HelpWindow.h"
#include "ContactWindow.h"

using namespace std;

///
/// Redefinicja klasy.
///
class Controller;

///
/// Widok.
/// Widok z architektury MVC (Model, View, Controler)
/// @author Wojciech Grzeskowiak
/// @date 2009.01.10
///
class View
{
		// Przyjaznie.

		// Okno kontaktów musi miec odstep do listy kontaktow.
		//friend class ContactWindow;

	public:

		///
		/// Zwraca instancje. Singleton.
		///
		static View * GetInstance();

    private:

        ///
		/// Kontroler.
		///
        Controller * _controller;

		///
		/// Okna.
		///
		std::list<Window *> _windows;

		///
		/// Lista kontaktow.
		///
		std::list<CONTACT> _contacts;

		///
		/// Konstruktor.
		/// Prywatny bo Singleton.
		///
		View();

    public:

        ///
		/// Destruktor.
		///
        virtual ~View();

		///
		/// Uruchamia widok.
		///
		void Run();

        ///
		/// Zwraca kontroler.
		/// @return Kontroler.
		///
        Controller * GetController();

        ///
		/// Ustawia kontroler.
		/// @param[in] controller Kontroler.
        void SetController(Controller * controller);

		///
		/// Dodanie okna.
		/// @param[in] window Okno jakie nalezy dodac.
		///
		void AddWindow(Window * window);

		///
		/// Usuniecie okna.
		/// @param[in] window Okno jakie nalezy usunac.
		///
		void DelWindow(Window * window);
};

#endif
