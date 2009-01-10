#ifndef MODEL_H
#define MODEL_H
//Begin section for file Model.h
//TODO: Add definitions that you want preserved
//End section for file Model.h

#include "CorbaConnector.h"

#include "IModel.h"

#include "IClientClient.h"
#include "IClientClient_impl.h"
#include "IClientServer.h"
#include "IClientServer_impl.h"

#include "DomainData.h"

#include <log4cxx/logger.h>
#include <log4cxx/level.h>

class Client;
class ClientsData;

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class Model : public IModel, public CorbaConnector
{

    //Begin section for Model
    //TODO: Add attributes that you want preserved
    //End section for Model

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Client * client;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsData * clientsData;

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
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("AplicationClass"));
			logger->setLevel(log4cxx::Level::getAll());
		}

		///
		/// Stworzenie brokera po stronie klienta, zarejestrownie obiektow zdalnych i uruchomienie
		/// nasluchiwania na porcie CLNTPORT; musi zostac wywolana dopiero po polaczeniu z serwerem
		///
		void activateListning();

    public:

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
		}

		//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         int AddStatusObserver(DataObserver & observer) ;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         int SendPackage(FilePackage package);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         int DeleteContact() ;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         int SendMessage() ;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         int AddContact() ;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         int Disconnect() ;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         bool ConnectToServer() ;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         int AddFileObserver(IRemoteObserver & observer) ;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         int AddMessageObserver(IRemoteObserver & observer) ;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
          int GetContactsList(); // TODO: zmienic typ zwracany

};  //end class Model

#endif
