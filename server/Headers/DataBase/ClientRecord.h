#ifndef CLIENTRECORD_H
#define CLIENTRECORD_H

#include "Record.h"

// Aby moc urzywac takich struktur jak Enability.
using namespace DomainData;
using namespace ClientInterfaces;

///
/// Client Rekord
/// @brief Podstawowa jednosta informacji w bazie danych o klientach.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.06
///
class ClientRecord : Record
{
	private:

		///
		/// Identyfikator serwera do ktorego podlaczony jest klient.
		int _clientServerId;

		///
		/// Namiastka klienta dla serwera.
		IClientServer * _clientRemoteInstance;

		///
		/// Dostepnosc klienta.
		struct Enability _enability;

    public:

        ///
		/// Konstruktor bezparametrowy.
        ClientRecord();

		///
		/// Konstruktor kopiujacy.
		/// @param[in] arg Record do skopiowania.
        ClientRecord(const ClientRecord & arg);

        ///
		/// Operator przypisania.
		/// param[in] arg Record ktory chcemy przypisac.
        ClientRecord & operator =(const ClientRecord & arg);

        ///
		/// Destruktor.
        virtual ~ClientRecord();

		///
		/// Zwraca ID serwera do ktorego podlaczony jest klient.
		/// @return Id serwera do ktorego podlaczony jest klient.
		int GetClientServerId() const;

		///
		/// Ustawia ID serwera do ktorego podlaczony jest klient.
		/// @param[in] clientServerId Id serwera do ktorego podlaczony jest klient.
		void SetClientServerId(int & clientServerId);

		///
		/// Pobiera namiastke klienta.
		/// @return Namiastka klienta.
		IClientServer * GetClientRemoteInstance() const;

		///
		/// Ustawia namiastke klienta.
		/// @param[in] clientRemoteInstance Namiastka klienta.
		void SetClientRemoteInstance(IClientServer * clientRemoteInstance);

		///
		/// Pobiera dostepnosc klienta.
		/// @return Dostepnosc klienta.
		Enability GetEnability() const;

		///
		/// Ustawia dostepnosc klienta.
		/// param[in] enability Dostepnosc klienta.
		void SetEnability(Enability & enability);
};

#endif
