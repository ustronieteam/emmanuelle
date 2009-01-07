#ifndef DATABASE_H
#define DATABASE_H

#include "Record.h"
#include <vector>
#include <map>

using namespace std;

///
/// DataBase
/// @brief Baza danych trzymajaca rekordy.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.06
///
class DataBase
{
	private:

		map<int, Record> _records;

    public:

        ///
		/// Konstruktor bezparametrowy.
        DataBase();

        ///
		/// Konstruktor kopiujacy.
		/// @param[in] arg Baza danych do skopiowania.
        DataBase(DataBase & arg);

        ///
		/// Operator przypisania.
		/// param[in] arg Baza danych ktora chcemy przypisac.
        DataBase & operator =(const DataBase & arg);

        ///
		/// Destruktor.
        ~DataBase();

		///
		/// Zwraca rekord po podaniu rekord id.
		/// @param[in] recordId Identyfikator rekordu.
		/// @return Rekord o podanym idetyfikatorze.
        Record GetRecord(int recordId);

		///
		/// Zwraca wszystkie rekordy z bazy danych.
		/// @return Wektor ze wszystkimi rekordami.
		std::vector<Record> GetAllRecords();

        ///
		/// Dodaje rekord do bazy danych.
		/// param[in] record Record do wstawienia.
		/// @return ???
        int InsertRecord(const Record & record);

        ///
		/// Usuwa rekord o podanym id z bazy danych.
		/// param[in] recordId ID rekordu ktory ma byc usuniety.
		/// @return ???
        int DeleteRecord(int recordId);

        ///
		/// Modyfikuje rekord w bazie danych.
		/// param[in] record Record ze zmodyfikowanymi danymi.
		/// @return ???
        int ModifyRecord(const Record & record);

		///
		/// Zamyka baze danych.
		/// @return ???
        int Close();

        ///
		/// Inicjalizuje baze danych.
		/// @return ???
        int Initialize();
};

#endif
