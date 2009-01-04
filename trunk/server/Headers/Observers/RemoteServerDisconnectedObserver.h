#ifndef REMOTESERVERDISCONNECTEDOBSERVER_H
#define REMOTESERVERDISCONNECTEDOBSERVER_H
//Begin section for file RemoteServerDisconnectedObserver.h
//TODO: Add definitions that you want preserved
//End section for file RemoteServerDisconnectedObserver.h

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
//Do utworzenia logow w przypadkyu bledow
#include <log4cxx/logger.h>
#include <log4cxx/level.h>




class ServerDataBase;

//    1) ZnajdŸ odpowiedni serwer(ten który siê roz³¹cza)
//    2) zaktualizuj jego wpis(usun?)
//    3)Powiadom wszystkie serwery o zmianie
class RemoteServerDisconnectedObserver : IRemoteObserver
{

    //Begin section for RemoteServerDisconnectedObserver
    //TODO: Add attributes that you want preserved
    //End section for RemoteServerDisconnectedObserver

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
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


//@author Marian Szczykulski
//@brief Funktor odpowiedzialny za logike przetwarzania. 
//@brief Potrzebny do wywo³ania w odzielnym watku
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
