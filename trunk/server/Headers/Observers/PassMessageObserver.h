#ifndef PASSMESSAGEOBSERVER_H
#define PASSMESSAGEOBSERVER_H

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
#include "Server.h"
//Do utworzenia logow w przypadkyu bledow
#include <log4cxx/logger.h>
#include <log4cxx/level.h>

class ClientsDataBase;

///
///@author Marian Szczykulski
///@date 2009-01-09
///@brief Klasa obserwatora obslugujacego logike podczas przesylania wiadomosci pomiedzy serwerami
///@brief    1)Znajdz klienta docelowego(adresata) - musi byc do nas pod³¹czony (Je¿eli nie to b³¹d.)
///@brief    2)Przekaz mu wiadomoœæ
///
class PassMessageObserver : public IRemoteObserver
{

    private:
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

///
///@author Marian Szczykulski
///@brief Funktor odpowiedzialny za logike przetwarzania. 
///@brief Potrzebny do wywo³ania w odzielnym watku
///
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
			logger->setLevel(LOGLEVEL);
		}
		int operator()();


};


#endif
