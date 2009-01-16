#include "Observers/RemoteClientConnectedObserver.h"

RemoteClientConnectedObserver::RemoteClientConnectedObserver() 
{
    this->clientsDataBase  = boost::shared_ptr<ClientsDataBase>();
    this->serverDataBase  = boost::shared_ptr<ServerDataBase>();
}
RemoteClientConnectedObserver::RemoteClientConnectedObserver(boost::shared_ptr<ServerDataBase> & servDB, boost::shared_ptr<ClientsDataBase> & clientsDB)
{
	this->clientsDataBase = clientsDB;
    this->serverDataBase  = servDB;
}

RemoteClientConnectedObserver::RemoteClientConnectedObserver(RemoteClientConnectedObserver & arg) 
{
    this->clientsDataBase = arg.clientsDataBase;
    this->serverDataBase = arg.serverDataBase;
}


RemoteClientConnectedObserver & RemoteClientConnectedObserver::operator =(const RemoteClientConnectedObserver & arg) 
{

    if (this != &arg)
    {
        this->clientsDataBase = arg.clientsDataBase;
        this->serverDataBase = arg.serverDataBase;
    }
	return *this;
}


RemoteClientConnectedObserver::~RemoteClientConnectedObserver() 
{
}


boost::shared_ptr<ClientsDataBase> & RemoteClientConnectedObserver::get_clientsDataBase() 
{
    
    return clientsDataBase;
}


void RemoteClientConnectedObserver::set_clientsDataBase(boost::shared_ptr<ClientsDataBase> & clientsDataBase) 
{
	this->clientsDataBase = clientsDataBase;
}


boost::shared_ptr<ServerDataBase> & RemoteClientConnectedObserver::get_serverDataBase() 
{
    
    return serverDataBase;
}


void RemoteClientConnectedObserver::set_serverDataBase(boost::shared_ptr<ServerDataBase> & serverDataBase) 
{
	this->serverDataBase = serverDataBase;
}
//@author Marian Szczykulski
//@date 29-12-2008
//@note Obserwator podlaczenia sie nowego klienta
//@brief Glowna funkcja obserwatora, odpowiedzialna za logike przetwarzania.
//@param[in] Dane obserwatora potrzebne do podejmowania decyzji podczas przetwarzania
//@return ??
int RemoteClientConnectedObserver::Refresh(RemoteObserverData observerData)
{
	if(observerData.get_eventType()!=CLIENT_CONNECTED)
		return 0; 
	//Utworz logike watku
	RemoteClientConnectedObserverLogicRunnable threadLogic(serverDataBase,clientsDataBase,observerData);
	//Utworz i uruchom watki
	boost::thread threadRemoteClientConnectedObserver(threadLogic);
	return 0;
}
//@author Marian Szczykulski
//@date 29-12-2008
//@note Logika watku
//@brief Zawiera logike przetwarzania ktora moze byc uruchomiona w odzielnym watku
int RemoteClientConnectedObserverLogicRunnable::operator()()
{
	//Konieczne dane w observerData: clientAddr (reszte wyciagniemy z bazy)
	LOG4CXX_INFO(logger, "Przetwarzanie logiki RemoteClientConnectedObserver");

	//    1) Znajdz klienta
	//struct DomainData::User clientDestData = observerData.getDestinationUser();
	struct DomainData::User clientUserData = observerData.getClientUserData();
	int clientId = 0;
	ClientRecord clRec;
	try
	{
		clientId = clientsDataBase->Find(clientUserData);
		clRec = clientsDataBase->GetRecord(clientId);
	}
	catch(std::exception & e)
	{
		LOG4CXX_FATAL(logger, "Nieoczekiwany wyjatek podczas pobierania rekordu z bazy(powinna go wstawic zdalna metoda connect)"<<e.what());
		return -1;
	}

	struct DomainData::Address localServAddr = Server::GetMyIP();
	int localId = serverDataBase->Find(localServAddr); //wlasne id w bazie
	if(localId<=0)
	{
		LOG4CXX_FATAL(logger,"Brak danych o lokalnym serwerze w bazie");
		return -2;
	}
	std::vector<ServerRecord> allRecords = serverDataBase->GetAllRecords();

	//Utworz licznik serwerow z listy
	int serverCounter =0;
	//	3) Do ka¿dego serwera z listy dodaj nowy serwer (AddServer)
	LOG4CXX_DEBUG(logger, "Petla wysylania wiadomosci do serwerow");
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
					serverDataBase->ModifyRecord(servRec);
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
			DomainData::Address clientAddr = clRec.GetAddress();

			remoteServer->ClientStatusChanged(clientUserData, clientAddr, enab, localServAddr);
			LOG4CXX_INFO(logger, "Wiadomosc wyslana do serwera nr"<<serverCounter);
		}
		catch(CORBA::SystemException & exc) 
		{
			LOG4CXX_ERROR(logger, "Blad wysylania do serwera: " << servRec.GetAddress().localization.in()<< ".Powod: "<< exc._name());
		}
		catch(std::exception & exc)
		{
			LOG4CXX_ERROR(logger, "Blad wysylania do serwera: " << servRec.GetAddress().localization.in()<< ".Powod: "<< exc.what());
		}
		serverCounter++;

	}

	LOG4CXX_INFO(logger, "Koniec przetwarzania logiki RemoteClientConnectedObserver");
	return serverCounter;
}