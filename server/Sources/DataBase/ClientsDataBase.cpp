#include "ClientsDataBase.h"

///
/// Konstruktor bezparametrowy.
ClientsDataBase::ClientsDataBase() 
{

}

///
/// Konstruktor kopiujacy.
/// @param[in] arg Baza danych do skopiowania.
ClientsDataBase::ClientsDataBase(const ClientsDataBase & arg) 
{
	this->_records = arg._records;
}

///
/// Operator przypisania.
/// param[in] arg Baza danych ktora chcemy przypisac.
ClientsDataBase & ClientsDataBase::operator =(const ClientsDataBase & arg) 
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
ClientsDataBase * ClientsDataBase::GetInstance()
{
	static ClientsDataBase * _db = new ClientsDataBase();

	return _db;
}

///
/// Destruktor.
ClientsDataBase::~ClientsDataBase() 
{

}

///
/// Zwraca rekord po podaniu rekord id.
/// @param[in] recordId Identyfikator rekordu.
/// @return Rekord o podanym idetyfikatorze.
const ClientRecord & ClientsDataBase::GetRecord(int recordId) 
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
std::vector<ClientRecord> ClientsDataBase::GetAllRecords() 
{
	boost::mutex::scoped_lock sl(_mutex);
	std::vector<ClientRecord> v;
	
	if ( _records.size() != 0 )
		for(std::map<int, ClientRecord>::iterator i = this->_records.begin(); i != this->_records.end(); i++)
			v.push_back((*i).second);

	return v;
}

///
/// Dodaje rekord do bazy danych.
/// param[in] record Record do wstawienia.
/// @return ???
int ClientsDataBase::InsertRecord(const ClientRecord & record) 
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
int ClientsDataBase::DeleteRecord(int recordId) 
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
int ClientsDataBase::ModifyRecord(const ClientRecord & record) 
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
int ClientsDataBase::Close()
{
	return 1;
}

///
/// Inicjalizuje baze danych.
/// @return ???
int ClientsDataBase::Initialize()
{
	return 1;
}

///
/// Zwraca liczbe elementow.
/// @return Liczba elementow w kolekcji.
int ClientsDataBase::Size()
{
	return this->_records.size();
}

///
/// Usuwa wszystkie rekordy z bazy.
void ClientsDataBase::Clear()
{
	boost::mutex::scoped_lock sl(_mutex);

	this->_records.clear();
}

///
/// Znajdz rekord klienta.
/// @param[in] address Adres do wyszukania rekordu.
/// @return ID wyszukanego rekordu. -1 gdy nie znajdzie.
int ClientsDataBase::Find(const struct DomainData::Address & address)
{
	boost::mutex::scoped_lock sl(_mutex);

	if ( this->_records.size() != 0 )
		for(std::map<int, ClientRecord>::iterator i = this->_records.begin(); i != this->_records.end(); i++)
			if ( (*i).second.GetAddress().name == address.name )
				return (*i).second.GetRecordId();

	return -1;
}

///
/// Znajduje aktywnego klienta w bazie danych.
/// @return Id rekordu aktywnego klienta. -1 gdy nie znajdzie.
int ClientsDataBase::FindActiveClient()
{
	boost::mutex::scoped_lock sl(_mutex);

	if ( _records.size() != 0 )
		for(std::map<int, ClientRecord>::iterator i = this->_records.begin(); i != this->_records.end(); i++)
			if ( (*i).second.GetEnability().mode_ == DomainData::active )
				return (*i).second.GetRecordId();

	return -1;
}

///
/// Znajduje aktywnego klienta na danym serwerze.
/// @return Id rekordu aktywnego klienta. -1 gdy nie znajdzie.
int ClientsDataBase::FindActiveClientOnServer(int serverId)
{
	boost::mutex::scoped_lock sl(_mutex);

	if ( _records.size() != 0 )
		for(std::map<int, ClientRecord>::iterator i = this->_records.begin(); i != this->_records.end(); i++)
			if ( (*i).second.GetEnability().mode_ == DomainData::active && (*i).second.GetClientServerId() == serverId )
				return (*i).second.GetRecordId();

	return -1;
}

///
/// Przeciazony operator wypisu bazy danych do strumienia.
/// @param[in] os Strumien wyjsciowy.
/// @param[in] db Baza danych.
/// @return Strumien wyjsciowy.
std::ostream & operator<<(std::ostream & os, const ClientsDataBase & db)
{
	int k = 1;
	for(std::map<int, ClientRecord>::const_iterator i = db._records.begin(); i != db._records.end(); i++, ++k)
	{
		os	<< k << "\t" 
			<< (*i).second.GetRecordId() << "\t"
			<< (*i).second.GetAddress().localization.in()
			<< std::endl;
	}

	return os;
}