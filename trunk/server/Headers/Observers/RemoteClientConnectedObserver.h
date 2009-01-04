#ifndef REMOTECLIENTCONNECTEDOBSERVER_H
#define REMOTECLIENTCONNECTEDOBSERVER_H
//Begin section for file RemoteClientConnectedObserver.h
//TODO: Add definitions that you want preserved
//End section for file RemoteClientConnectedObserver.h

#include "IRemoteObserver.h"
#include "ServerDataBase.h"
#include "ServerRecord.h"
#include "ClientsDataBase.h"
#include "ClientRecord.h"
#include "RemoteObserverData.h"
#include "IServerServer.h" //Zaslepka
#include <boost/shared_ptr.hpp>
#include <iostream>
#include <exception>
#include <boost/thread.hpp>
#include <vector>
//Do utworzenia logow w przypadkyu bledow
#include <log4cxx/logger.h>
#include <log4cxx/level.h>


class ClientsDataBase;
class ServerDataBase;

//    1) Znajdz klienta
//    2) zaktualizuj jego wpis w bazie (dodaj jak nie ma)
//    3) Powiadom wszystkie serwery o zmianie
class RemoteClientConnectedObserver : IRemoteObserver
{

    //Begin section for RemoteClientConnectedObserver
    //TODO: Add attributes that you want preserved
    //End section for RemoteClientConnectedObserver

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        boost::shared_ptr<ClientsDataBase> clientsDataBase;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
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

//@author Marian Szczykulski
//@brief Funktor odpowiedzialny za logike przetwarzania. 
//@brief Potrzebny do wywo³ania w odzielnym watku
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
			logger->setLevel(log4cxx::Level::getAll());
		}
		int operator()();


};


#endif
