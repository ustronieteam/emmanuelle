#ifndef _VIEWDATA_H_
#define _VIEWDATA_H_

#include <boost/date_time/posix_time/posix_time.hpp>

///
/// Struktura trymajaca kontakt.
///
typedef struct _contact
{
	///
	/// Nazwa kontaktu.
	///
	std::string name;
	///
	/// Numer kontaktu.
	///
	int number;
	///
	/// Dostepnosc kontaktu.
	///
	bool status;
}
CONTACT;

///
/// Struktura trzymajaca konfiguracje.
///
typedef struct _configuration
{
	///
	/// Adres serwer do podlaczenia.
	/// 
	std::string serverAddress;

	///
	/// Port na ktorym podlaczamy sie do serwera.
	///
	int serverPort;

	///
	/// Nazwa uzytkownika.
	///
	std::string userName;

	///
	/// Numer uzytkownika.
	///
	int userNumber;
}
CONFIGURATION;

///
/// Struktura trzymajaca informacje.
///

typedef struct _info
{
	///
	/// Status podlaczenia.
	///
	bool connected;

	///
	/// Czas podlaczenia.
	///
	boost::posix_time::ptime connectedDate;

	///
	/// Ilosc odebranych wiadomosci
	///
	int inMsgCount;
}
INFO;


///
/// Struktura trzymajaca pojedyncza wiadomosc.
///
typedef struct _msg
{
	///
	/// Data otrzymania wiadomosci.
	///
	boost::posix_time::ptime time;

	///
	/// Tresc wiadomosci.
	///
	std::string content;

	/// 
	/// Nadawca.
	///
	std::string sender;
}
MYMESSAGE;

#endif /* _VIEWDATA_H_ */