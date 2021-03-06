#ifndef SERVERDATABASE_H
#define SERVERDATABASE_H

#include "ServerRecord.h"

#include <vector>
#include <map>

///
/// ClientDataBase
/// @brief Baza danych trzymajaca rekordy informacyjne o klientach.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.06
///
class ServerDataBase
{
		friend std::ostream & operator<<(std::ostream & os, const ServerDataBase & db);

	private:

		///
		/// Obiekt logowania.
		///
		log4cxx::LoggerPtr _logger;

		///
		/// Mutex, gdy� kolekcja uzywana w r�znych w�tkach.
		///
		boost::mutex _mutex;

		///
		/// Kolekcja trzymajaca rekordy.
		///
		std::map<int, ServerRecord> _records;

        ///
		/// Konstruktor bezparametrowy.
		///
        ServerDataBase();

        ///
		/// Konstruktor kopiujacy.
		/// @param[in] arg Baza danych do skopiowania.
		///
        ServerDataBase(const ServerDataBase & arg);

        ///
		/// Operator przypisania.
		/// param[in] arg Baza danych ktora chcemy przypisac.
		///
        ServerDataBase & operator =(const ServerDataBase & arg);

	public:

		///
		/// Zwraca baze danych (singleton)
		/// @return Baza danych
		///
		static ServerDataBase * GetInstance();

		static boost::shared_ptr<ServerDataBase> GetInstnace();

        ///
		/// Destruktor.
		///
        virtual ~ServerDataBase();

		///
		/// Zwraca rekord po podaniu rekord id.
		/// @param[in] recordId Identyfikator rekordu.
		/// @return Rekord o podanym idetyfikatorze.
		///
        const ServerRecord & GetRecord(int recordId);

		///
		/// Zwraca wszystkie rekordy z bazy danych.
		/// @return Wektor ze wszystkimi rekordami.
		///
		std::vector<ServerRecord> GetAllRecords();

        ///
		/// Dodaje rekord do bazy danych.
		/// param[in] record Record do wstawienia.
		/// @return 1 jesli OK, wpp -1
		///
        int InsertRecord(const ServerRecord & record);

        ///
		/// Usuwa rekord o podanym id z bazy danych.
		/// param[in] recordId ID rekordu ktory ma byc usuniety.
		/// @return 1 jesli OK, wpp -1
		///
        int DeleteRecord(int recordId);

        ///
		/// Modyfikuje rekord w bazie danych.
		/// param[in] record Record ze zmodyfikowanymi danymi.
		/// @return 1 jesli OK, wpp -1
		///
        int ModifyRecord(const ServerRecord & record);

		///
		/// Zamyka baze danych.
		/// @return 1 jesli OK, wpp -1
		///
		virtual int Close();

		///
		/// Inicjalizuje baze danych.
		/// @return 1 jesli OK, wpp -1
		///
		virtual int Initialize();

		///
		/// Zwraca liczbe elementow.
		/// @return Liczba elementow w kolekcji.
		///
		int Size();

		///
		/// Usuwa wszystkie rekordy z bazy.
		///
		void Clear();

		/// Metody szukajace.

		///
		/// Znajdz rekord servera.
		/// @param[in] address Adres do wyszukania rekordu.
		/// @return ID wyszukanego rekordu.
		///
		int Find(const struct DomainData::Address & address);
};

///
/// Przeciazony operator wypisu bazy danych do strumienia.
/// @param[in] os Strumien wyjsciowy.
/// @param[in] db Baza danych.
/// @return Strumien wyjsciowy.
///
std::ostream & operator<<(std::ostream & os, const ServerDataBase & db);

#endif
