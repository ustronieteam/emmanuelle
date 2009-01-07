#ifndef SERVERDATABASE_H
#define SERVERDATABASE_H

#include <boost/thread/mutex.hpp>
#include <vector>
#include <map>

#include "ServerRecord.h"

///
/// ClientDataBase
/// @brief Baza danych trzymajaca rekordy informacyjne o klientach.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.06
///
class ServerDataBase
{
	private:

		///
		/// Mutex, gdy¿ kolekcja uzywana w róznych w¹tkach.
		boost::mutex _mutex;

		///
		/// Kolekcja trzymajaca rekordy.
		std::map<int, ServerRecord> _records;

        ///
		/// Konstruktor bezparametrowy.
        ServerDataBase();

        ///
		/// Konstruktor kopiujacy.
		/// @param[in] arg Baza danych do skopiowania.
        ServerDataBase(const ServerDataBase & arg);

        ///
		/// Operator przypisania.
		/// param[in] arg Baza danych ktora chcemy przypisac.
        ServerDataBase & operator =(const ServerDataBase & arg);

	public:

		///
		/// Zwraca baze danych (singleton)
		/// @return Baza danych
		static ServerDataBase * GetInstance();

        ///
		/// Destruktor.
        virtual ~ServerDataBase();

		///
		/// Zwraca rekord po podaniu rekord id.
		/// @param[in] recordId Identyfikator rekordu.
		/// @return Rekord o podanym idetyfikatorze.
        const ServerRecord & GetRecord(int recordId);

		///
		/// Zwraca wszystkie rekordy z bazy danych.
		/// @return Wektor ze wszystkimi rekordami.
		std::vector<ServerRecord> GetAllRecords();

        ///
		/// Dodaje rekord do bazy danych.
		/// param[in] record Record do wstawienia.
		/// @return ???
        int InsertRecord(const ServerRecord & record);

        ///
		/// Usuwa rekord o podanym id z bazy danych.
		/// param[in] recordId ID rekordu ktory ma byc usuniety.
		/// @return ???
        int DeleteRecord(int recordId);

        ///
		/// Modyfikuje rekord w bazie danych.
		/// param[in] record Record ze zmodyfikowanymi danymi.
		/// @return ???
        int ModifyRecord(const ServerRecord & record);

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
		/// Znajdz rekord servera.
		/// @param[in] address Adres do wyszukania rekordu.
		/// @return ID wyszukanego rekordu.
		int Find(struct DomainData::Address & address);
};

#endif
