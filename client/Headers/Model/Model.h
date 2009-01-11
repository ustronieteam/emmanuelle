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
#include <boost/shared_ptr.hpp>
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
class Model : public IModel, public CorbaConnector
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
			clientsData = boost::shared_ptr<ClientsData>(new ClientsData());
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
		/// @return adres serwera do ktorego laczy sie klient
		///
		/// address getter
		///
		DomainData::Address GetServerAddress() const
		{
			return serverAddress;
		}

		///
		/// @param [in] addr	adres serwera do ktorego laczy sie klient
		///
		/// address setter
		///
		void SetServerAddress(const char * addr)
		{
			DomainData::Address a;
			a.localization = CORBA::string_dup(addr);
			this->serverAddress = a;
			client->setServerAddress(a);
		}


         int AddStatusObserver(DataObserver & observer) ;

         int SendPackage(FilePackage package);

         int DeleteContact() ;

         int SendMessage(DomainData::Address recAddr, DomainData::Message msg);

         int AddContact() ;

         int Disconnect() ;

         bool ConnectToServer() ;

         int AddFileObserver(IRemoteObserver & observer) ;

         int AddMessageObserver(IRemoteObserver & observer) ;

         int GetContactsList(); // TODO: zmienic typ zwracany

};  //end class Model

#endif
