#ifndef REMOTESERVERDISCONNECTEDOBSERVER_H
#define REMOTESERVERDISCONNECTEDOBSERVER_H

#include "IRemoteObserver.h"
#include "ServerDataBase.h"
#include "ServerRecord.h"
#include "RemoteObserverData.h"
#include "IServerServer.h"
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <exception>
#include <boost/thread.hpp>
#include <vector>
#include "DomainData.h"
//Do utworzenia logow w przypadkyu bledow
#include <log4cxx/logger.h>
#include <log4cxx/level.h>




class ServerDataBase;

///@author Marian Szczykulski
///@date 2009-01-09
///@brief Klasa obserwatora obslugujacego logike podczas rozlaczania sie serwera
class RemoteServerDisconnectedObserver : public IRemoteObserver
{
    private:
        boost::shared_ptr<ServerDataBase> serverDataBase;



    public:

        RemoteServerDisconnectedObserver();
		RemoteServerDisconnectedObserver(boost::shared_ptr<ServerDataBase> & sptr);
        RemoteServerDisconnectedObserver(RemoteServerDisconnectedObserver & arg);
        RemoteServerDisconnectedObserver & operator =(const RemoteServerDisconnectedObserver & arg);

        virtual ~RemoteServerDisconnectedObserver();

        boost::shared_ptr<ServerDataBase> & get_serverDataBase();

        void set_serverDataBase(boost::shared_ptr<ServerDataBase> & serverDataBase);
		virtual int Refresh(RemoteObserverData observerData);

};  //end class RemoteServerDisconnectedObserver


///@author Marian Szczykulski
///@brief Funktor odpowiedzialny za logike przetwarzania. 
///@brief Potrzebny do wywo³ania w odzielnym watku
class RemoteServerDisconnectedObserverLogicRunnable
{
	private: 
		boost::shared_ptr<ServerDataBase> serverDataBase;
		RemoteObserverData observerData;
		log4cxx::LoggerPtr logger;//(Logger::getLogger("RemoteServerDisconnectedObserverLogicRunnable"));
	public:
		RemoteServerDisconnectedObserverLogicRunnable(boost::shared_ptr<ServerDataBase> & sDB, const RemoteObserverData & oD)
		{
			serverDataBase = sDB;
			observerData = oD;
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("RemoteServerDisconnectedObserverLogicRunnable"));
			logger->setLevel(log4cxx::Level::getAll());
		}
		int operator()();


};
#endif
