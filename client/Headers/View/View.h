#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <string>
#include <list>

#include "MessageObserver.h"
#include "StatusObserver.h"
#include "FileObserver.h"

#include "ConfigWindow.h"
#include "WelcomeWindow.h"
#include "HelpWindow.h"
#include "ContactWindow.h"
#include "MsgWindow.h"

// Polecenia.
#define CHANGE_WINDOW		"`"
#define EXIT_APP			"exit"
#define OPEN_WINDOW			"op"
#define CLOSE_WINDOW		"cl"
#define LIST_WIN			"wins"	
#define CONNECT				"conn"
#define DISCONNECT			"dcon"
// Bledy.
#define ER_WIN_NO_WIN		"!@# Nie ma takiego okna!"
#define ER_WIN_LAST_WIN		"!@# Nie mozna zamknac ostatniego okna!"
#define ER_CONN_NO_SERVE	"!@# Nie ustalono nazwy serwera!"
#define ER_CONN_NO_UNAME	"!@# Nie ustalono nazwy uzytkownika!"
#define ER_CONN_NO_UNUMB	"!@# Nie ustalono numeru uzytkownika!"
#define ER_CONN_NO_CONN		"!@# Nie mozna bylo sie podlaczyc! Sprawdz adres serwera."
#define ER_CONN_IS_CONN		"!@# Jestes juz podlaczony do serwera!"
#define ER_DCONN_NO_CONN	"!@# Nie jestes podlaczony do serwera!"
#define ER_DCONN_CANT		"!@# Nie mozna bylo rozlaczyc z serwerem!"
// Informacje.
#define INFO_CONN_CONN_OK	"^^ Pomyslnie podlaczono do serwera."
#define INFO_CONN_STILL		"Trwa laczenie do serwera "
#define INFO_DCONN_DCONN_OK "^^ Rozlaczono z serwerem."
#define INFO_DCONN_STILL	"Trwa rozlaczanie..."
#define INFO_GET_NEW_MSG	"^^ Otrzymales nowa rozmowe od "
#define INFO_GET_NEW_STAT1	"^^ Twoj znajomy "
#define INFO_GET_NEW_STAT2	" zmienil status na "
#define INFO_GET_FILE1		"^^ Twoj znajomy "
#define INFO_GET_FILE2		" przyslal ci plik "
#define INFO_GET_FILE_MSG	" Przyslano Ci plik: "
#define INFO_GET_FILE_MSND	"[emmanuelle]"

using namespace std;

///
/// Widok.
/// Widok z architektury MVC (Model, View, Controler)
/// @author Wojciech Grzeskowiak
/// @date 2009.01.10
///
class View : public IObserverView
{
	public:

		///
		/// Zwraca instancje. Singleton.
		///
		static View * GetInstance();

    private:

        ///
		/// Kontroler.
		///
        Controller * _controller;

		///
		/// Okna.
		///
		std::list<Window *> _windows;

		///
		/// Aktywne okno.
		///
		std::list<Window *>::iterator _activeWindow;

		///
		/// Informacje.
		///
		INFO _information;

		///
		/// Aktualne rozmowy.
		///
		std::map<std::string, std::list<MYMESSAGE> *> _talks;

		///
		/// Mutexy na aktualne rozmowy.
		///
		std::map<std::string, boost::mutex *> _mxsTalks;

		///
		/// Konstruktor.
		/// Prywatny bo Singleton.
		///
		View();

		///
		/// Mutex do aktywnego okna.
		///
		boost::mutex _mxActiveWindow;

		///
		/// Mutex do zbioru okien.
		///
		boost::mutex _mxWindows;

		///
		/// Mutex na tworzenie, otwieranie okien rozmow.
		///
		boost::mutex _mxCreateTalks;

		///
		/// Obiekt logowania.
		///
		log4cxx::LoggerPtr _logger;

    public:

        ///
		/// Destruktor.
		///
        virtual ~View();

		///
		/// Uruchamia widok.
		///
		void Run();

        ///
		/// Zwraca kontroler.
		/// @return Kontroler.
		///
        Controller * GetController();

        ///
		/// Ustawia kontroler.
		/// @param[in] controller Kontroler.
		///
        void SetController(Controller * controller);

		///
		/// Ustawia aktywne okno.
		/// @param[in] window Iterator na okno ktore ma byc aktywne.
		///
		void SetActiveWindow(std::list<Window *>::iterator window);

		///
		/// Pobiera aktywne okno.
		/// @return Iterator na aktywne okno.
		///
		std::list<Window *>::iterator GetActiveWindow();

		///
		/// Zmien aktywne okno na nastepne.
		///
		void ChangeActiveWindow();

		///
		/// Dodaje okno.
		/// @param[in] window Okno ktore nalezy dodac.
		///
		std::list<Window *>::iterator AddWindow(Window * window);

		///
		/// Usuwa okno.
		/// @param[in] window Iterator na okno jakie naleyz usunac.
		///
		bool DelWindow(std::list<Window *>::iterator window);

		///
		/// Pobiera liste okien
		/// @return Lista okien.
		///
		std::list<Window *> GetAllWindows();

		/// Metody wywolywane przez obserwatorów. IObserverView interface.

		///
		/// Odebranie wiadomosci
		/// @param[in] senderAddress Adres nadawcy.
		/// @param[in] message Wiadomosc.
		///
		virtual void Obsrv_ReciveMessage(const DomainData::User & senderAddress, const DomainData::Message & message);

		///
		/// Zmiana statusu osoby na liscie kontatkow.
		/// @param[in] contact Kontakt ktory sie zmienil.
		///
		virtual void Obsrv_StatusChanged(const ContactRecord & contact);

		///
		/// Odebranie pliku.
		/// @param[in]
		///
		virtual void Obsrv_File(const char * userName, const char * fileName);
};

#endif
