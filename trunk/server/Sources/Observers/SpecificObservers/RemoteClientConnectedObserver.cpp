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
	LOG4CXX_INFO(logger, "Przetwarzanie logiki RemoteClientConnectedObserver");

	//    1) Znajdz klienta
	int clientId = clientsDataBase->Find(/*Dane z observerData*/);
	if(clientId <= 0)
	{ //Klienta nie ma w bazie - trzeba dodac go do bazy i oznaczyc jego status jako aktywny

		//Utworz nowy rekord klienta
		Record newClient=Record(/*wstaw dane klienta*/);
		//Wstaw dane

		//Dodaj rekord do bazy
		int status = clientsDataBase->InsertRecord(newClient);
		if(status<0)
		{
			LOG4CXX_ERROR(logger, "Blad wstawiania nowego rekordu do bazy klientow");
			return -1;
		}
		//powiadom wszystkie serwery o zmianie
		//Zawsze wysylamy clientStatusChanged z danymi klienta i jego statusem
	}
	else
	{ //Klient jest w bazie - trzeba zmienic status i rozeslac zdarzenie statusChanged

		//Znajdz rekord klienta
		Record clRec = clientsDataBase->GetRecord(clientId);

		//Modyfikuj odpowiednie pole rekordu

		//Aktualizuj bazkê
		int status = clientsDataBase->ModifyRecord(clRec);
		if(status<0)
		{
			LOG4CXX_ERROR(logger, "Blad modyfikowania rekordu w bazie klientow");
			return -2;
		}
		//Powiadom wszystkie serwery o zmianie.

	}
	std::vector<Record> allRecords = serverDataBase->get_record();

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
		IServerServer remoteServer = servRec.getRemoteInstance();
		try
		{
			remoteServer.ClientStatusChanged(/*dane*/);//Dodac dane z observer Data
			LOG4CXX_INFO(logger, "Wiadomosc wyslana do serwera nr"<<serverCounter);
		}
		catch(std::exception & exc) //chyba rzuca jakis wyjatek??
		{
			LOG4CXX_ERROR(logger, "Blad wysylania do serwera: " << serverCounter);
		}
		serverCounter++;

	}
	//    2) zaktualizuj jego wpis w bazie (dodaj jak nie ma)
	//    3) Powiadom wszystkie serwery o zmianie

	LOG4CXX_INFO(logger, "Koniec przetwarzania logiki RemoteClientConnectedObserver");
	return serverCounter;
}