#include "DataBase.h"

///
/// Konstruktor bezparametrowy.
DataBase::DataBase() 
{

}

///
/// Konstruktor kopiujacy.
/// @param[in] arg Baza danych do skopiowania.
DataBase::DataBase(DataBase & arg) 
{

}

///
/// Operator przypisania.
/// param[in] arg Baza danych ktora chcemy przypisac.
DataBase & DataBase::operator =(const DataBase & arg) 
{
	return const_cast<DataBase &>(arg);
}

///
/// Destruktor.
DataBase::~DataBase() 
{

}

///
/// Zwraca rekord po podaniu rekord id.
/// @param[in] recordId Identyfikator rekordu.
/// @return Rekord o podanym idetyfikatorze.
Record DataBase::GetRecord(int recordId) 
{
    Record r;
    return r;
}

///
/// Zwraca wszystkie rekordy z bazy danych.
/// @return Wektor ze wszystkimi rekordami.
std::vector<Record> DataBase::GetAllRecords() 
{
    vector<Record> v;
    return v;
}

///
/// Dodaje rekord do bazy danych.
/// param[in] record Record do wstawienia.
/// @return ???
int DataBase::InsertRecord(Record record) 
{
    return 0;
}

///
/// Usuwa rekord o podanym id z bazy danych.
/// param[in] recordId ID rekordu ktory ma byc usuniety.
/// @return ???
int DataBase::DeleteRecord(int recordId) 
{
    return 0;
}

///
/// Modyfikuje rekord w bazie danych.
/// param[in] record Record ze zmodyfikowanymi danymi.
/// @return ???
int DataBase::ModifyRecord(Record record) 
{
    return 0;
}
