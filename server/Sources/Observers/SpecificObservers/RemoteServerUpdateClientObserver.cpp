#include "Observers/RemoteServerUpdateClientObserver.h"
//Begin section for file RemoteServerUpdateClientObserver.cpp
//TODO: Add definitions that you want preserved
//End section for file RemoteServerUpdateClientObserver.cpp


RemoteServerUpdateClientObserver::RemoteServerUpdateClientObserver() 
{
    this->clientsDataBase  = boost::shared_ptr<ClientsDataBase>();
    this->serverDataBase  = boost::shared_ptr<ServerDataBase>();
}
RemoteServerUpdateClientObserver::RemoteServerUpdateClientObserver(boost::shared_ptr<ServerDataBase> & servDB, boost::shared_ptr<ClientsDataBase> & clientsDB) 
{
    //TODO Auto-generated method stub
	this->clientsDataBase = clientsDB;
    this->serverDataBase = servDB;
}
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteServerUpdateClientObserver::RemoteServerUpdateClientObserver(RemoteServerUpdateClientObserver & arg) 
{
    //TODO Auto-generated method stub
    this->clientsDataBase = arg.clientsDataBase;
    this->serverDataBase = arg.serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteServerUpdateClientObserver & RemoteServerUpdateClientObserver::operator =(const RemoteServerUpdateClientObserver & arg) 
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
RemoteServerUpdateClientObserver::~RemoteServerUpdateClientObserver() 
{
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
boost::shared_ptr<ClientsDataBase> & RemoteServerUpdateClientObserver::get_clientsDataBase() 
{
    return clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteServerUpdateClientObserver::set_clientsDataBase(boost::shared_ptr<ClientsDataBase> & clientsDataBase) 
{
	this->clientsDataBase = clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
boost::shared_ptr<ServerDataBase> & RemoteServerUpdateClientObserver::get_serverDataBase() 
{
    return serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteServerUpdateClientObserver::set_serverDataBase(boost::shared_ptr<ServerDataBase> & serverDataBase) 
{
	this->serverDataBase = serverDataBase;
}
//@author Marian Szczykulski
//@date 29-12-2008
//@note Obserwator aktualizacji danych klienta
//@brief Glowna funkcja obserwatora, odpowiedzialna za logike przetwarzania.
//@param[in] Dane obserwatora potrzebne do podejmowania decyzji podczas przetwarzania
//@return ??
int RemoteServerUpdateClientObserver::Refresh(RemoteObserverData observerData)
{
	if(observerData.get_eventType()!=SERVER_UPDATE_CLIENT)
		return 0;
	//Utworz logike watku
	RemoteServerUpdateClientObserverLogicRunnable threadLogic(serverDataBase, clientsDataBase, observerData);
	//Utworz i uruchom watki
	boost::thread threadRemoteServerUpdateClient(threadLogic);

	return 0;
}
//@author Marian Szczykulski
//@date 29-12-2008
//@note Logika watku
//@brief Zawiera logike przetwarzania ktora moze byc uruchomiona w odzielnym watku
int RemoteServerUpdateClientObserverLogicRunnable::operator()()
{
	LOG4CXX_INFO(logger, "Przetwarzanie logiki RemoteServerUpdateClientObserver");

	//    1)Znajdz klienta
	struct DomainData::User clientData = observerData.getClientUserData();
	int clientId = clientsDataBase->Find(clientData);
	if(clientId <=0)
	{//Klienta nie ma w bazie => podlaczyl sie nowy klient
		ClientRecord newClientRecord = ClientRecord(/*Dane z observerData*/);
		//Utworz odpowiedni rekord

		int status = clientsDataBase->InsertRecord(newClientRecord);
		if(status <0)
		{
			LOG4CXX_ERROR(logger, "Blad wstawiania nowego rekordu do bazy klientow");
			return -1;
		}
	}
	else
	{//Dane klienta sa juz w bazie, nalezy je tylko zmodyfikowac
		ClientRecord oldRecord;
		try
		{
			oldRecord = clientsDataBase->GetRecord(clientId);
		}
		catch(std::exception & exc)
		{
			LOG4CXX_ERROR(logger, "Nie znaleziono rekordu o podanym id clientId: "<<clientId<< ".Powod: "<< exc.what());
			return -2;
		}
		ClientRecord newRecord = oldRecord;
	

		//    2) Wprowaz zmiany w jego rekordzie
	
		/* 
			MODYFIKUJ newRecord na podstawie observerData
		*/
	
		clientsDataBase->ModifyRecord(newRecord); //Czy zmieniaja sie tylko statusy?
	}//Nie trzeba przesylac dalej bo to jest juz przeslane
	//	/*Na podstawie observerData
	//	if(Dane od innego serwera) //Nie przesylaj dalej
	//	{
	//		return 0;
	//	}
	//	//Przeslij dalej, bo dane pochodza od klienta 
	//	//(wiec trzeba powiadomic tez inne serwery)
	//*/
	////    3)Powiadom wszystkie serwery o zmianie

	////Pobierz wszystkie serwery z bazy
	//std::vector<Record> allRecords = serverDataBase->get_record();

	////Utworz licznik serwerow z listy
	//int serverCounter =0;
	////	3) Do ka¿dego serwera z listy dodaj nowy serwer (AddServer)
	//LOG4CXX_INFO(logger, "Petla wysylania wiadomosci do serwerow");
	//for(std::vector<Record>::iterator it = allRecords.begin();
	//		it != allRecords.end();	//Dopuki nie doszlismy do konca zbioru
	//			it++)
	//{
	//	Record rec = (*it);
	//	ServerRecord servRec = *(dynamic_cast<ServerRecord *>(&rec));
	//	IServerServer remoteServer = servRec.getRemoteInstance();
	//	try
	//	{
	//		remoteServer.ClientStatusChanged();//Dodac dane z observer Data
	//		LOG4CXX_INFO(logger, "Wiadomosc wyslana do serwera nr"<<serverCounter);
	//	}
	//	catch(std::exception & exc) //chyba rzuca jakis wyjatek??
	//	{
	//		LOG4CXX_ERROR(logger, "Blad wysylania do serwera: " << serverCounter);
	//	}
	//	serverCounter++;

	//}

	LOG4CXX_INFO(logger, "Koniec przetwarzania logiki RemoteServerUpdateClientObserver");
	return 1;
}
