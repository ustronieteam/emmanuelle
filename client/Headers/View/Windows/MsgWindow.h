#ifndef _MSGWINDOW_H_
#define _MSGWINDOW_H_

#include <list>
#include "Window.h"

// Opjcie konfiguracyjne.
#define MSG_MAX_MSG_LEN		100
#define MSG_MAX_SEE_MSG		10
// Informacje
#define MSG_INF_NO_MSG		"Brak wiadomosci."
#define MSG_INF_SND_MSG		"Wysylanie wiadomosci..."
#define MSG_INF_SND_FIL		"Wysylanie pliku..."
#define MSG_INF_SHOW_L		"^^ Pokazywane sa ostatnie wiadomosci."
#define MSG_INF_SHOW_A		"^^ Pokazywane sa wszystkie wiadomosci."
#define MSG_INF_FILE_SND1	" Plik '"
#define MSG_INF_FILE_SND2	"' zostal pomyslnie wyslany."
#define MSG_INF_FILE_SNDR	"[emmanuelle]"
// Bledy
#define MSG_ER_SND_MSG		"!@# Nie mozna bylo wyslac wiadomosci!"
#define MSG_ER_SND_FIL		"!@# Nie znaleziono pliku!"
#define MSG_ER_FILE_SND2	" nie mogl byc wyslany."


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
		/// Mutex na rozmowe.
		///
		boost::mutex * _mxTalk;

		///
		/// Mutex na renderowanie.
		///
		boost::mutex _mxRender;

		///
		/// Bufor do pobranie jednej wiadomosci.
		///
		char _singleMsg[MSG_MAX_MSG_LEN];

		///
		/// Typ wyswietlania. 
		///
		bool _showLast;

		///
		/// Obiekt logowania.
		///
		log4cxx::LoggerPtr _logger;

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
		/// @param[in] talk Wskaznik na rozmowe.
		///
		void SetTalk(std::list<MYMESSAGE> * talk);

		///
		/// Ustawia mutex na rozmowe.
		/// @param[in] mxTalk Wskaznik na mutex do rozmowy.
		///
		void SetMutexTalk(boost::mutex * mxTalk);
};

#endif /* _MSGWINDOW_H_ */