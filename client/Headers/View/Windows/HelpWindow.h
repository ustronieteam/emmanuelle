#ifndef _HELPWINDOW_H_
#define _HELPWINDOW_H_

#include "Window.h"

///
/// HelpWindow
/// @brief Okienko z pomoca.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.10
///
class HelpWindow : public Window
{
	public:

		///
		/// Konstruktor.
		/// @param[in] controller Kontroler.
		///
		HelpWindow(Controller * controller);

		///
		/// Renderowanie okienka help.
		/// @param[in] o Strumien do ktorego renderujemy obraz.
		///
		virtual void Render(std::ostream & o);

		///
		/// Komenda przekazana do okna.
		/// @param[in] cmd Komenda.
		///
		virtual void Command(std::string & cmd);
};

#endif /* _HELPWINDOW_H_ */