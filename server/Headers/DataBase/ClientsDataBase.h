#ifndef CLIENTSDATABASE_H
#define CLIENTSDATABASE_H

#include "ClientRecord.h"

#include <vector>
#include <map>

///
/// ClientDataBase
/// @brief Baza danych trzymajaca rekordy informacyjne o klientach.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.06
///
class ClientsDataBase
{
		friend std::ostream & operator<<(std::ostream & os, const ClientsDataBase & db);

	private:

		///
		/// Obiekt logowania.
		///
		log4cxx::LoggerPtr _logger;

		///
		/// Mutex, gdy¿ kolekcja uzywana w róznych w¹tkach.
		boost::mutex _mutex;

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

		///
		/// Usuwa wszystkie rekordy z bazy.
		void Clear();

		/// Metody szukajace.

		///
		/// Znajdz rekord klienta po adresie.
		/// @param[in] address Adres do wyszukania rekordu.
		/// @return ID wyszukanego rekordu. -1 gdy nie znajdzie.
		//int Find(const struct DomainData::Address & address);

		///
		/// Znajdz rekord klienta po uzytkowniku
		/// @param[in] user Uzytkownik do wyszukania rekordu.
		/// @return ID wyszukanego rekordu. -1 gdy nie znajdzie.
		int Find(const struct DomainData::User & user);

		///
		/// Znajduje aktywnego klienta w bazie danych.
		/// @return Id rekordu aktywnego klienta. -1 gdy nie znajdzie.
		int FindActiveClient();

		///
		/// Znajduje aktywnego klienta na danym serwerze.
		/// @return Id rekordu aktywnego klienta. -1 gdy nie znajdzie.
		int FindActiveClientOnServer(int serverId);
};

///
/// Przeciazony operator wypisu bazy danych do strumienia.
/// @param[in] os Strumien wyjsciowy.
/// @param[in] db Baza danych.
/// @return Strumien wyjsciowy.
std::ostream & operator<<(std::ostream & os, const ClientsDataBase & db);

#endif
