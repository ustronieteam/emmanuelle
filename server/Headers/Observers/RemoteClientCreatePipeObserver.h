#ifndef REMOTECLIENTCREATEPIPEOBSERVER_H
#define REMOTECLIENTCREATEPIPEOBSERVER_H
//Begin section for file RemoteClientCreatePipeObserver.h
//TODO: Add definitions that you want preserved
//End section for file RemoteClientCreatePipeObserver.h

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


//    1) Znajdz w bazie o klientach, takiego który nie blokuje po³¹czeñ przychodz¹cych i jest pod³¹czony
//    z aktualnym serwerem i przekaz mu odpowiedni komunikat o tworzeniu pipe'u
//    2) Je¿eli takiego nie ma to znajdŸ takiego który jest pod³¹czony do innego serwera i przeka¿ temu serwerowi
//    odpowiedni komunikat (PassCreatePipe?)
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class RemoteClientCreatePipeObserver : IRemoteObserver
{

    //Begin section for RemoteClientCreatePipeObserver
    //TODO: Add attributes that you want preserved
    //End section for RemoteClientCreatePipeObserver

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        boost::shared_ptr<ClientsDataBase> clientsDataBase;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
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


//@author Marian Szczykulski
//@brief Funktor odpowiedzialny za logike przetwarzania. 
//@brief Potrzebny do wywo³ania w odzielnym watku
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
