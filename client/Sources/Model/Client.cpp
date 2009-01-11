#include "Client.h"

const std::string Client::configFileName = "client.config";
///
///@author Marian Szczykulski
///@date 2009-01-11
///@brief Konstruktor klienta
Client::Client() 
{
	logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("Client"));
	logger->setLevel(log4cxx::Level::getAll());		
	readServerAddress();
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
		serverAddress.localization.out() = CORBA::string_dup(servAddr.c_str());//???
		file.close();
	}
	catch(std::exception &exc)
	{
		LOG4CXX_ERROR(logger, "Blad podczas parsowania pliku konfiguracyjnego. Wyjatek: "<<exc.what() ); 
		file.close();
	}
	
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
///@brief	Metoda umo¿liwiajaca pod³¹czenie sie klienta do danego serwera
int Client::ConnectToServer() 
{
	if(serverAddress.localization.in() != NULL && strcmp(serverAddress.localization.in(),"")!=0)
	{//Adres jest ustawiony

	}
	else
	{//Rzuc wyjatek nie mozna podlaczys sie do serwera

	}
    return 0;
}

int Client::Disconnect() 
{
    return 0;
}

int Client::SendMessage() 
{
    return 0;
}
int Client::AddMessageObserver(IRemoteObserver & messageObserver) 
{
    return 0;
}
