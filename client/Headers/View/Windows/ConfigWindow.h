#ifndef _CONFIGWINDOW_H_
#define _CONFIGWINDOW_H_

#include "Window.h"

// Komunikaty
#define INF_NEW_SRV		"^^ Adres serwera zostal zmieniony."
#define INF_NEW_UNAME	"^^ Nazwa uzytkownika zostala zmieniona."
#define INF_NEW_UNUM	"^^ Numer uzytkownika zostal zmieniony."

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

		///
		/// Nazwa uzytkownika.
		///
		std::string _userName;

		///
		/// Numer uzytkownika.
		///
		int _userNumber;

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