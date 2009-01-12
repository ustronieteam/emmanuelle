#ifndef MODEL_H
#define MODEL_H

#include "CorbaConnector.h"

#include "IModel.h"

#include "IClientClient.h"
#include "IClientClient_impl.h"
#include "IClientServer.h"
#include "IClientServer_impl.h"
#include "DomainData.h"

#include "Client.h"
#include "ClientsData.h"
#include "FileObserver.h"
#include "MessageObserver.h"
#include "StatusObserver.h"
#include "StatusCheckerFunctor.h"

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <log4cxx/logger.h>
#include <log4cxx/level.h>

class Client;
class ClientsData;

///
/// @author	Mateusz Ko³odziejczyk, Marian Szczykulski
/// @date	10.01.2009
///
/// @brief	klasa Modelu - implementuje interfejs IModel i dziedziczy z klasy CorbaConnector
///
class Model : public IModel
{

    private:
		
		boost::shared_ptr<Client> client;

		boost::shared_ptr<ClientsData> clientsData;

		///
		/// wskaznik do obiektu zdalnego udostepnianego serwerom
		///
		IClientServer_impl * serverImpl;

		///
		/// wskaznik do obiektu zdalnego udostepnianego klientom
		///
		IClientClient_impl * clientImpl;

		///
		/// adres serwera do ktorego powinien sie podlaczyc klient
		///
		DomainData::Address serverAddress;

		// logger
		log4cxx::LoggerPtr logger;

		///
		/// prywatny konstruktor
		///
		Model()
		{
			//logger
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("Model"));
			logger->setLevel(log4cxx::Level::getAll());
			client = boost::shared_ptr<Client>(new Client(serverAddress) );
			clientsData = boost::shared_ptr<ClientsData>(new ClientsData(true));
		}

		///
		/// Stworzenie brokera po stronie klienta, zarejestrownie obiektow zdalnych i uruchomienie
		/// nasluchiwania na porcie CLNTPORT; musi zostac wywolana dopiero po polaczeniu z serwerem
		///
		void activateListning();

    public:

		///
		/// @return	obiekt modelu, ktory jest obiektem typu singleton
		///
		/// statyczna metoda zwracajaca wskaznik do obiektu klasy Model jesli
		/// istnieje badz tworzaca go jesli nie istnieje
		///
        static IModel * GetInstance()
		{
			static IModel * instance = new Model();

			return instance;
		}

		///
		/// destruktor
		///
        virtual ~Model()
		{}

        Client * GetClient()
		{}

        void SetClient(Client * clnt)
		{}

        ClientsData *  GetClientsData()
		{}

		void SetClientsData(ClientsData * clientsData)
		{}

		///
		/// @return	namistaka, ktora jest udostepniana serwerom
		///
		/// getter serverImpl
		///
		IClientServer_impl * GetServerImpl()
		{
			return serverImpl;
		}

		///
		/// @return	namistaka, ktora jest udostepniana klientom
		///
		/// getter clientImpl
		///
		IClientClient_impl * GetClientImpl()
		{
			return clientImpl;
		}

		///
		/// @return adres serwera do ktorego laczy sie klient
		///
		/// address getter
		///
		virtual const DomainData::Address & GetServerAddress() const
		{
			return serverAddress;
		}

		///
		/// @param [in] addr	adres serwera do ktorego laczy sie klient
		///
		/// address setter
		///
		virtual void SetServerAddress(const char * addr)
		{
			DomainData::Address a;
			a.localization = CORBA::string_dup(addr);
			this->serverAddress = a;
			client->setServerAddress(a);
		}


		virtual void SetPortNumber(const int & p);
		virtual int GetPortNumber() const;

         int AddStatusObserver(DataObserver & observer) ;

         int SendPackage(FilePackage package);

         int DeleteContact(const DomainData::User & usr) ;

         virtual int SendMessage(DomainData::Address recAddr, DomainData::Message msg);

         int AddContact(const DomainData::User &usr) ;

         int Disconnect() ;

         bool ConnectToServer() ;

         int AddFileObserver(IRemoteObserver & observer) ;

         int AddMessageObserver(IRemoteObserver & observer) ;

		 virtual std::vector<ContactRecord> GetContactsList(); 
		virtual std::string GetOwnName();
		virtual const long & GetOwnNumber();
		virtual bool GetMyAvailability();

		virtual void SetOwnName(const char * c);
		virtual void SetOwnNumber(long l);
		virtual void SetMyAvailability(bool b);
		virtual bool runStatusChecker();

};  //end class Model

#endif
