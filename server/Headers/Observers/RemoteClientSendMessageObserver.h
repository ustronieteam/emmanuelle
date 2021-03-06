#ifndef REMOTECLIENTSENDMESSAGEOBSERVER_H
#define REMOTECLIENTSENDMESSAGEOBSERVER_H

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
///@brief Klasa obserwatora obslugujacego logike wysylania wiadomo�ci przez klienta
///    1) Znajdz odpowiedniego klienta (adresata)
///    2) Jezeli jest do nas pod��czony przekaz mu wiadomo��
///    3) Je�eli nie jest to wykonaj PassMessage na serwerze do kt�rego jest pod��czony
///
class RemoteClientSendMessageObserver : public  IRemoteObserver
{
    private:

        boost::shared_ptr<ClientsDataBase> clientsDataBase;
        boost::shared_ptr<ServerDataBase> serverDataBase;



	public:
        RemoteClientSendMessageObserver();
		RemoteClientSendMessageObserver(boost::shared_ptr<ServerDataBase> & servDB, boost::shared_ptr<ClientsDataBase> & clientsDB);
        RemoteClientSendMessageObserver(RemoteClientSendMessageObserver & arg);
        RemoteClientSendMessageObserver & operator =(const RemoteClientSendMessageObserver & arg);

        virtual ~RemoteClientSendMessageObserver();


        boost::shared_ptr<ClientsDataBase>& get_clientsDataBase();
        void set_clientsDataBase( boost::shared_ptr<ClientsDataBase>& clientsDataBase);

        boost::shared_ptr<ServerDataBase> & get_serverDataBase();
        void set_serverDataBase(boost::shared_ptr<ServerDataBase> & serverDataBase);
		virtual int Refresh(RemoteObserverData observerData);

};  //end class RemoteClientSendMessageObserver

///
///@author Marian Szczykulski
///@brief Funktor odpowiedzialny za logike przetwarzania. 
///@brief Potrzebny do wywo�ania w odzielnym watku
///
class RemoteClientSendMessageObserverLogicRunnable
{
	private: 
		boost::shared_ptr<ServerDataBase> serverDataBase;
		boost::shared_ptr<ClientsDataBase> clientsDataBase;
		RemoteObserverData observerData;
		log4cxx::LoggerPtr logger;//(Logger::getLogger("RemoteClientSendMessageObserverLogicRunnable"));
	public:
		RemoteClientSendMessageObserverLogicRunnable(boost::shared_ptr<ServerDataBase> & sDB,boost::shared_ptr<ClientsDataBase> & cDB, const RemoteObserverData & oD)
		{
			serverDataBase = sDB;
			clientsDataBase = cDB;
			observerData = oD;
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("RemoteClientSendMessageObserverLogicRunnable"));
			logger->setLevel(LOGLEVEL);
		}
		int operator()();


};

#endif
