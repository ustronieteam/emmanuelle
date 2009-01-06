#ifndef REMOTESERVERCONNECTEDOBSERVER_H
#define REMOTESERVERCONNECTEDOBSERVER_H
//Begin section for file RemoteServerConnectedObserver.h
//TODO: Add definitions that you want preserved
//End section for file RemoteServerConnectedObserver.h

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

//Do utworzenia logow w przypadkyu bledow
#include <log4cxx/logger.h>
#include <log4cxx/level.h>


class ServerDataBase;

//<h4>
//    Odpowiedz na Join()
//</h4>
//<p>
//    1) Dodaj nowy serwer do bazy
//</p>
//<p>
//    2) Pobierz liste wszystkich serwer�w
//</p>
//<p>
//    3) Do ka�dego serwera z listy dodaj nowy serwer (AddServer)
//</p>
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class RemoteServerConnectedObserver : IRemoteObserver
{

    //Begin section for RemoteServerConnectedObserver
    //TODO: Add attributes that you want preserved
    //End section for RemoteServerConnectedObserver

    private:
        //ServerDataBase * serverDataBase;
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

//@author Marian Szczykulski
//@brief Funktor odpowiedzialny za logike przetwarzania. 
//@brief Potrzebny do wywo�ania w odzielnym watku
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
