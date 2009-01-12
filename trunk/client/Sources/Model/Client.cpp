#include "Client.h"

const std::string Client::configFileName = config::configFileName;
const int Client::defaultPortNumber = 6666;
///
///@author Marian Szczykulski
///@date 2009-01-11
///@brief Konstruktor klienta
Client::Client() 
{
	logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("Client"));
	logger->setLevel(log4cxx::Level::getAll());		
	readServerAddress();
	port = defaultPortNumber;
}
Client::Client(DomainData::Address servAddr)
{
	logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("Client"));
	logger->setLevel(log4cxx::Level::getAll());		
	serverAddress = servAddr;
	port = defaultPortNumber;
}
Client::~Client() 
{

}
///
///@author Marian Szczykulski
///@date 2009-01-11
///@brief czyta adres serwera z pliku konfiguracyjnego
void Client::readServerAddress()
{
	std::string servAddr="";
	po::options_description configOption( "Opcje pliku konfiguracyjnego" );
	configOption.add_options()
			   ("serverAddress", po::value<std::string>(&servAddr),
     "Adres Ip servera domyslnego") 
	;
	po::variables_map vm;
	std::ifstream file;
	file.open(configFileName.c_str());

	try
	{
		store( parse_config_file(file,configOption), vm );
		po::notify( vm );
		serverAddress.localization = CORBA::string_dup(servAddr.c_str());//???
		file.close();
	}
	catch(std::exception &exc)
	{
		LOG4CXX_ERROR(logger, "Blad podczas parsowania pliku konfiguracyjnego. Wyjatek: "<<exc.what() ); 
		file.close();
	}
	
}
///
///@author Marian Szczykulski
///@date 2009-01-11
///@brief  Pobiera zdaln� instancje servera(jezeli juz jakas jest to ja usuwa)
bool Client::getRemoteServerInstance()
{
	//Instancja musi byc niezainicjalizowana
	try
	{
		if(! CORBA::is_nil(connectedServerInstance))
		{
			CORBA::release(connectedServerInstance);
		}
		if(! CORBA::is_nil(orb))
		{
			orb->destroy();
		}
	}
	catch(CORBA::SystemException & e)
	{
		LOG4CXX_ERROR(logger, "Wyjatek podczas resetowania zdalnej instancji"<<e._name());
		return false;
	}
	LOG4CXX_DEBUG(logger, "Pozyskiwanie zdalnej instancji servera");
	try
	{
		std::cout << "serv addr: " << serverAddress.localization.in();
		if(connectToServerClient(serverAddress.localization.in(), orb, connectedServerInstance)==false)
		{
			LOG4CXX_ERROR(logger, "Nie mozna pozyskac zdalnej instancji servera");
			return false;
		}
		else
		{
			LOG4CXX_DEBUG(logger, "Pozyskano zdalna instancje serwera");
			return true;
		}
	}
	catch(CORBA::SystemException & e)
	{
		LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas pozyskiwania zdalnej instancji: "<<e._name());
			return false;
	}
	return false;
}

int Client::AddFileObserver(IRemoteObserver & fileObserver) 
{
    return 0;
}

int Client::SendPackage() 
{
    return 0;
}
///
///@author Marian Szczykulski
///@date	2009-01-10
///@brief	Metoda umo�liwiajaca pod��czenie sie klienta do danego serwera
///@brief	rzuca wyjatek jak nie uda sie podlaczyc
///@return	1 jak udalo sie podlaczyc
///@return	0 jak nie udalo sie podlaczyc ale mo�na sprobowac jeszcze raz
///			w przeciwnym wypadku rzucany jest wyjatek
int Client::ConnectToServer() 
{
	if(serverAddress.localization.in() != NULL && strcmp(serverAddress.localization.in(),"")!=0)
	{//Adres jest ustawiony
		if(!getRemoteServerInstance())
		{
			LOG4CXX_ERROR(logger, "Nie mozna podlaczyc sie do wybranego serwera");
			std::exception ex("Nie mo�na podlaczyc sie do serwera");
			throw ex;
		}
		DomainData::Address *servAddr = NULL;
		DomainData::User user;
		user.name = clientName.c_str();
		user.number = clientNumber;
		try
		{
			LOG4CXX_INFO(logger, "Wywolywanie metody zdalnej connect()");
			servAddr = connectedServerInstance->Connect(serverAddress,mode, user);
			LOG4CXX_DEBUG(logger, "Metoda zdalna connect wywolana");
			if(strcmp(servAddr->localization.in(),serverAddress.localization.in())!=0)
			{
				if(servAddr!=NULL)
				{
					LOG4CXX_INFO(logger, "Connect zwrocil wartosc rozna od NULL");
					serverAddress = *servAddr;
					return 0; //Kontroler moze jeszcze raz sprobowac sie polaczyc
				}
				std::exception ex("Nie mo�na podlaczyc sie do wybranego serwera");
				throw ex;
			}
			else
			{
				LOG4CXX_INFO(logger, "Podlaczono do servera: "<<serverAddress.localization.in());
				return 1;
			}
		}
		catch(CORBA::SystemException &e)
		{
			LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas podlaczania sie do serwera");
			std::exception ex("Nie mo�na podlaczyc sie do serwera");
			throw ex;
		}

	}
	else
	{//Rzuc wyjatek nie mozna podlaczys sie do serwera
		std::exception ex("Nie mo�na podlaczyc sie do serwera. Podany adres jest nie dostepny");
		throw ex;
	}

    std::exception ex("Nie mo�na podlaczyc sie do serwera. Podany adres jest bledny(pusty)");
	throw ex;
}


///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief Metoda rozlaczajaca sie z serwerem
int Client::Disconnect() 
{
	if(CORBA::is_nil(connectedServerInstance))
	{//nie jestesmy do niczego podlaczeni
		return -2;
	}
	try
	{
		connectedServerInstance->Disconnect();
	}
	catch(CORBA::SystemException & e)
	{
		LOG4CXX_DEBUG(logger, "Nie udalo sie rozlaczyc. Wyjatek podczas wywolywania metody zdalnej");
		return -1;
	}
    return 0;
}
///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief Wysylanie wiadomosci do klienta(poprzez serwer)
///@param[in] recAddr	adresat wiadomosci
///@param[in] msg		wiadomosc
///@return				status (-2 zdalna instancja serwera nie zainicjowana,
///								-1 blad podczas wywolywania zdalnej metody serwera)
int Client::SendMessage(DomainData::Address recAddr, DomainData::Message msg) 
{
	if(CORBA::is_nil(connectedServerInstance))
	{//nie jestesmy podlaczeni do zdalnej instancji serwera
		LOG4CXX_DEBUG(logger, "Wysylanie wiadomosci przy niezainicjowanej zdalnej instancji serwera");
		return -2;
	}
	try
	{
		connectedServerInstance->SendMessageW(recAddr, msg);
	}
	catch(CORBA::SystemException & e)
	{
		LOG4CXX_ERROR(logger, "wyjatek ze zdalnej instancji serwera podczas wysylania wiadomosci");
		return -1;
	}
    return 0;
}
int Client::AddMessageObserver(IRemoteObserver & messageObserver) 
{
    return 0;
}