#ifndef _CONFIGWINDOW_H_
#define _CONFIGWINDOW_H_

#include "Window.h"

///
/// ConfigWindow
/// @brief Okienko konfiguracyjne.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.10
///
class ConfigWindow : public Window
{
	private:

		///
		/// Adres serwera do ktorego jest sie podlaczonym.
		///
		std::string _serverAddress;

	public:

		///
		/// Konstruktor.
		/// @param[in] controller Kontroler.
		///
		ConfigWindow(Controller * controller);

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

#endif /* _CONFIGWINDOW_H_ */