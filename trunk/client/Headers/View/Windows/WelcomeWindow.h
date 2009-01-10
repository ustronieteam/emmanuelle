#ifndef _WELCOMEWINDOW_H_
#define _WELCOMEWINDOW_H_

#include "Window.h"

///
/// WelcomeWindow
/// @brief Okienko konfiguracyjne.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.10
///
class WelcomeWindow : public Window
{
	public:

		///
		/// Konstruktor.
		/// @param[in] controller Kontroler.
		///
		WelcomeWindow(Controller * controller);

		///
		/// Renderowanie okienka konfiguracji.
		/// @param[in] o Strumien do ktorego renderujemy obraz.
		///
		virtual void Render(std::ostream & o);

		///
		/// Komenda przekazana do okna.
		/// @param[in] cmd Komenda.
		///
		virtual void Command(std::string & cmd);
};

#endif /* _WELCOMEWINDOW_H_ */