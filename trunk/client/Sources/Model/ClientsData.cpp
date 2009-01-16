#include "ClientsData.h"

const std::string ClientsData::configFileName = config::configFileName;

///
///@author Marian Szczykulski
///@brief Konstruktor jedno argumentowy.
///@param[in] con	flaga okreslajaca czy kolekcja ma byc wielowatkowa (domyslnie jest wielowatkowa)
///
ClientsData::ClientsData(bool con)
{
	readClientName();
	isConcurrent = con;
}

///
///@author Marian Szczykulski
///@brief BLokuje mutex (jezeli kolekcja jest wielowatkowa)
///
void ClientsData::lock_mutex()
{
	if(isConcurrent)
		_mutex.lock();
}

///
///@author Marian Szczykulski
///@brief odblokowuje mutex (jezeli kolekcja jest wielowatkowa)
///
void ClientsData::unlock_mutex()
{
	if(isConcurrent)
		_mutex.unlock();
}

///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief Wirtualny destruktor
///
ClientsData::~ClientsData() 
{
}

///
///@author Marian Szczykulski
///@date 2009-01-12
///@return		aktualnie przechowywana lista kontaktow (jest juz posortowana alfabetycznie po nazwach klientow)
///
std::vector<ContactRecord> ClientsData::GetContactsList() const  
{//Nie synchronizuje (bo metoda moze byc czasochlonna) a nie spowoduje to 
 //desynchronizacji danych w bazie
	std::vector<ContactRecord> v;
	if ( _records.size() != 0 )
	for(std::map<std::string, ContactRecord>::const_iterator i = this->_records.begin(); i != this->_records.end(); i++)
		v.push_back((*i).second);
    return v;
}

///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief	Usuwa kontakt z bazy (jezeli konieczne jest synchronizowana)
///@param[in]	usr		dane klienta ktorego chcemy usunac
///@return		1		jezeli udalo sie dodac
///		
int ClientsData::DeleteContact(DomainData::User usr) 
{
	lock_mutex();
	if ( this->_records.count(usr.name.in()) != 0 )
	{
		this->_records.erase(usr.name.in());
		unlock_mutex();
		return 1;
	}
	else
	{
		unlock_mutex();
		ContactNotFoundException e;
		throw e;
	}
}

///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief	Dodaje kontakt do bazy (jezeli konieczne jest synchronizowana)
///@param[in]	usr		dane klienta ktore chcemy dodac do listy kontaktow
///@return		1		jezeli udalo sie dodac
///						lub rzuca wyjatek jak sie nie uda
///
int ClientsData::AddContact(DomainData::User usr) 
{
	lock_mutex();
	if ( this->_records.count(usr.name.in()) == 0 )
	{
		ContactRecord contRec;
		contRec.userDesc = usr;
		contRec.isAvailable = false;

		this->_records[usr.name.in()] = contRec;
		unlock_mutex();
		return 0;
	}
	else
	{
		unlock_mutex();
		ContactAlreadyExistsException ex;
		throw ex;
	}
}

///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief Znajduje record poprzez nazwe i zwraca go
///@param[in]	name	nazwa klienta, ktorego szukamy
///@return				Rekord poszukiwanego klienta
///
const ContactRecord & ClientsData::FindByName(std::string name)
{
	lock_mutex();
	if(_records.count(name) == 0)
	{
		ContactNotFoundException e;
		unlock_mutex();
		throw e;
	}
	else
	{
		/*const ContactRecord cr = _records[name];
		return cr;*/
		unlock_mutex();
		return _records[name];
	}

}

///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief czyta nazwe klienta z pliku konfiguracyjnego
///
void ClientsData::readClientName()
{
	lock_mutex();
	std::string clName="";
	long clNumber = 0;
	po::options_description configOption( "Opcje pliku konfiguracyjnego" );
	configOption.add_options()
			   ("clientName", po::value<std::string>(&clName),
     "Adres Ip servera domyslnego")
				("clientNumber", po::value<long>(&clNumber),
     "Adres Ip servera domyslnego") 
	;
	po::variables_map vm;
	std::ifstream file;
	file.open(configFileName.c_str());

	try
	{
		store( parse_config_file(file,configOption), vm );
		po::notify( vm );
		file.close();
		ownRecord.userDesc.name = CORBA::string_dup(clName.c_str());
		ownRecord.userDesc.number = clNumber;
		ownRecord.isAvailable = true;
	}
	catch(std::exception &)
	{
		file.close();
		unlock_mutex();
	}
	unlock_mutex();
}

///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief	Zwraca wlasny rekord z danymi
///@return	wlasny rekord z danymi
///
const ContactRecord & ClientsData::GetOwnRecord() const
{
	return ownRecord;
}

///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief setter nazwy lokalnego klienta
///
void ClientsData::SetOwnName(const char * c)
{
	lock_mutex();
	ownRecord.userDesc.name = CORBA::string_dup(c);
	unlock_mutex();
}

///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief setter numeru lokalnego klienta
///
void ClientsData::SetOwnNumber(long l)
{
	lock_mutex();
	ownRecord.userDesc.number = l;
	unlock_mutex();
}

///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief setter dostepnosci lokalnego klienta
///
void ClientsData::SetMyAvailability(bool b)
{
	lock_mutex();
	ownRecord.isAvailable = b;
	unlock_mutex();
}

bool ClientsData::ModifyRecord(const ContactRecord & cr)
{
	lock_mutex();

	if ( this->_records.count(cr.userDesc.name.in())!=0)
	{
		_records[cr.userDesc.name.in()] = cr;
		unlock_mutex();
		return true;
	}
	else
	{

		ContactNotFoundException e;
		unlock_mutex();
		throw e;
	}
	return true;
}