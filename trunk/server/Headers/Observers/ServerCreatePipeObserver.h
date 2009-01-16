#ifndef SERVERCREATEPIPEOBSERVER_H
#define SERVERCREATEPIPEOBSERVER_H

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

///
///@author Marian Szczykulski
///@date 2009-01-09
///@brief Klasa obserwatora obslugujacego logike podczas tworzenia pipe-e (komunikacja serwerow)
///@brief    1)Klientowi który ma tworzyæ pipe przeka¿ odpowiedni¹ wiadomoœæ.
///@brief      Klient ten musi byæ z nami pod³¹czony, je¿eli nie to b³ad integralnoœci danych w bazie.
///
class ServerCreatePipeObserver : public IRemoteObserver
{

    private:

         boost::shared_ptr<ClientsDataBase> clientsDataBase;



    public:

        ServerCreatePipeObserver();
        ServerCreatePipeObserver(ServerCreatePipeObserver & arg);
		ServerCreatePipeObserver(boost::shared_ptr<ClientsDataBase> & clientsDB);
        ServerCreatePipeObserver & operator =(const ServerCreatePipeObserver & arg);

        virtual ~ServerCreatePipeObserver();

         boost::shared_ptr<ClientsDataBase> & get_clientsDataBase();
        void set_clientsDataBase( boost::shared_ptr<ClientsDataBase> & clientsDataBase);

		virtual int Refresh(RemoteObserverData observerData);

};  //end class ServerCreatePipeObserver

///
///@author Marian Szczykulski
///@brief Funktor odpowiedzialny za logike przetwarzania. 
///@brief Potrzebny do wywo³ania w odzielnym watku
///
class ServerCreatePipeObserverLogicRunnable
{
	private: 
		boost::shared_ptr<ClientsDataBase> clientsDataBase;
		RemoteObserverData observerData;
		log4cxx::LoggerPtr logger;//(Logger::getLogger("ServerCreatePipeObserverLogicRunnable"));
	public:
		ServerCreatePipeObserverLogicRunnable(boost::shared_ptr<ClientsDataBase> & cDB, const RemoteObserverData & oD)
		{
			clientsDataBase = cDB;
			observerData = oD;
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("ServerCreatePipeObserverLogicRunnable"));
			logger->setLevel(LOGLEVEL);
		}
		int operator()();


};

#endif