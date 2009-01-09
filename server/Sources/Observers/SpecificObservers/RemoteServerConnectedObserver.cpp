#include "Observers/RemoteServerConnectedObserver.h"
#include <vector>
#include <boost/thread.hpp>
#include <exception>
#include <boost/thread.hpp>
#include "ServerRecord.h"
#include "ServerDataBase.h"
#include "IServerServer.h"
#include <iostream>

RemoteServerConnectedObserver::RemoteServerConnectedObserver() 
{
	this->serverDataBase = boost::shared_ptr<ServerDataBase>();
}
RemoteServerConnectedObserver::RemoteServerConnectedObserver(boost::shared_ptr<ServerDataBase> & servDB) 
{
	 this->serverDataBase = servDB;
}

RemoteServerConnectedObserver::RemoteServerConnectedObserver(RemoteServerConnectedObserver & arg) 
{
    this->serverDataBase = arg.serverDataBase;
}


RemoteServerConnectedObserver & RemoteServerConnectedObserver::operator=(const RemoteServerConnectedObserver & arg) 
{
    if (this != &arg)
    {
        this->serverDataBase = arg.serverDataBase;
    }
	return *this;
}

RemoteServerConnectedObserver::~RemoteServerConnectedObserver() 
{
}

boost::shared_ptr<ServerDataBase> & RemoteServerConnectedObserver::get_serverDataBase() 
{
    return serverDataBase;
}
///@author Marian Szczykulski
///@date 27-12-2008
///@note Ustawieni bazy serwerow
///@brief Funkcja ustawjajaca baze serwera
///@param[in] sprytny wskaznik na baze danych serwera
void RemoteServerConnectedObserver::set_serverDataBase(boost::shared_ptr<ServerDataBase> & serverDataBase)
{
	this->serverDataBase = serverDataBase;
}
///@author Marian Szczykulski
///@date 27-12-2008
///@note Obserwator podlaczenia sie nowego serwera
///@brief Glowna funkcja obserwatora, odpowiedzialna za logike przetwarzania.
///@param[in] Dane obserwatora potrzebne do podejmowania decyzji podczas przetwarzania
///@return ??
int RemoteServerConnectedObserver::Refresh(RemoteObserverData observerData)
{
	log4cxx::LoggerPtr logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("RemoteServerConnectedObserver"));
	logger->setLevel(log4cxx::Level::getAll());

	LOG4CXX_DEBUG(logger, "Refresh obserwatora : start. ServerAddres" <<observerData.getServerAddress().localization.in());
	if(observerData.get_eventType()!=SERVER_CONNECTED)
		return 0; //Odfiltrowanie niechcianych zdarzen
	//Utworz logike watku
	RemoteServerConnectedObserverLogicRunnable threadLogic(serverDataBase, observerData);
	//Utworz i uruchom watki
	boost::thread threadRemoteServerConnected(threadLogic);
	LOG4CXX_DEBUG(logger, "Refresh obserwatora : end");
	return 0;
}
///@author Marian Szczykulski
///@date 27-12-2008
///@note Logika watku
///@brief Zawiera logike przetwarzania ktora moze byc uruchomiona w odzielnym watku
int RemoteServerConnectedObserverLogicRunnable::operator()()
{
	LOG4CXX_INFO(logger, "Przetwarzanie logiki");
	//Odpowiedz na Join()		 -> wtedy rozsylamy info do innych serverow

	//	1) Dodaj nowy serwer do bazy(lub zmodyfikuj istniejacy rekord)
	struct DomainData::Address servAddr = observerData.getServerAddress();
	int serverId = serverDataBase->Find(servAddr); //id nowego serwera
	if(serverId<=0)
	{
		LOG4CXX_ERROR(logger,"Brak nowego serwera na lokalnej bazie. Nie zostal dodany wiec nigdzie. serv addr:" <<servAddr.localization.in() <<"servId:"<< serverId);
		return -1;
	}
	//Zdobadz wlasne id
	struct DomainData::Address localServAddr = Server::GetMyIP();
	int localId = serverDataBase->Find(localServAddr); //wlasne id w bazie
	if(localId<=0)
	{
		LOG4CXX_ERROR(logger,"Brak danych o lokalnym serwerze w bazie");
		return -2;
	}
	//Utworz licznik serwerow z listy(tylko dla odp dla Join ma sens)
	int serverCounter =0;

	//	2) Pobierz liste wszystkich serwerów
	std::vector<ServerRecord> allRecords = serverDataBase->GetAllRecords();

	
	//	3) Do ka¿dego serwera z listy dodaj nowy serwer (AddServer)
	LOG4CXX_INFO(logger, "Petla wysylania wiadomosci do serwerow");
	for(std::vector<ServerRecord>::iterator it = allRecords.begin();
			it != allRecords.end();	//Dopuki nie doszlismy do konca zbioru
				it++)
	{
		ServerRecord servRec = (*it);
		if(servRec.GetRecordId()==serverId || servRec.GetRecordId()==localId)
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
			struct DomainData::Address Addr;
			Addr = observerData.getServerAddress();
			remoteServer->AddServer(Addr);//Dodac dane z observer Data
			LOG4CXX_INFO(logger, "Wiadomosc wyslana do serwera nr"<<serverCounter);
		}
		catch(CORBA::SystemException & e) //chyba rzuca jakis wyjatek??
		{
			LOG4CXX_ERROR(logger, "Blad wysylania do serwera: " << serverCounter<< ".Powod: "<< e._name());
		}
		serverCounter++;

	}
	//TODO: dodac wywolanie na rekordzie o id serverID wywolanie w petli dodanie wszystkich klientow
	//TODO: aby ustawic baze klientow

	//Sleep(5000);
	LOG4CXX_INFO(logger, "Koniec przetwarzania logiki");
	return serverCounter;
}
