#ifndef CLIENTSDATABASE_H
#define CLIENTSDATABASE_H

//#include <boost/thread/mutex.hpp>
#include <vector>
#include <map>

#include "ClientRecord.h"

///
/// ClientDataBase
/// @brief Baza danych trzymajaca rekordy informacyjne o klientach.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.06
///
class ClientsDataBase
{
	private:

		///
		/// Mutex, gdy¿ kolekcja uzywana w róznych w¹tkach.
		//boost::mutex _mutex;

		///
		/// Kolekcja trzymajaca rekordy.
		std::map<int, ClientRecord> _records;

        ///
		/// Konstruktor bezparametrowy.
        ClientsDataBase();

        ///
		/// Konstruktor kopiujacy.
		/// @param[in] arg Baza danych do skopiowania.
        ClientsDataBase(const ClientsDataBase & arg);

        ///
		/// Operator przypisania.
		/// param[in] arg Baza danych ktora chcemy przypisac.
        ClientsDataBase & operator =(const ClientsDataBase & arg);

	public:

		///
		/// Zwraca baze danych (singleton)
		/// @return Baza danych
		static ClientsDataBase * GetInstance();

        ///
		/// Destruktor.
        virtual ~ClientsDataBase();

		///
		/// Zwraca rekord po podaniu rekord id.
		/// @param[in] recordId Identyfikator rekordu.
		/// @return Rekord o podanym idetyfikatorze.
        const ClientRecord & GetRecord(int recordId);

		///
		/// Zwraca wszystkie rekordy z bazy danych.
		/// @return Wektor ze wszystkimi rekordami.
		std::vector<ClientRecord> GetAllRecords();

        ///
		/// Dodaje rekord do bazy danych.
		/// param[in] record Record do wstawienia.
		/// @return ???
        int InsertRecord(const ClientRecord & record);

        ///
		/// Usuwa rekord o podanym id z bazy danych.
		/// param[in] recordId ID rekordu ktory ma byc usuniety.
		/// @return ???
        int DeleteRecord(int recordId);

        ///
		/// Modyfikuje rekord w bazie danych.
		/// param[in] record Record ze zmodyfikowanymi danymi.
		/// @return ???
        int ModifyRecord(const ClientRecord & record);

		///
		/// Zamyka baze danych.
		/// @return ???
		virtual int Close();

		///
		/// Inicjalizuje baze danych.
		/// @return ???
		virtual int Initialize();

		///
		/// Zwraca liczbe elementow.
		/// @return Liczba elementow w kolekcji.
		int Size();

		/// Metody szukajace.

		///
		/// Znajdz rekord klienta.
		/// @param[in] address Adres do wyszukania rekordu.
		/// @return ID wyszukanego rekordu. -1 gdy nie znajdzie.
		int Find(struct DomainData::Address & address);

		///
		/// Znajduje aktywnego klienta w bazie danych.
		/// @return Id rekordu aktywnego klienta. -1 gdy nie znajdzie.
		int FindActiveClient();

		///
		/// Znajduje aktywnego klienta na danym serwerze.
		/// @return Id rekordu aktywnego klienta. -1 gdy nie znajdzie.
		int FindActiveClientOnServer(int serverId);
};

#endif
