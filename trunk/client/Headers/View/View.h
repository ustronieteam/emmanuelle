#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>
#include <list>

#include "Controller.h"
#include "ViewData.h"
#include "Window.h"
#include "ConfigWindow.h"
#include "WelcomeWindow.h"
#include "HelpWindow.h"
#include "ContactWindow.h"
#include "MsgWindow.h"

// Polecenia.
#define CHANGE_WINDOW		"`"
#define EXIT_APP			"exit"
#define OPEN_WINDOW			"op"
#define CLOSE_WINDOW		"cl"
#define LIST_WIN			"wins"	
#define CONNECT				"conn"
#define DISCONNECT			"dcon"
// Bledy.
#define ER_WIN_NO_WIN		"!@# Nie ma takiego okna!"
#define ER_WIN_LAST_WIN		"!@# Nie mozna zamknac ostatniego okna!"
#define ER_CONN_NO_SERVE	"!@# Nie ustalono nazwy serwera!"
#define ER_CONN_NO_UNAME	"!@# Nie ustalono nazwy uzytkownika!"
#define ER_CONN_NO_UNUMB	"!@# Nie ustalono numeru uzytkownika!"
#define ER_CONN_NO_CONN		"!@# Nie mozna bylo sie podlaczyc! Sprawdz adres serwera."
#define ER_CONN_IS_CONN		"!@# Jestes juz podlaczony do serwera!"
#define ER_DCONN_NO_CONN	"!@# Nie jestes podlaczony do serwera!"
#define ER_DCONN_CANT		"!@# Nie mozna bylo rozlaczyc z serwerem!"
// Informacje.
#define INFO_CONN_CONN_OK	"^^ Pomyslnie podlacono do serwera."
#define INFO_CONN_STILL		"Trwa laczenie..."
#define INFO_DCONN_DCONN_OK "^^ Rozlaczono z serwerem."
#define INFO_DCONN_STILL	"Trwa rozlaczanie..."

using namespace std;

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
		//friend class ConfigWindow;

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
		/// Konfiguracja.
		///
		CONFIGURATION _configuration;

		///
		/// Informacje.
		///
		INFO _information;

		///
		/// Aktualne rozmowy.
		///
		std::map<std::string, std::list<MYMESSAGE> *> _talks;

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
};

#endif
