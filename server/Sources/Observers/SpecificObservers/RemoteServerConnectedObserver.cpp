#include "Observers/RemoteServerConnectedObserver.h"
#include <vector>
#include <boost/thread.hpp>
#include <exception>
#include <boost/thread.hpp>
#include "ServerRecord.h"
#include "ServerDataBase.h"
#include "IServerServer.h"
#include <iostream>

//Begin section for file RemoteServerConnectedObserver.cpp
//TODO: Add definitions that you want preserved
//End section for file RemoteServerConnectedObserver.cpp

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
//@author Marian Szczykulski
//@date 27-12-2008
//@note Ustawieni bazy serwerow
//@brief Funkcja ustawjajaca baze serwera
//@param[in] sprytny wskaznik na baze danych serwera
void RemoteServerConnectedObserver::set_serverDataBase(boost::shared_ptr<ServerDataBase> & serverDataBase)
{
	this->serverDataBase = serverDataBase;
}
//@author Marian Szczykulski
//@date 27-12-2008
//@note Obserwator podlaczenia sie nowego serwera
//@brief Glowna funkcja obserwatora, odpowiedzialna za logike przetwarzania.
//@param[in] Dane obserwatora potrzebne do podejmowania decyzji podczas przetwarzania
//@return ??
int RemoteServerConnectedObserver::Refresh(RemoteObserverData observerData)
{
	//Utworz logike watku
	RemoteServerConnectedObserverLogicRunnable threadLogic(serverDataBase, observerData);
	//Utworz i uruchom watki
	boost::thread threadRemoteServerConnected(threadLogic);

	return 0;
}
//@author Marian Szczykulski
//@date 27-12-2008
//@note Logika watku
//@brief Zawiera logike przetwarzania ktora moze byc uruchomiona w odzielnym watku
int RemoteServerConnectedObserverLogicRunnable::operator()()
{
	LOG4CXX_INFO(logger, "Przetwarzanie logiki");
	//Odpowiedz na Join()		 -> wtedy rozsylamy info do innych serverow
	//Lub odpowiedz na AddServer -> wtedy nie rozsylamy info do innych serverow

	//	1) Dodaj nowy serwer do bazy(lub zmodyfikuj istniejacy rekord)
	int serverId = serverDataBase->Find(/*dane z observerdata*/);
	if(serverId >0)
	{//Rekord jest w bazie z jakis powodow, trzeba wiec go zmodyfikowac
		try
		{
			Record servRec = serverDataBase->GetRecord(serverId);
			//Modyfikuj rekord zgodnie z observerData
			int status = serverDataBase->ModifyRecord(servRec);
			if(status<0)
			{
				LOG4CXX_ERROR(logger, "Blad modyfikacji rekordu servera");
				return -2;
			}
			
		}
		catch(std::exception & exc)
		{
			LOG4CXX_ERROR(logger, "Zlapano wyjotek podczas pobierania rekordu z bazy danych servera serverId: "<<serverId);
			return -2;
		}
		
	}
	else
	{//Rekordu nie ma w bazie trzeba dodac nowy
		ServerRecord newRecord = ServerRecord(); //do dokonczenia (wype³niæ pola z observerData) !!!
		int status = serverDataBase->InsertRecord(newRecord);
		if(status < 0)
		{
			LOG4CXX_ERROR(logger, "Blad podczas wstawiania nowego rekordu servera");
			return -1;
		}
	}
	//Utworz licznik serwerow z listy(tylko dla odp dla Join ma sens)
	int serverCounter =0;
	//na podstawie observerData ocen czy jest to odpowiedz na join czy AddServer
	if(true/*jest to odp na Join */)
	{

	
		//	2) Pobierz liste wszystkich serwerów
		std::vector<Record> allRecords = serverDataBase->get_record();

		
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
				remoteServer.AddServer();//Dodac dane z observer Data
				LOG4CXX_INFO(logger, "Wiadomosc wyslana do serwera nr"<<serverCounter);
			}
			catch(std::exception & exc) //chyba rzuca jakis wyjatek??
			{
				LOG4CXX_ERROR(logger, "Blad wysylania do serwera: " << serverCounter);
			}
			serverCounter++;

		}
		//Sleep(5000);
	}
	LOG4CXX_INFO(logger, "Koniec przetwarzania logiki");
	return serverCounter;
}
