#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "Controller.h"
#include "ViewData.h"

#include <iostream>
#include <string>

#include <boost/thread/mutex.hpp>

// Pomocne definicje.
#define HEADLINE			"+-------------------------------------------------------[_][O][X]-+\n"
#define LINE				"+-----------------------------------------------------------------+\n"
#define SIDE				"| "
#define PROMPT				">> "
// Okna
#define WIN_WELCOME			"welcome"
#define WIN_CONF			"conf"
#define WIN_HELP			"help"
#define WIN_CONTACT			"con"
#define WIN_MSG				"msg"
// Wspolne komunikaty.
#define ER_NO_COMMAND		"!@# Brak takiej komendy!"
#define ER_NO_PARAM			"!@# Brak takiego parametru!"

#ifndef WIN32
#define CLSCMD "clear"
#else
#define CLSCMD "CLS"
#endif

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

		///
		/// Mutex na wiadomosci.
		///
		boost::mutex _mxMsg;

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

		///
		/// Ustawia nazwe okna.
		/// @param[in] name Nazwa okna.
		///
		void SetName(const std::string & name);
};

#endif /* _WINDOW_H_ */