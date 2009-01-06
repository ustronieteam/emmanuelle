#ifndef PASSMESSAGEOBSERVER_H
#define PASSMESSAGEOBSERVER_H
//Begin section for file PassMessageObserver.h
//TODO: Add definitions that you want preserved
//End section for file PassMessageObserver.h

#include "IRemoteObserver.h"
#include "ClientsDataBase.h"
#include "ClientRecord.h"
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

class ClientsDataBase;

//    1)Znajdz klienta docelowego(adresata) - musi byc do nas pod³¹czony (Je¿eli nie to b³¹d.)
//    2)Przekaz mu wiadomoœæ
class PassMessageObserver : IRemoteObserver
{

    //Begin section for PassMessageObserver
    //TODO: Add attributes that you want preserved
    //End section for PassMessageObserver

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        boost::shared_ptr<ClientsDataBase> clientsDataBase;



    public:

        PassMessageObserver();
		PassMessageObserver(boost::shared_ptr<ClientsDataBase> & cDB);
        PassMessageObserver(PassMessageObserver & arg);
		PassMessageObserver & operator =(const PassMessageObserver & arg);

        virtual ~PassMessageObserver();

        boost::shared_ptr<ClientsDataBase> & get_clientsDataBase();
        void set_clientsDataBase(boost::shared_ptr<ClientsDataBase> & clientsDataBase);

		virtual int Refresh(RemoteObserverData observerData);

};  //end class PassMessageObserver

//@author Marian Szczykulski
//@brief Funktor odpowiedzialny za logike przetwarzania. 
//@brief Potrzebny do wywo³ania w odzielnym watku
class PassMessageObserverLogicRunnable
{
	private: 
		boost::shared_ptr<ClientsDataBase> clientsDataBase;
		RemoteObserverData observerData;
		log4cxx::LoggerPtr logger;//(Logger::getLogger("PassMessageObserverLogicRunnable"));
	public:
		PassMessageObserverLogicRunnable(boost::shared_ptr<ClientsDataBase> & cDB, const RemoteObserverData & oD)
		{
			clientsDataBase = cDB;
			observerData = oD;
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("PassMessageObserverLogicRunnable"));
			logger->setLevel(log4cxx::Level::getAll());
		}
		int operator()();


};


#endif
