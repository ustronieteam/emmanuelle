#ifndef SERVER_H
#define SERVER_H

#include <OB/CORBA.h>
#include <OB/BootManager.h>
#include <OB/OCI_IIOP.h>

#include "ClientsDataBase.h"
#include "ServerDataBase.h"

#include "IServerServer.h"
#include "IServerServer_impl.h"
#include "IServerClient.h"
#include "IServerClient_impl.h"

#include "RemoteServerConnectedObserver.h"
#include "RemoteServerDisconnectedObserver.h"
#include "RemoteServerUpdateClientObserver.h"
#include "PassMessageObserver.h"
#include "RemoteClientConnectedObserver.h"
#include "RemoteClientCreatePipeObserver.h"
#include "RemoteClientDisconnectedObserver.h"
#include "RemoteClientSendMessageObserver.h"
#include "ServerCreatePipeObserver.h"

#include "ServerRecord.h"
#include "ClientRecord.h"

#include "CorbaConnector.h"

#include <iostream>
#include <fstream>
#include <string>
#include <boost/thread.hpp>
#include <boost/regex.hpp>

#include <log4cxx/logger.h>
#include <log4cxx/level.h>


const std::string NADDRESS = "address";

///
/// @author	Mateusz Ko³odziejczyk
/// @date	06.01.2009
///
/// @brief	Reprezentacja obiektu serwera - lacznie z innymi serwerami i wlaczenie nasluchiwania
///
/// Klasa reprezentuj¹ca Serwer - przechowuje obiekty bazy danych serwow aktywnych i aktywnych
/// klientow, wczytuje dane z pliku konfiguracyjnego i na jego podstawie tworzy: serwer macierzysty
/// albo nowy serwer i podlacza sie do ktoregos juz pierwotnie utworzonego; wlacza nasluchiwanie na 
/// nowe serwery i klientow
///
class Server : public CorbaConnector
{
    private:

		///
		/// wskaznik do bazy danych aktywnych klientow
		///
		boost::shared_ptr<ClientsDataBase> clientDataBaseObj;

		///
		/// wskaznik do bazy danych aktywnych serwerow
		///
		boost::shared_ptr<ServerDataBase> serverDataBaseObj;

		///
		/// wskaznik do obiektu zdalnego udostepnianego serwerom
		///
		IServerServer_impl * serverImpl;

		///
		/// wskaznik do obiektu zdalnego udostepnianego klientom
		///
		IServerClient_impl * clientImpl;

		///
		/// nazwa pliku konfiguracyjnego
		///
        const char * configFileName;

		///
		/// address instancji serwera
		///
		static DomainData::Address myIPAddress;

		// logger
		log4cxx::LoggerPtr logger;

		///
		/// @param [in]	address	adres serwera macierzystego
		/// @param [in]	port	port na ktorym masluchuje serwer macierzysty
		/// @return				0 - powodzneie, 1 - niepowodzenie
		///
		/// polaczenie z serwerem macierzystym, komunikacja (wymiana danych) i ich zapisanie w bazie 
		///
		bool init(std::string address, std::string port);

		///
		///	@param [out]	address		miejsce gdzie ma byc zapisany adress serwera mecierzystego odczytany z pliku
		/// @return						0 - powodzenie, 1 - niepowodzenie
		///
		/// Otwarcie pliku konfiguracyjnego o nawie 'configFileName' i odczytanie 
		/// addresu serwera i przekazanie go do 'address'
		///
		bool openConfFile(std::string & address);

		///
		/// @param [in]	fileName	nazwa pliku konfiguracyjnego
		///
		/// konstruktor
		///
        Server(const char * fileName)
		{
			// stworzenie obiektow baz danych: klienta i serwera
			clientDataBaseObj = boost::shared_ptr<ClientsDataBase>( ClientsDataBase::GetInstance() );
			clientDataBaseObj->Initialize();
			serverDataBaseObj = boost::shared_ptr<ServerDataBase>(ServerDataBase::GetInstance() );
			serverDataBaseObj->Initialize();

			// nazwa pliku konfiguracyjnego
			configFileName = fileName;

			// nadanie wartosci domyslnej dla adresu ip serwera
			myIPAddress.localization = CORBA::string_dup("null");

			//logger
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("ServerLogicRunnable"));
			logger->setLevel(LOGLEVEL);
		}

    public:

		///
		/// @param [in]	fileName	nazwa pliku konfiguracyjnego
		/// @return					wskaznik do instancji obiektu serwera
		///
		/// statyczna metoda zwracajaca wskaznik do obiektu klasy Server jesli
		/// istnieje badz tworzaca go jesli nie istnieje
		///
        static Server * GetInstance(const char * fileName)
		{
			static Server * instance = new Server(fileName);

			return instance;
		}

		///
		/// @return	adres uruchomionego serwera
		///
		/// myIPAddress getter
		///
		static DomainData::Address GetMyIP()
		{
			return Server::myIPAddress;
		}

		///
		/// @param [in]	addr	adres serwera
		///
		/// myIPAddress	setter
		///
		static void SetMyIP(const DomainData::Address addr)
		{
			myIPAddress = addr;
		}

		///
		/// @return wskaznik do obiektu zdalnego udostepnianego serwerom
		///
		/// getter serverImpl
		IServerServer_impl * GetServerImpl()
		{
			return serverImpl;
		}

		///
		/// @return wskaznik do obiektu zdalnego udostepnianego klientom
		///
		/// getter clientImpl;
		///
		IServerClient_impl * GetClientImpl()
		{
			return clientImpl;
		}

		///
		/// @return		 1 - niepowodznie, 0 - zakonczono bez niepowodzen
		///
		/// Odpowiada za wczytanie i pozyskanie danych z pliku konfiguracyjnego i wlaczenie serwera
		/// w trybie macierzystym (tylko nasluchiwanie) badz zwyklym (polaczenie z serwem macierzystym
		/// i wymiana danych a nastepnie przejscie w stan nasluchiwania)
		///
		bool Run();

		///
		/// Stworzenie brokera po stronie serwera, zarejestrownie obiektow zdalnych i uruchomienie
		/// nasluchiwania na porcie SRVPORT
		///
		void ActivateListning();
}; 

#endif
