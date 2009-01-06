#ifndef SERVER_H
#define SERVER_H

#include "DataBase.h"
#include "DataBase/ClientsDataBase.h"
#include "DataBase/ServerDataBase.h"
#include "CorbaClasses/ServerInterfaces.h"
#include "CorbaClasses/ServerInterfaces_impl.h"

#include <OB/CORBA.h>
#include <OB/BootManager.h>

#include <iostream>
#include <fstream>
#include <string>

#include <log4cxx/logger.h>
#include <log4cxx/level.h>


const std::string VADDRESS = "localhost";
const std::string VPORT = "6666";
const std::string NADDRESS = "address";
const std::string NPORT = "port";

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
		/// @param [address]	adres serwera macierzystego
		/// @param [port]		port na ktorym masluchuje serwer macierzysty
		/// @return				0 - powodzneie, 1 - niepowodzenie
		///
        /// Inicjalizacja servera.
        ///    Utworzenie objektów zdalnych i wrzucenie go na broker(udostêpnienie)
        ///    Ponad to nale¿y zainstalowaæ ka¿demu obiektowi zdalnemu po jednym obserwatorze
        ///    Tworzac obserwatorów nale¿y im dostarczyæ odpowiedniegi obiektu&nbsp;bazy danych
		///
		bool init(std::string address, std::string port);

		///
		///	@param [address]	miejsce gdzie ma byc zapisany adress serwera mecierzystego odczytany z pliku
		/// @param [port]		miejsce gdzie ma byc zapisany port serwera macierzystego odczytany z pliku
		/// @return				0 - powodzenie, 1 - niepowodzenie
		///
		/// Otwarcie pliku konfiguracyjnego o nawie 'configFileName' i odczytanie 
		/// numerow: portu i addresu serwera i przekazanie ich do 'address' i 'port'
		///
		bool openConfFile(std::string & address, std::string & port);


    public:

		///
		/// @param [fileName]	nazwa pliku konfiguracyjnego
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

		///
		/// destruktor
		///
        virtual ~Server()
		{
		}

		///
		/// @param [fileName]	nazwa pliku konfiguracyjnego
		/// @return				wskaznik do instancji obiektu serwera
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
		bool Run();
}; 

#endif
