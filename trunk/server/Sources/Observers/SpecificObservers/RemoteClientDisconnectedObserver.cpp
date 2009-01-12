#include "Observers/RemoteClientDisconnectedObserver.h"
//Begin section for file RemoteClientDisconnectedObserver.cpp
//TODO: Add definitions that you want preserved
//End section for file RemoteClientDisconnectedObserver.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientDisconnectedObserver::RemoteClientDisconnectedObserver() 
{
    this->clientsDataBase  = boost::shared_ptr<ClientsDataBase>();
    this->serverDataBase  = boost::shared_ptr<ServerDataBase>();
}
RemoteClientDisconnectedObserver::RemoteClientDisconnectedObserver(boost::shared_ptr<ServerDataBase> & servDB, boost::shared_ptr<ClientsDataBase> & clientsDB)
{
	this->clientsDataBase = clientsDataBase;
    this->serverDataBase  = serverDataBase;
}
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientDisconnectedObserver::RemoteClientDisconnectedObserver(RemoteClientDisconnectedObserver & arg) 
{
    //TODO Auto-generated method stub
    this->clientsDataBase = arg.clientsDataBase;
    this->serverDataBase = arg.serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientDisconnectedObserver & RemoteClientDisconnectedObserver::operator =(const RemoteClientDisconnectedObserver & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->clientsDataBase = arg.clientsDataBase;
        this->serverDataBase = arg.serverDataBase;
    }
	return *this;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientDisconnectedObserver::~RemoteClientDisconnectedObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
boost::shared_ptr<ClientsDataBase> & RemoteClientDisconnectedObserver::get_clientsDataBase() 
{
    //TODO Auto-generated method stub
    return clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteClientDisconnectedObserver::set_clientsDataBase(boost::shared_ptr<ClientsDataBase> & clientsDataBase) 
{
	this->clientsDataBase = clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
boost::shared_ptr<ServerDataBase> & RemoteClientDisconnectedObserver::get_serverDataBase() 
{
    //TODO Auto-generated method stub
    return serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteClientDisconnectedObserver::set_serverDataBase(boost::shared_ptr<ServerDataBase> & serverDataBase) 
{
	this->serverDataBase = serverDataBase;
}
//@author Marian Szczykulski
//@date 30-12-2008
//@note Obserwator odlaczenia sie klienta
//@brief Glowna funkcja obserwatora, odpowiedzialna za logike przetwarzania.
//@param[in] Dane obserwatora potrzebne do podejmowania decyzji podczas przetwarzania
//@return ??
int RemoteClientDisconnectedObserver::Refresh(RemoteObserverData observerData)
{
	if(observerData.get_eventType()!=CLIENT_DISCONNECTED)
		return 0; 
	//Utworz logike watku
	RemoteClientDisconnectedObserverLogicRunnable threadLogic(serverDataBase, clientsDataBase, observerData);
	//Utworz i uruchom watki
	boost::thread threadRemoteClientDisconnected(threadLogic);

	return 0;
}
//@author Marian Szczykulski
//@date 01-01-2009
//@note Logika watku
//@brief Zawiera logike przetwarzania ktora moze byc uruchomiona w odzielnym watku
int RemoteClientDisconnectedObserverLogicRunnable::operator()()
{
	LOG4CXX_INFO(logger, "Przetwarzanie logiki RemoteClientDisconnectedObserver");

	//    1) Zaktualizuj wpis o kliencie(roz³¹cz)
	//Znajdz klienta w bazie klientow
	struct DomainData::Address clientAddr = observerData.getClientAddress();
	int clientId = clientsDataBase->Find(clientAddr); 
	if(clientId <=0)
	{
		LOG4CXX_ERROR(logger, "Rozlaczanego klienta nie ma w bazie!!!");
		return -1;
	}
	ClientRecord clRec;
	try
	{
		clRec = clientsDataBase->GetRecord(clientId);
	}
	catch(std::exception & exc)
	{
		LOG4CXX_ERROR(logger, "Zlapano nieoczekiwany wyjatek: " <<exc.what() );
		return -2;
	}
	struct DomainData::Address localServAddr = Server::GetMyIP();
	int localId = serverDataBase->Find(localServAddr); //wlasne id w bazie
	if(localId<=0)
	{
		LOG4CXX_ERROR(logger,"Brak danych o lokalnym serwerze w bazie");
		return -2;
	}
	//    2)Powiadom wszystkie serwery o zmianie
	std::vector<ServerRecord> allRecords = serverDataBase->GetAllRecords();

	//Utworz licznik serwerow z listy
	int serverCounter =0;
	//	3) Do ka¿dego serwera z listy dodaj nowy serwer (AddServer)
	LOG4CXX_INFO(logger, "Petla wysylania wiadomosci do serwerow");
	for(std::vector<ServerRecord>::iterator it = allRecords.begin();
			it != allRecords.end();	//Dopuki nie doszlismy do konca zbioru
				it++)
	{
		ServerRecord servRec = (*it);
		if(servRec.GetRecordId()==localId)//Samemu sobie juz nie przesylamy
		{
			continue;
		}
		IServerServer_var remoteServer = servRec.GetServerRemoteInstance();
		if(CORBA::is_nil(remoteServer))
		{
			LOG4CXX_DEBUG(logger, "Pozyskiwanie zdalnej instancji servera");
			CORBA::ORB_var orb;
			IServerServer_var remInstance;
			try
			{
				if(Server::connectToServerServer(servRec.GetAddress().localization.in(), orb, remInstance)==false)
				{
					//TODO: zastanowic sie czy tu nie usunac serwer
					LOG4CXX_ERROR(logger, "Nie mozna pozyskac zdalnej instancji servera");
					continue; //Nie mozna wywolac zdalnej metody
				}
				else
				{
					LOG4CXX_DEBUG(logger, "Pozyskano zdalna instancje serwera");
					servRec.SetServerRemoteInstance(remInstance);
					servRec.SetBroker(orb);
					remoteServer = remInstance;
				}
			}
			catch(CORBA::SystemException & e)
			{
				//TODO Usuwanie
				LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas pozyskiwania zdalnej instancji: "<<e._name());
				continue;
			}
		}
		try
		{
			struct DomainData::Enability enab = clRec.GetEnability();
			struct DomainData::User usr = observerData.getClientUserData();			//remoteServer->ClientStatusChanged(clientAddr, enab);
			LOG4CXX_INFO(logger, "Wiadomosc wyslana do serwera "<<it->GetAddress().localization.in());
		}
		catch(std::exception & exc) //chyba rzuca jakis wyjatek??
		{
			LOG4CXX_ERROR(logger, "Blad wysylania do serwera: " << serverCounter<< ".Powod: "<< exc.what());
		}
		serverCounter++;

	}

	LOG4CXX_INFO(logger, "Koniec przetwarzania logiki RemoteClientDisconnectedObserver");
	return serverCounter;
}
