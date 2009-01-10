#include "Observers/RemoteClientConnectedObserver.h"
//Begin section for file RemoteClientConnectedObserver.cpp
//TODO: Add definitions that you want preserved
//End section for file RemoteClientConnectedObserver.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientConnectedObserver::RemoteClientConnectedObserver() 
{
    this->clientsDataBase  = boost::shared_ptr<ClientsDataBase>();
    this->serverDataBase  = boost::shared_ptr<ServerDataBase>();
}
RemoteClientConnectedObserver::RemoteClientConnectedObserver(boost::shared_ptr<ServerDataBase> & servDB, boost::shared_ptr<ClientsDataBase> & clientsDB)
{
	this->clientsDataBase = clientsDataBase;
    this->serverDataBase  = serverDataBase;
}
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientConnectedObserver::RemoteClientConnectedObserver(RemoteClientConnectedObserver & arg) 
{
    this->clientsDataBase = arg.clientsDataBase;
    this->serverDataBase = arg.serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientConnectedObserver & RemoteClientConnectedObserver::operator =(const RemoteClientConnectedObserver & arg) 
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
RemoteClientConnectedObserver::~RemoteClientConnectedObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
boost::shared_ptr<ClientsDataBase> & RemoteClientConnectedObserver::get_clientsDataBase() 
{
    //TODO Auto-generated method stub
    return clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteClientConnectedObserver::set_clientsDataBase(boost::shared_ptr<ClientsDataBase> & clientsDataBase) 
{
	this->clientsDataBase = clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
boost::shared_ptr<ServerDataBase> & RemoteClientConnectedObserver::get_serverDataBase() 
{
    //TODO Auto-generated method stub
    return serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
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
	struct DomainData::Address clientAddr = observerData.getClientAddress();
	int clientId = clientsDataBase->Find(clientAddr);
	ClientRecord clRec = clientsDataBase->GetRecord(clientId);

	//if(clientId <= 0)
	//{ //Klienta nie ma w bazie - trzeba dodac go do bazy i oznaczyc jego status jako aktywny

	//	//Utworz nowy rekord klienta
	//	ClientRecord newClient=ClientRecord(/*wstaw dane klienta*/);
	//	//Wstaw dane

	//	//Dodaj rekord do bazy
	//	int status = clientsDataBase->InsertRecord(newClient);
	//	if(status<0)
	//	{
	//		LOG4CXX_ERROR(logger, "Blad wstawiania nowego rekordu do bazy klientow");
	//		return -1;
	//	}
	//	//powiadom wszystkie serwery o zmianie
	//	//Zawsze wysylamy clientStatusChanged z danymi klienta i jego statusem
	//}
	//else
	//{ //Klient jest w bazie - trzeba zmienic status i rozeslac zdarzenie statusChanged

	//	//Znajdz rekord klienta
	//	ClientRecord clRec = clientsDataBase->GetRecord(clientId);

	//	//Modyfikuj odpowiednie pole rekordu

	//	//Aktualizuj bazkê
	//	int status = clientsDataBase->ModifyRecord(clRec);
	//	if(status<0)
	//	{
	//		LOG4CXX_ERROR(logger, "Blad modyfikowania rekordu w bazie klientow");
	//		return -2;
	//	}
	//	//Powiadom wszystkie serwery o zmianie.

	//}
	//Zdobadz wlasne id

	struct DomainData::Address localServAddr = Server::GetMyIP();
	int localId = serverDataBase->Find(localServAddr); //wlasne id w bazie
	if(localId<=0)
	{
		LOG4CXX_ERROR(logger,"Brak danych o lokalnym serwerze w bazie");
		return -2;
	}
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
				if(Server::connectToServer(servRec.GetAddress().localization.in(), orb, remInstance)==false)
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
			remoteServer->ClientStatusChanged(clientAddr, enab);//Dodac dane z observer Data
			LOG4CXX_INFO(logger, "Wiadomosc wyslana do serwera nr"<<serverCounter);
		}
		catch(std::exception & exc) //chyba rzuca jakis wyjatek??
		{
			LOG4CXX_ERROR(logger, "Blad wysylania do serwera: " << servRec.GetAddress().localization.in()<< ".Powod: "<< exc.what());
		}
		serverCounter++;

	}

	LOG4CXX_INFO(logger, "Koniec przetwarzania logiki RemoteClientConnectedObserver");
	return serverCounter;
}