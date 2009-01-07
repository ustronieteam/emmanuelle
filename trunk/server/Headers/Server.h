#ifndef SERVER_H
#define SERVER_H

#include "DataBase.h"
#include "DataBase/ClientsDataBase.h"
#include "DataBase/ServerDataBase.h"
#include "IServerServer.h"
#include "IServerServer_impl.h"
#include "IServerClient.h"
#include "IServerClient_impl.h"

#include <OB/CORBA.h>
#include <OB/BootManager.h>

#include <iostream>
#include <fstream>
#include <string>

#include <log4cxx/logger.h>
#include <log4cxx/level.h>


const std::string NADDRESS = "address";

const std::string LPORT = "7080";

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
		ClientsDataBase * clientDataBaseObj;

		///
		/// wskaznik do bazy danych aktywnych serwerow
		///
		ServerDataBase * serverDataBaseObj;

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
		/// @param [in]		address	adres serwera do ktorego chcemy sie polaczyc
		/// @param [in]		port	port na ktorym nasluchuje ten serwer
		/// @param [out]	orb		wsk na obiekt brokera - trzyma polaczenie
		/// @param [out]	server	wsk na obiekt namiastki
		/// @return			0 - powodznie, 1 - niepowodzenie
		///
		/// Laczy sie do serwera o zadanym adresie nasluchujacym na podanym porcie; efektem polaczenia jest 
		/// zwrocenie wskaznikow do brokera polaczenia i obiektu namastki
		///
		bool connectToServer(string address, string port, CORBA::ORB_out orb, IServerServer_out server);

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
			this->clientDataBaseObj = new ClientsDataBase();
			this->serverDataBaseObj = new ServerDataBase();

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
		/// @return		 1 - niepowodznie, 0 - zakonczono bez niepowodzen
		///
		/// Odpowiada za wczytanie i pozyskanie danych z pliku konfiguracyjnego i wlaczenie serwera
		/// w trybie macierzystym (tylko nasluchiwanie) badz zwyklym (polaczenie z serwem macierzystym
		/// i wymiana danych a nastepnie przejscie w stan nasluchiwania)
		///
		bool Run();
}; 

#endif
