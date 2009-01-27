#include "ClientsDataBase.h"

ClientsDataBase::ClientsDataBase() 
{
	// Inicjalizacja loggera.
	_logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("ClientsDataBase"));
	_logger->setLevel(LOGLEVEL);
}

ClientsDataBase::ClientsDataBase(const ClientsDataBase & arg) 
{
	this->_records = arg._records;
}

ClientsDataBase & ClientsDataBase::operator =(const ClientsDataBase & arg) 
{
	if ( this != &arg )
	{
		this->_records = arg._records;
	}

	return *this;
}

ClientsDataBase * ClientsDataBase::GetInstance()
{
	static ClientsDataBase * _db = new ClientsDataBase();

	return _db;
}

boost::shared_ptr<ClientsDataBase> ClientsDataBase::GetInstnace()
{
	static boost::shared_ptr<ClientsDataBase> _database(new ClientsDataBase());

	return _database;
}

ClientsDataBase::~ClientsDataBase() 
{

}

const ClientRecord & ClientsDataBase::GetRecord(int recordId) 
{
	boost::mutex::scoped_lock sl(_mutex);

	LOG4CXX_DEBUG(_logger, "Pobieranie rekordu o id: " << recordId);

	if ( this->_records.count(recordId) != 0 )
	{
		LOG4CXX_DEBUG(_logger, "Znaleziono rekord. User.name: " << _records[recordId].GetUser().name.in() );
		return _records[recordId];
	}
	else
	{
		LOG4CXX_ERROR(_logger, "Nie znaleziono rekordu.");

		throw std::exception();//"Brak rekordu o podanym ID!");
	}
}

std::vector<ClientRecord> ClientsDataBase::GetAllRecords() 
{
	boost::mutex::scoped_lock sl(_mutex);

	LOG4CXX_DEBUG(_logger, "Pobieranie wszystkich rekordow.");

	std::vector<ClientRecord> v;
	
	if ( _records.size() != 0 )
		for(std::map<int, ClientRecord>::iterator i = this->_records.begin(); i != this->_records.end(); i++)
			v.push_back((*i).second);

	return v;
}

int ClientsDataBase::InsertRecord(const ClientRecord & record) 
{
	boost::mutex::scoped_lock sl(_mutex);

	LOG4CXX_DEBUG(_logger, "Wstawianie rekordu. User.name: " << record.GetUser().name.in() );

	if ( this->_records.count(record.GetRecordId()) == 0 )
	{
		// Triger
		// Address.Name = User.Name
		ClientRecord rec(record);
		DomainData::Address adr = rec.GetAddress();
		DomainData::User usr = rec.GetUser();
		adr.name = CORBA::string_dup(usr.name.in());
		rec.SetAddress(adr);

		this->_records[record.GetRecordId()] = rec;
		return 1;
	}
	else
	{
		LOG4CXX_ERROR(_logger, "Rekord o podanym id juz istnieje");

		//"Record o podanym ID jest juz w bazie danych!");
		throw std::exception();
	}
}

int ClientsDataBase::DeleteRecord(int recordId) 
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

		//"Brak rekordu o podanym ID!");
		throw std::exception();
	}
}

int ClientsDataBase::ModifyRecord(const ClientRecord & record) 
{
	boost::mutex::scoped_lock sl(_mutex);

	LOG4CXX_DEBUG(_logger, "Modyfikacja rekordu. (new)User.name: " << record.GetUser().name.in() );

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

int ClientsDataBase::Close()
{
	return 1;
}

int ClientsDataBase::Initialize()
{
	return 1;
}

int ClientsDataBase::Size()
{
	return this->_records.size();
}

void ClientsDataBase::Clear()
{
	boost::mutex::scoped_lock sl(_mutex);

	this->_records.clear();
}

int ClientsDataBase::Find(const struct DomainData::User & user)
{
	boost::mutex::scoped_lock sl(_mutex);

	LOG4CXX_DEBUG(_logger, "Szukanie po strukturze User. User.name: " << user.name.in() );

	if ( this->_records.size() != 0 )
		for(std::map<int, ClientRecord>::iterator i = this->_records.begin(); i != this->_records.end(); i++)
			if ( strcmp((*i).second.GetUser().name.in(), user.name.in()) == 0 )
			{
				LOG4CXX_DEBUG(_logger, "Znaleziono rekord!");
				return (*i).second.GetRecordId();
			}

	LOG4CXX_DEBUG(_logger, "Nie znaleziono rekordu!");
	return -1;
}

int ClientsDataBase::FindActiveClient()
{
	boost::mutex::scoped_lock sl(_mutex);

	LOG4CXX_DEBUG(_logger, "Szukanie aktywnych klientow.");

	if ( _records.size() != 0 )
		for(std::map<int, ClientRecord>::iterator i = this->_records.begin(); i != this->_records.end(); i++)
			if ( (*i).second.GetEnability().mode_ == DomainData::active )
			{
				LOG4CXX_DEBUG(_logger, "Znaleziono rekord!");
				return (*i).second.GetRecordId();
			}

	LOG4CXX_DEBUG(_logger, "Nie znaleziono rekordu!");	
	return -1;
}

int ClientsDataBase::FindActiveClientOnServer(int serverId)
{
	boost::mutex::scoped_lock sl(_mutex);

	LOG4CXX_DEBUG(_logger, "Szukanie aktywnych klientow na serwerze o id: " << serverId);

	if ( _records.size() != 0 )
		for(std::map<int, ClientRecord>::iterator i = this->_records.begin(); i != this->_records.end(); i++)
			if ( (*i).second.GetEnability().mode_ == DomainData::active && (*i).second.GetClientServerId() == serverId )
			{
				LOG4CXX_DEBUG(_logger, "Znaleziono rekord!");
				return (*i).second.GetRecordId();
			}

	LOG4CXX_DEBUG(_logger, "Nie znaleziono rekordu!");	
	return -1;
}


int ClientsDataBase::FindByAddress(const struct DomainData::Address & address)
{
	boost::mutex::scoped_lock sl(_mutex);

	LOG4CXX_DEBUG(_logger, "Szukanie po strukturze Address. Address.name: " << address.name.in() << " Address.localization: " << address.localization.in() );

	if ( _records.size() != 0 )
		for(std::map<int, ClientRecord>::iterator i = this->_records.begin(); i != this->_records.end(); i++)
			if ( strcmp((*i).second.GetAddress().localization.in(), address.localization.in()) == 0 )
			{
				LOG4CXX_DEBUG(_logger, "Znaleziono rekord!");
				return (*i).second.GetRecordId();
			}

	LOG4CXX_DEBUG(_logger, "Nie znaleziono rekordu!");
	return -1;
}

std::ostream & operator<<(std::ostream & os, const ClientsDataBase & db)
{
	int k = 1;

	os  << "Nr\tId\tAdres.Loc.\tSt.\tSrv.\tUser.Name\n";

	for(std::map<int, ClientRecord>::const_iterator i = db._records.begin(); i != db._records.end(); i++, ++k)
	{
		os	<< k << "\t" 
			<< (*i).second.GetRecordId() << '\t'
			<< (*i).second.GetAddress().localization.in() << '\t'
			<< (*i).second.GetEnability().status << '\t'
			<< (*i).second.GetClientServerId() << '\t'
			<< (*i).second.GetUser().name.in()
			<< std::endl;
	}

	return os;
}
