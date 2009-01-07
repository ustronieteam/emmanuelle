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
	int clientId = clientsDataBase->Find(clientAddr/*dane z observerData*/); //Dodac dane!!!
	Record clRec;
	try
	{
		clRec = clientsDataBase->GetRecord(clientId);
	}
	catch(std::exception & exc)
	{
		LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas pobierania rekordu recordId: "<<clientId<< ".Powod: "<< exc.what());
		return -2;
	}

	//Aktualizuj wpis clRec

	int status = clientsDataBase->ModifyRecord(clRec);
	if(status < 0)
	{
		LOG4CXX_ERROR(logger, "Blad modyfikowania rekordu w bazie");
		return -1;
	}

	//    2)Powiadom wszystkie serwery o zmianie

	std::vector<Record> allRecords = serverDataBase->GetAllRecords();

	//Utworz licznik serwerow z listy
	int serverCounter =0;
	//	3) Do ka¿dego serwera z listy dodaj nowy serwer (AddServer)
	LOG4CXX_INFO(logger, "Petla wysylania wiadomosci do serwerow");
	for(std::vector<Record>::iterator it = allRecords.begin();
			it != allRecords.end();	//Dopuki nie doszlismy do konca zbioru
				it++)
	{
		Record rec = (*it);
		ServerRecord servRec = *(dynamic_cast<ServerRecord *>(&rec));
		IServerServer_var remoteServer = servRec.GetServerRemoteInstance();
		try
		{
			struct DomainData::Enability enab = observerData.getClientEnability();
			remoteServer->ClientStatusChanged(clientAddr, enab/*dodac dane z observerData*/);//Dodac dane z observer Data
			LOG4CXX_INFO(logger, "Wiadomosc wyslana do serwera nr"<<serverCounter);
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
