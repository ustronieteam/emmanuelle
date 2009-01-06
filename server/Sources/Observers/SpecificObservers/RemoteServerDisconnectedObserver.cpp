#include "Observers/RemoteServerDisconnectedObserver.h"
//Begin section for file RemoteServerDisconnectedObserver.cpp
//TODO: Add definitions that you want preserved
//End section for file RemoteServerDisconnectedObserver.cpp


RemoteServerDisconnectedObserver::RemoteServerDisconnectedObserver() 
{
	this->serverDataBase = boost::shared_ptr<ServerDataBase>();
}
RemoteServerDisconnectedObserver::RemoteServerDisconnectedObserver(boost::shared_ptr<ServerDataBase> & sptr)
{
	 this->serverDataBase = sptr;
}
RemoteServerDisconnectedObserver::RemoteServerDisconnectedObserver(RemoteServerDisconnectedObserver & arg) 
{
    this->serverDataBase = arg.serverDataBase;
}

RemoteServerDisconnectedObserver & RemoteServerDisconnectedObserver::operator =(const RemoteServerDisconnectedObserver & arg) 
{
    if (this != &arg)
    {
        this->serverDataBase = arg.serverDataBase;
    }
	return *this;
}
RemoteServerDisconnectedObserver::~RemoteServerDisconnectedObserver() 
{

}

boost::shared_ptr<ServerDataBase> & RemoteServerDisconnectedObserver::get_serverDataBase() 
{
    return serverDataBase;
}

void RemoteServerDisconnectedObserver::set_serverDataBase(boost::shared_ptr<ServerDataBase> & serverDataBase) 
{
	this->serverDataBase = serverDataBase;
}
//@author Marian Szczykulski
//@date 29-12-2008
//@note Obserwator rozlaczenia sie serwera
//@brief Glowna funkcja obserwatora, odpowiedzialna za logike przetwarzania.
//@param[in] Dane obserwatora potrzebne do podejmowania decyzji podczas przetwarzania
//@return ??
int RemoteServerDisconnectedObserver::Refresh(RemoteObserverData observerData)
{
	//Utworz logike watku
	RemoteServerDisconnectedObserverLogicRunnable threadLogic(serverDataBase, observerData);
	//Utworz i uruchom watki
	boost::thread threadRemoteServerConnected(threadLogic);
	return 0;
}

//@author Marian Szczykulski
//@date 29-12-2008
//@note Logika watku
//@brief Zawiera logike przetwarzania ktora moze byc uruchomiona w odzielnym watku
int RemoteServerDisconnectedObserverLogicRunnable::operator()()
{
	LOG4CXX_INFO(logger, "Przetwarzanie logiki");
	
	//    1) ZnajdŸ odpowiedni serwer(ten który siê roz³¹cza)
	struct DomainData::Address servAddr = observerData.getServerAddress();
	int recordId = serverDataBase->Find(servAddr/*dane z observerData*/);
	if(recordId <=0)//Poniewaz bedzie to wykonane w odzielnynm watku nie ma gdzie zlapac tego wyjatku
	{				//Dlatego stodujemy tylko logowanie bledu i zakonczenie funkcji
		LOG4CXX_ERROR(logger, "Nie usunieto nic - Zle dane w observerData(objektu nie znaleziono)");
		return -1;
	}
	//    2) zaktualizuj jego wpis(usun?)
	int deletionCount = serverDataBase->DeleteRecord(recordId);//Czy rzuci jakis wyjatek
	if(deletionCount <=0)
	{
		LOG4CXX_WARN(logger, "Blad Funkcji DeleteRecord dla bazy na bierzacym serwerze");
	}
	//Pobierz wszystkie rekordy
	std::vector<Record> allRecords = serverDataBase->GetAllRecords();

	//Utworz licznik serwerow z listy
	int serverCounter =0;

	//    3)Powiadom wszystkie serwery o zmianie
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
			remoteServer->RemoveServer(servAddr/*Dane z observerData*/);//Dodac dane z observer Data
			LOG4CXX_INFO(logger, "Wiadomosc wyslana do serwera nr"<<serverCounter);
		}
		catch(std::exception & exc) //chyba rzuca jakis wyjatek??
		{
			LOG4CXX_ERROR(logger, "Blad wysylania do serwera: " << serverCounter);
		}
		serverCounter++;

	}
	

	LOG4CXX_INFO(logger, "Koniec przetwarzania logiki");
	return serverCounter;
}
