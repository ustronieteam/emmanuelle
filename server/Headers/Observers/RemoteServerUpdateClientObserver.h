#ifndef REMOTESERVERUPDATECLIENTOBSERVER_H
#define REMOTESERVERUPDATECLIENTOBSERVER_H



#include "IRemoteObserver.h"
#include "ServerDataBase.h"
#include "ServerRecord.h"
#include "ClientsDataBase.h"
#include "ClientRecord.h"
#include "RemoteObserverData.h"
#include "IServerServer.h"
#include "IClientServer.h"
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <exception>
#include <boost/thread.hpp>
#include <vector>
#include "DomainData.h"
//Do utworzenia logow w przypadkyu bledow
#include <log4cxx/logger.h>
#include <log4cxx/level.h>


class ClientsDataBase;
class ServerDataBase;

//    1)Znajdz klienta
//    2) Wprowaz zmiany w jego rekordzie
//    3)Powiadom wszystkie serwery o zmianie

///
///@author Marian Szczykulski
///@date 2009-01-09
///@brief Klasa obserwatora obslugujacego logike podczas modyfikacji danych klienta
///@brief	Zdarzenie modyfikacji rekordu klienta lub dodanie nowego rekordu
///@brief	jest odpowiedzią na zdalne metody: ClientStatusChanged - wysylane przez inne serwery
///@brief	ktore moze byc rozsylane gdy: podlaczyl sie nowy klient, podlaczyl sie klient juz istniejacy w bazie
///@brief	analogicznie dla rozlaczania
///
class RemoteServerUpdateClientObserver : public IRemoteObserver
{

    private:

        boost::shared_ptr<ClientsDataBase> clientsDataBase;

        boost::shared_ptr<ServerDataBase> serverDataBase;



    public:

        RemoteServerUpdateClientObserver();
		RemoteServerUpdateClientObserver(boost::shared_ptr<ServerDataBase> & servDB, boost::shared_ptr<ClientsDataBase> & clientsDB);
        RemoteServerUpdateClientObserver(RemoteServerUpdateClientObserver & arg);
        RemoteServerUpdateClientObserver & operator =(const RemoteServerUpdateClientObserver & arg);


        virtual ~RemoteServerUpdateClientObserver();

        boost::shared_ptr<ClientsDataBase> & get_clientsDataBase();

        void set_clientsDataBase(boost::shared_ptr<ClientsDataBase> & clientsDataBase);

        boost::shared_ptr<ServerDataBase> & get_serverDataBase();


        void set_serverDataBase(boost::shared_ptr<ServerDataBase> & serverDataBase);

		virtual int Refresh(RemoteObserverData observerData);

};  //end class RemoteServerUpdateClientObserver

///
///@author Marian Szczykulski
///@brief Funktor odpowiedzialny za logike przetwarzania. 
///@brief Potrzebny do wywołania w odzielnym watku
///
class RemoteServerUpdateClientObserverLogicRunnable
{
	private: 
		boost::shared_ptr<ServerDataBase> serverDataBase;
		boost::shared_ptr<ClientsDataBase> clientsDataBase;
		RemoteObserverData observerData;
		log4cxx::LoggerPtr logger;//(Logger::getLogger("RemoteServerConnectedObserverLogicRunnable"));
	public:
		RemoteServerUpdateClientObserverLogicRunnable(boost::shared_ptr<ServerDataBase> & sDB,boost::shared_ptr<ClientsDataBase> & cDB, const RemoteObserverData & oD)
		{
			serverDataBase = sDB;
			clientsDataBase = cDB;
			observerData = oD;
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("RemoteServerUpdateClientObserverLogicRunnable"));
			logger->setLevel(LOGLEVEL);
		}
		int operator()();


};

#endif
