#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>

// Pomocne definicje.
#define HEADLINE		"+---------------------------------------------[_][O][X]-+\n"
#define LINE			"+-------------------------------------------------------+\n"
#define SIDE			"| "
#define CHANGE_WINDOW	"`"
#define NO_COMMAND		"!@# Brak takiej komendy!"

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

	protected:
		
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

	public:

		///
		/// Konstruktor.
		/// @param[in] controller Kontroller.
		///
		Window(Controller * controller);

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
};

#endif /* _WINDOW_H_ */