#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>

// Pomocne definicje.
#define HEADLINE		"+-------------------------------------------------------[_][O][X]-+\n"
#define LINE			"+-----------------------------------------------------------------+\n"
#define SIDE			"| "
#define PROMPT			">> "
// Polecenia
#define CHANGE_WINDOW	"`"
#define EXIT_APP		"exit"
#define OPEN_WINDOW		"op"
#define CLOSE_WINDOW	"cl"
#define LIST_WIN		"wins"		
// Okna
#define WIN_WELCOME		"welcome"
#define WIN_CONF		"conf"
#define WIN_HELP		"help"
#define WIN_CONTACT		"con"
// Wspolne komunikaty.
#define NO_COMMAND		"!@# Brak takiej komendy!"
// Bledy
#define ER_NO_WIN		"!@# Nie ma takiego okna!"
#define ER_LAST_WIN		"!@# Nie mozna zamknac ostatniego okna!"
#define ER_NO_PARAM		"!@# Brak takiego parametru."

///
/// Redefinicja klasy.
///
class Controller;

///
/// Window
/// @brief Klasa bazowa dla okien.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.10
///
class Window
{
	private:

		///
		/// Kontroler.
		///
		Controller * _controller;

		/// 
		/// Wiadomosc.
		/// 
		std::string _msg;

		///
		/// Nazwa.
		///
		std::string _name;

	public:
		
		///
		/// Ustawienie kontrolera.
		/// @param[in] controller Kontroller.
		///
		void SetController(Controller * controller);

		///
		/// Pobranie kontroler.
		/// @return Kontroler.
		///
		Controller * GetController();

		///
		/// Ustawienie wiadomsoci.
		/// @param[in] msg Wiadomosc
		///
		void SetMsg(const std::string & msg);

		///
		/// Pobranie wiadomosci.
		/// @return Wiadomosc
		///
		const std::string & GetMsg();

		///
		/// Czyszczenie wiadomosci.
		///
		void ClearMsg();

		///
		/// Konstruktor.
		/// @param[in] controller Kontroller.
		///
		Window(Controller * controller, std::string name);

		///
		/// Odrysowanie okna.
		/// @param[in] o Strumien do ktorego renderujemy obraz.
		///
		virtual void Render(std::ostream & o) = 0;

		///
		/// Komenda przekazana do okna.
		/// @param[in] cmd Komenda.
		///
		virtual void Command(std::string & cmd) = 0;

		///
		/// Pobiera nazwe okna.
		/// @return Nazwa okna.
		///
		std::string & GetName();
};

#endif /* _WINDOW_H_ */