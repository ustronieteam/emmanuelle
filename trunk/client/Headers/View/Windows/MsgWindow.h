#ifndef _MSGWINDOW_H_
#define _MSGWINDOW_H_

#include <list>
#include "Window.h"

// Opjcie konfiguracyjne.
#define MSG_MAX_MSG_LEN		100
#define MSG_MAX_SEE_MSG		3
// Informacje
#define MSG_INF_NO_MSG		"Brak wiadomosci."
#define MSG_INF_SND_MSG		"Wysylanie wiadomosci..."
#define MSG_INF_SHOW_L		"^^ Pokazywane sa ostatnie wiadomosci."
#define MSG_INF_SHOW_A		"^^ Pokazywane sa wszystkie wiadomosci."
// Bledy
#define MSG_ER_SND_MSG		"!@# Nie mozna bylo wyslac wiadomosci!"


///
/// MsgWindow
/// @brief Okienko wysylania i odbierania wiadomosci.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.11
///
class MsgWindow : public Window
{
	private:

		///
		/// Nazwa uzytkownika z ktorym odbywa sie rozmowa.
		///
		std::string _contactName;

		///
		/// Rozmowa.
		///
		std::list<MYMESSAGE> * _talk;

		///
		/// Bufor do pobranie jednej wiadomosci.
		///
		char _singleMsg[MSG_MAX_MSG_LEN];

		///
		/// Typ wyswietlania. 
		///
		bool _showLast;

	public:

		///
		/// Konstruktor.
		/// @param[in] controller Kontroler.
		///
		MsgWindow(Controller * controller, const std::string & name);

		///
		/// Renderowanie okienka.
		/// @param[in] o Strumien do ktorego renderujemy obraz.
		///
		virtual void Render(std::ostream & o);

		///
		/// Komenda przekazana do okna.
		/// @param[in] cmd Komenda.
		///
		virtual void Command(std::string & cmd);

		///
		/// Ustawia rozmowe.
		///
		void SetTalk(std::list<MYMESSAGE> * talk);
};

#endif /* _MSGWINDOW_H_ */