#include "ServerDataBase.h"

///
/// Konstruktor bezparametrowy.
ServerDataBase::ServerDataBase() 
{
	// Inicjalizacja loggera.
	_logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("ServerDataBase"));
	_logger->setLevel(log4cxx::Level::getAll());
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

	LOG4CXX_DEBUG(_logger, "Pobieranie rekordu o id: " << recordId);

	if ( this->_records.count(recordId) != 0 )
	{
		LOG4CXX_DEBUG(_logger, "Znaleziono rekord. Address.localization: " << _records[recordId].GetAddress().localization.in() );
		return _records[recordId];
	}
	else
	{
		LOG4CXX_ERROR(_logger, "Nie znaleziono rekordu.");

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

	LOG4CXX_DEBUG(_logger, "Pobieranie wszystkich rekordow.");
	
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

	LOG4CXX_DEBUG(_logger, "Wstawianie rekordu. Address.localization: " << record.GetAddress().localization.in() );

	if ( this->_records.count(record.GetRecordId()) == 0 )
	{
		this->_records[record.GetRecordId()] = record;
		return 1;
	}
	else
	{
		LOG4CXX_ERROR(_logger, "Rekord o podanym id juz istnieje");

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

	LOG4CXX_DEBUG(_logger, "Usuwanie rekordu o id: " << recordId );

	if ( this->_records.count(recordId) != 0 )
	{
		this->_records.erase(recordId);

		LOG4CXX_DEBUG(_logger, "Rekord usunieto." );

		return 1;
	}
	else
	{
		LOG4CXX_ERROR(_logger, "Nie znaleziono rekordu!" );

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

	LOG4CXX_DEBUG(_logger, "Modyfikacja rekordu. (new)Address.localization: " << record.GetAddress().localization.in() );

	if ( this->_records.count(record.GetRecordId()) != 0 )
	{
		_records[record.GetRecordId()] = record;

		LOG4CXX_DEBUG(_logger, "Rekord zmodyfikowano.");

		return 1;
	}
	else
	{
		LOG4CXX_ERROR(_logger, "Nie zmodyfikowano rekordu!");

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
/// Usuwa wszystkie rekordy z bazy.
void ServerDataBase::Clear()
{
	boost::mutex::scoped_lock sl(_mutex);

	this->_records.clear();
}

///
/// Znajdz rekord servera.
/// @param[in] address Adres do wyszukania rekordu.
/// @return ID wyszukanego rekordu.
int ServerDataBase::Find(const struct DomainData::Address & address)
{
	boost::mutex::scoped_lock sl(_mutex);

	LOG4CXX_DEBUG(_logger, "Szukanie po strukturze Address. Address.name: " << address.name.in() << " Address.localization: " << address.localization.in() );

	if ( _records.size() != 0 )
		for(std::map<int, ServerRecord>::iterator i = this->_records.begin(); i != this->_records.end(); i++)
			if ( strcmp((*i).second.GetAddress().localization.in(), address.localization.in()) == 0 )
			{
				LOG4CXX_DEBUG(_logger, "Znaleziono rekord!");
				return (*i).second.GetRecordId();
			}

	LOG4CXX_DEBUG(_logger, "Nie znaleziono rekordu!");
	return -1;
}

///
/// Przeciazony operator wypisu bazy danych do strumienia.
/// @param[in] os Strumien wyjsciowy.
/// @param[in] db Baza danych.
/// @return Strumien wyjsciowy.
std::ostream & operator<<(std::ostream & os, const ServerDataBase & db)
{
	int k = 1;
	for(std::map<int, ServerRecord>::const_iterator i = db._records.begin(); i != db._records.end(); i++, ++k)
	{
		os	<< k << "\t" 
			<< (*i).second.GetRecordId() << "\t"
			<< (*i).second.GetAddress().localization.in()
			<< std::endl;
	}

	return os;
}
