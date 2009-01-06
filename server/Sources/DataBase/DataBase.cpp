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
	this->_records = arg._records;
}

///
/// Operator przypisania.
/// param[in] arg Baza danych ktora chcemy przypisac.
DataBase & DataBase::operator =(const DataBase & arg) 
{
	if ( this != &arg )
	{
		this->_records = arg._records;
	}

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
	if ( this->_records.count(recordId) != 0 )
	{
		return _records[recordId];
	}
	else
	{
		std::exception ex("Brak rekordu o podanym ID!");
		throw ex;
	}
}

///
/// Zwraca wszystkie rekordy z bazy danych.
/// @return Wektor ze wszystkimi rekordami.
std::vector<Record> DataBase::GetAllRecords() 
{
	vector<Record> v;
	
	if ( _records.size() != 0 )
		for(map<int, Record>::iterator i = this->_records.begin(); i != this->_records.end(); i++)
			v.push_back((*i).second);

	return v;
}

///
/// Dodaje rekord do bazy danych.
/// param[in] record Record do wstawienia.
/// @return ???
int DataBase::InsertRecord(Record record) 
{
	if ( this->_records.count(record.GetRecordId()) == 0 )
	{
		this->_records[record.GetRecordId()] = record;
		return 1;
	}
	else
	{
		std::exception ex("Record o podanym ID jest juz w bazie danych!");
		throw ex;
	}
}

///
/// Usuwa rekord o podanym id z bazy danych.
/// param[in] recordId ID rekordu ktory ma byc usuniety.
/// @return ???
int DataBase::DeleteRecord(int recordId) 
{
	if ( this->_records.count(recordId) != 0 )
	{
		this->_records.erase(recordId);
		return 1;
	}
	else
	{
		std::exception ex("Brak rekordu o podanym ID!");
		throw ex;
	}
}

///
/// Modyfikuje rekord w bazie danych.
/// param[in] record Record ze zmodyfikowanymi danymi.
/// @return ???
int DataBase::ModifyRecord(Record record) 
{
	if ( this->_records.count(record.GetRecordId()) != 0 )
	{
		_records[record.GetRecordId()] = record;
		return 1;
	}
	else
	{
		std::exception ex("Brak rekordu o podanym ID!");
		throw ex;
	}
}
