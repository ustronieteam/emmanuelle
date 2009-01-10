#ifndef REMOTECLIENTCREATEPIPEOBSERVER_H
#define REMOTECLIENTCREATEPIPEOBSERVER_H

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


///@author Marian Szczykulski
///@date 2009-01-09
///@brief Klasa obserwatora obslugujacego logike obslugi rzadania klienta o utworzenie pipe-u
class RemoteClientCreatePipeObserver : public  IRemoteObserver
{
    private:
        boost::shared_ptr<ClientsDataBase> clientsDataBase;
        boost::shared_ptr<ServerDataBase> serverDataBase;
    public:

        RemoteClientCreatePipeObserver();
		RemoteClientCreatePipeObserver(boost::shared_ptr<ServerDataBase> & servDB, boost::shared_ptr<ClientsDataBase> & clientsDB);
        RemoteClientCreatePipeObserver(RemoteClientCreatePipeObserver & arg);
        RemoteClientCreatePipeObserver & operator =(const RemoteClientCreatePipeObserver & arg);

        virtual ~RemoteClientCreatePipeObserver();

        boost::shared_ptr<ClientsDataBase> & get_clientsDataBase();
        void set_clientsDataBase(boost::shared_ptr<ClientsDataBase> & clientsDataBase);

        boost::shared_ptr<ServerDataBase> & get_serverDataBase();
        void set_serverDataBase(boost::shared_ptr<ServerDataBase> & serverDataBase);

		virtual int Refresh(RemoteObserverData observerData);

};  //end class RemoteClientCreatePipeObserver


///@author Marian Szczykulski
///@brief Funktor odpowiedzialny za logike przetwarzania. 
///@brief Potrzebny do wywo³ania w odzielnym watku
class RemoteClientCreatePipeObserverLogicRunnable
{
	private: 
		boost::shared_ptr<ServerDataBase> serverDataBase;
		boost::shared_ptr<ClientsDataBase> clientsDataBase;
		RemoteObserverData observerData;
		log4cxx::LoggerPtr logger;//(Logger::getLogger("RemoteClientCreatePipeObserverLogicRunnable"));
	public:
		RemoteClientCreatePipeObserverLogicRunnable(boost::shared_ptr<ServerDataBase> & sDB,boost::shared_ptr<ClientsDataBase> & cDB, const RemoteObserverData & oD)
		{
			serverDataBase = sDB;
			clientsDataBase = cDB;
			observerData = oD;
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("RemoteClientCreatePipeObserverLogicRunnable"));
			logger->setLevel(log4cxx::Level::getAll());
		}
		int operator()();


};

#endif
