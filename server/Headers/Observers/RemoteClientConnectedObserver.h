#ifndef REMOTECLIENTCONNECTEDOBSERVER_H
#define REMOTECLIENTCONNECTEDOBSERVER_H

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
#include "Server.h"
//Do utworzenia logow w przypadkyu bledow
#include <log4cxx/logger.h>
#include <log4cxx/level.h>


class ClientsDataBase;
class ServerDataBase;

///
///@author Marian Szczykulski
///@date 2009-01-09
///@brief Klasa obserwatora obslugujacego logike podczas podlaczania sie nowego klienta
///    1) Znajdz klienta
///    2) Powiadom wszystkie serwery o zmianie
///
class RemoteClientConnectedObserver : public  IRemoteObserver
{

    private:
        boost::shared_ptr<ClientsDataBase> clientsDataBase;
        boost::shared_ptr<ServerDataBase> serverDataBase;



    public:
        RemoteClientConnectedObserver();
		RemoteClientConnectedObserver(boost::shared_ptr<ServerDataBase> & servDB, boost::shared_ptr<ClientsDataBase> & clientsDB);
        RemoteClientConnectedObserver(RemoteClientConnectedObserver & arg);
        RemoteClientConnectedObserver & operator =(const RemoteClientConnectedObserver & arg);

        virtual ~RemoteClientConnectedObserver();

        boost::shared_ptr<ClientsDataBase> & get_clientsDataBase();
        void set_clientsDataBase(boost::shared_ptr<ClientsDataBase> & clientsDataBase);

        boost::shared_ptr<ServerDataBase> & get_serverDataBase();
        void set_serverDataBase(boost::shared_ptr<ServerDataBase> & serverDataBase);

		virtual int Refresh(RemoteObserverData observerData);

};  //end class RemoteClientConnectedObserver

///
///@author Marian Szczykulski
///@brief Funktor odpowiedzialny za logike przetwarzania. 
///
///@brief Potrzebny do wywo�ania w odzielnym watku
///
class RemoteClientConnectedObserverLogicRunnable
{
	private: 
		boost::shared_ptr<ServerDataBase> serverDataBase;
		boost::shared_ptr<ClientsDataBase> clientsDataBase;
		RemoteObserverData observerData;
		log4cxx::LoggerPtr logger;//(Logger::getLogger("RemoteServerConnectedObserverLogicRunnable"));
	public:
		RemoteClientConnectedObserverLogicRunnable(boost::shared_ptr<ServerDataBase> & sDB,boost::shared_ptr<ClientsDataBase> & cDB, const RemoteObserverData & oD)
		{
			serverDataBase = sDB;
			clientsDataBase = cDB;
			observerData = oD;
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("RemoteClientConnectedObserverLogicRunnable"));
			logger->setLevel(LOGLEVEL);
		}
		int operator()();


};


#endif
