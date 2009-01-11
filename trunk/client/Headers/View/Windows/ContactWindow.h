#ifndef _CONTACTWINDOW_H_
#define _CONTACTWINDOW_H_

#include <list>
#include "ViewData.h"
#include "Window.h"

#define WIN_CONTACT_CON_EN		"[#]"
#define WIN_CONTACT_CON_DI		"[_]"
// Komunikaty.
#define WIN_CONTACT_NO_CON		"Brak kontakow na liscie"
#define WIN_CONTACT_NEW_CON		"^^ Dodano nowy kontakt!"
#define WIN_CONTACT_DEL_CON		"^^ Usunieto kontakt!"
#define WIN_CONTACT_ER_NO_CON	"!@# Nie ma takiego kontaktu na liscie!"
#define WIN_CONTACT_ER_NEW_CON	"!@# Bledna definicja kontaktu! Poprawna: 'add nazwa numer'"

///
/// ContactWindow
/// @brief Okienko z kontaktami.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.11
///
class ContactWindow : public Window
{
	private:

		///
		/// Kontakty.
		///
		std::list<CONTACT> * _contacts;

	public:

		///
		/// Konstruktor.
		/// @param[in] controller Kontroler.
		///
		ContactWindow(Controller * controller, std::list<CONTACT> * contacts);

		///
		/// Renderowanie okienka z kontaktami.
		/// @param[in] o Strumien do ktorego renderujemy obraz.
		///
		virtual void Render(std::ostream & o);

		///
		/// Komenda przekazana do okna.
		/// @param[in] cmd Komenda.
		///
		virtual void Command(std::string & cmd);
};

#endif /* _CONTACTWINDOW_H_ */