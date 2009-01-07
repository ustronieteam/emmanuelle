#include "ServerDataBase.h"

///
/// Konstruktor bezparametrowy.
ServerDataBase::ServerDataBase() 
{

}

///
/// Konstruktor kopiujacy.
/// @param[in] arg Baza danych do skopiowania.
ServerDataBase::ServerDataBase(const ServerDataBase & arg) 
{
	this->_records = arg._records;
}

///
/// Operator przypisania.
/// param[in] arg Baza danych ktora chcemy przypisac.
ServerDataBase & ServerDataBase::operator =(const ServerDataBase & arg) 
{
	if ( this != &arg )
	{
		this->_records = arg._records;
	}

	return *this;
}

///
/// Zwraca baze danych (singleton)
/// @return Baza danych
ServerDataBase * ServerDataBase::GetInstance()
{
	static ServerDataBase * _db = new ServerDataBase();

	return _db;
}

///
/// Destruktor.
ServerDataBase::~ServerDataBase() 
{

}


///
/// Zwraca rekord po podaniu rekord id.
/// @param[in] recordId Identyfikator rekordu.
/// @return Rekord o podanym idetyfikatorze.
const ServerRecord & ServerDataBase::GetRecord(int recordId) 
{
	boost::mutex::scoped_lock sl(_mutex);

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
std::vector<ServerRecord> ServerDataBase::GetAllRecords() 
{
	boost::mutex::scoped_lock sl(_mutex);
	std::vector<ServerRecord> v;
	
	if ( _records.size() != 0 )
		for(std::map<int, ServerRecord>::iterator i = this->_records.begin(); i != this->_records.end(); i++)
			v.push_back((*i).second);

	return v;
}

///
/// Dodaje rekord do bazy danych.
/// param[in] record Record do wstawienia.
/// @return ???
int ServerDataBase::InsertRecord(const ServerRecord & record) 
{
	boost::mutex::scoped_lock sl(_mutex);

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
int ServerDataBase::DeleteRecord(int recordId) 
{
	boost::mutex::scoped_lock sl(_mutex);

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
int ServerDataBase::ModifyRecord(const ServerRecord & record) 
{
	boost::mutex::scoped_lock sl(_mutex);

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

///
/// Zamyka baze danych.
/// @return ???
int ServerDataBase::Close()
{
	return 1;
}

///
/// Inicjalizuje baze danych.
/// @return ???
int ServerDataBase::Initialize()
{
	return 1;
}

///
/// Zwraca liczbe elementow.
/// @return Liczba elementow w kolekcji.
int ServerDataBase::Size()
{
	return this->_records.size();
}

///
/// Znajdz rekord servera.
/// @param[in] address Adres do wyszukania rekordu.
/// @return ID wyszukanego rekordu.
int ServerDataBase::Find(struct DomainData::Address & address)
{
	boost::mutex::scoped_lock sl(_mutex);

	if ( _records.size() != 0 )
		for(std::map<int, ServerRecord>::iterator i = this->_records.begin(); i != this->_records.end(); i++)
			if ( (*i).second.GetAddress().localization == address.localization )
				return (*i).second.GetRecordId();

	return -1;
}
