#ifndef _CONFIGWINDOW_H_
#define _CONFIGWINDOW_H_

#include "Window.h"

// Komunikaty
#define INF_NEW_SRV		"^^ Adres serwera zostal zmieniony."
#define INF_NEW_PORT	"^^ Port serwera zostal zmieniony."
#define INF_NEW_UNAME	"^^ Nazwa uzytkownika zostala zmieniona."
#define INF_NEW_UNUM	"^^ Numer uzytkownika zostal zmieniony."
// Bledy
#define INF_ER_NEW_UNUM	"!@# Nie podano liczby!" 
#define INF_ER_NEW_PORT "!@# Port serwera powinien byc liczba!"

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
		/// Konfiguracja.
		///
		CONFIGURATION * _configuration;

		///
		/// Informacje.
		///
		INFO * _information;

	public:

		///
		/// Konstruktor.
		/// @param[in] controller Kontroler.
		///
		ConfigWindow(Controller * controller, CONFIGURATION * configuration, INFO * information);

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