#ifndef SERVER_H
#define SERVER_H

#include <OB/CORBA.h>
#include <OB/BootManager.h>
#include <OB/OCI_IIOP.h>

#include "DataBase/ClientsDataBase.h"
#include "DataBase/ServerDataBase.h"
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

#include <iostream>
#include <fstream>
#include <string>

#include <log4cxx/logger.h>
#include <log4cxx/level.h>


const std::string NADDRESS = "address";

static const std::string LPORT = "7080";

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
class Server
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

		IServerServer_impl * serverImpl;

		IServerClient_impl * clientImpl;

		///
		/// nazwa pliku konfiguracyjnego
		///
        const char * configFileName;

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
		/// Stworzenie brokera po stronie serwera, zarejestrownie obiektow zdalnych i uruchomienie
		/// nasluchiwania na porcie PORT
		///
		void activateListning();

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

			//logger
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("ServerLogicRunnable"));
			logger->setLevel(log4cxx::Level::getAll());
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
		/// statyczna metoda sluzaca do pobrania adresu serwera juz podlaczonego
		/// do danego serwera
		///
		static char * GetRemotedAddress()
		{
			char* orb_options[] = { "-OAport", const_cast<char *>(LPORT.c_str()) };
			int optc = sizeof(orb_options)/sizeof(char *);

			CORBA::ORB_var orb = CORBA::ORB_init(optc, orb_options);

			CORBA::Object_var baseCurrent = orb->resolve_initial_references("OCICurrent");
			OCI::Current_var current = OCI::Current::_narrow(baseCurrent);
		 
			OCI::TransportInfo_var info = current->get_oci_transport_info();
			OCI::IIOP::TransportInfo_var iiopInfo = OCI::IIOP::TransportInfo::_narrow(info);

			if(CORBA::is_nil(iiopInfo))
				return "";

			return iiopInfo->remote_addr();
		}

		///
		/// @param [in]		address	adres serwera do ktorego chcemy sie polaczyc
		/// @param [out]	orb		wsk na obiekt brokera - trzyma polaczenie
		/// @param [out]	server	wsk na obiekt namiastki
		/// @return			0 - powodznie, 1 - niepowodzenie
		///
		/// Laczy sie do serwera o zadanym adresie nasluchujacym na porcie LPORT; efektem polaczenia jest 
		/// zwrocenie wskaznikow do brokera polaczenia i obiektu namastki
		///
		static bool connectToServer(std::string address, CORBA::ORB_out orb, IServerServer_out server)
		{
			char* orb_options[] = { const_cast<char *>(address.c_str()) , const_cast<char *>(LPORT.c_str()) };
			int optc = sizeof(orb_options)/sizeof(char *);

			orb = CORBA::ORB_init(optc, orb_options);

			CORBA::String_var strIOR = CORBA::string_dup("corbaloc:iiop:");
			strIOR += address.c_str();
			strIOR += ":";
			strIOR += LPORT.c_str();
			strIOR += "/serverserver";

			CORBA::Object_var oServer = orb->string_to_object(strIOR);
			if (CORBA::is_nil(oServer))
			{
				return 1;
			}

			server = IServerServer::_narrow(oServer);
		    
			if (CORBA::is_nil(server))
			{
				return 1;
			}

			return 0;
		}

		///
		/// @param [in]		address	adres serwera do ktorego chcemy sie polaczyc
		/// @param [out]	orb		wsk na obiekt brokera - trzyma polaczenie
		/// @param [out]	client	wsk na obiekt namiastki
		/// @return			0 - powodznie, 1 - niepowodzenie
		///
		/// Laczy sie do klienta o zadanym adresie nasluchujacym na porcie LPORT; efektem polaczenia jest 
		/// zwrocenie wskaznikow do brokera polaczenia i obiektu namastki
		///
		static bool connectToClient(std::string address, CORBA::ORB_out orb, IClientServer_out client)
		{
			return 0;
		}

		///
		/// @return		 1 - niepowodznie, 0 - zakonczono bez niepowodzen
		///
		/// Odpowiada za wczytanie i pozyskanie danych z pliku konfiguracyjnego i wlaczenie serwera
		/// w trybie macierzystym (tylko nasluchiwanie) badz zwyklym (polaczenie z serwem macierzystym
		/// i wymiana danych a nastepnie przejscie w stan nasluchiwania)
		///
		bool Run();
}; 

#endif
