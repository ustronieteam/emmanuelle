#include "ServerDataBase.h"

ServerDataBase::ServerDataBase() 
{
	// Inicjalizacja loggera.
	_logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("ServerDataBase"));
	_logger->setLevel(LOGLEVEL);
}

ServerDataBase::ServerDataBase(const ServerDataBase & arg) 
{
	this->_records = arg._records;
}

ServerDataBase & ServerDataBase::operator =(const ServerDataBase & arg) 
{
	if ( this != &arg )
	{
		this->_records = arg._records;
	}

	return *this;
}

ServerDataBase * ServerDataBase::GetInstance()
{
	static ServerDataBase * _db = new ServerDataBase();

	return _db;
}

ServerDataBase::~ServerDataBase() 
{

}

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

		//"Brak rekordu o podanym ID!");
		throw std::exception();
	}
}

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

		//"Record o podanym ID jest juz w bazie danych!");
		throw std::exception();
	}
}

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

		throw std::exception();
	}
}

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

		//"Brak rekordu o podanym ID!");
		throw std::exception();
	}
}

int ServerDataBase::Close()
{
	return 1;
}

int ServerDataBase::Initialize()
{
	return 1;
}

int ServerDataBase::Size()
{
	return this->_records.size();
}

void ServerDataBase::Clear()
{
	boost::mutex::scoped_lock sl(_mutex);

	this->_records.clear();
}

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
