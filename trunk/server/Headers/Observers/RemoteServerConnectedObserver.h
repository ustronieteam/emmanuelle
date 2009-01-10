#ifndef REMOTESERVERCONNECTEDOBSERVER_H
#define REMOTESERVERCONNECTEDOBSERVER_H

#include "IRemoteObserver.h"
#include "RemoteObserverData.h"
#include <boost/shared_ptr.hpp>
#include <exception>
#include <boost/thread.hpp>
#include <vector>
#include <boost/thread.hpp>
#include <exception>
#include <boost/thread.hpp>
#include "ServerRecord.h"
#include "ServerDataBase.h"
#include "IServerServer.h"
#include <iostream>
#include "DomainData.h"
#include "Server.h"
#include "ClientRecord.h"
//Do utworzenia logow w przypadkyu bledow
#include <log4cxx/logger.h>
#include <log4cxx/level.h>


class ServerDataBase;

///@author Marian Szczykulski
///@date 2009-01-09
///@brief Klasa obserwatora obslugujacego logike podczas podlaczania sie nowego serwera
class RemoteServerConnectedObserver : public IRemoteObserver
{
    private:
		boost::shared_ptr<ServerDataBase> serverDataBase;


    public:

		//Zestaw konstruktorow
        RemoteServerConnectedObserver();
        RemoteServerConnectedObserver(RemoteServerConnectedObserver & arg);
		RemoteServerConnectedObserver(boost::shared_ptr<ServerDataBase> & servDB);

        RemoteServerConnectedObserver & operator=(const RemoteServerConnectedObserver & arg);

        virtual ~RemoteServerConnectedObserver();

        boost::shared_ptr<ServerDataBase>& get_serverDataBase();
        void set_serverDataBase(boost::shared_ptr<ServerDataBase> & serverDataBase);

		virtual int Refresh(RemoteObserverData observerData);

};  
//end class RemoteServerConnectedObserver

///@author Marian Szczykulski
///@brief Funktor odpowiedzialny za logike przetwarzania. 
///@brief Potrzebny do wywo³ania w odzielnym watku
class RemoteServerConnectedObserverLogicRunnable
{
	private: 
		boost::shared_ptr<ServerDataBase> serverDataBase;
		RemoteObserverData observerData;
		log4cxx::LoggerPtr logger;//(Logger::getLogger("RemoteServerConnectedObserverLogicRunnable"));
	public:
		RemoteServerConnectedObserverLogicRunnable(boost::shared_ptr<ServerDataBase> & sDB, const RemoteObserverData & oD)
		{
			serverDataBase = sDB;
			observerData = oD;
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("RemoteServerConnectedObserverLogicRunnable"));
			logger->setLevel(log4cxx::Level::getAll());
		}
		int operator()();


};

#endif
