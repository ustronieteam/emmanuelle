#ifndef CLIENT_H
#define CLIENT_H

#include "IRemoteObserver.h"
#include "IServerClient.h"
//Do Tworzenia logow
#include <log4cxx/logger.h>
#include <log4cxx/level.h>
//Do pliku konfiguracyjnego
#include <boost/program_options.hpp>
#include <string>
#include <fstream>
namespace po = boost::program_options;

///
///@author Marian Szczykulski
///@date	2009-01-10
///@brief	Model klienta zapewnia komunikacje sieciowa, poprzez objekt CORBY
///
class Client
{

	private:
		static const std::string configFileName;
		///
		///Namiastka serwera
		IServerClient_var connectedServerInstance; //Namiastka serwera do którego jestesmy pod³¹czeni
		CORBA::ORB_var orb;

		///
		///Adres zdalnego serwera do ktorego podlaczamy sie
		DomainData::Address serverAddress;
		///
		///tryb polaczenia (active/passive)
		DomainData::Mode mode;
		///
		///nazwa klienta
		std::string clientName;

		///
		///numer klienta
		long clientNumber;

		// logger
		log4cxx::LoggerPtr logger;

		//
		void readServerAddress();
		//Pobiera zdalna instancje
		bool getRemoteServerInstance();
		//Laczy sie z serverem(pobiera instancje)
		bool connectToServerClient(std::string address, CORBA::ORB_out orb, IServerClient_out server);
    public:

		//korzysta z pliku konfiguracyjnego
        Client();
		//Nie korzysta z pliku konfiguracyjnego
		Client(DomainData::Address servAddr);
        virtual ~Client();
        int AddFileObserver(IRemoteObserver & fileObserver);
        int SendPackage();
        int ConnectToServer();
        int Disconnect();
        int SendMessage();
        int AddMessageObserver(IRemoteObserver & messageObserver);

		void setServerAddress(const DomainData::Address & a) {serverAddress = a;}//TODO dokonczyc
		DomainData::Address getServerAddress() { return serverAddress;}

		void setClientName(std::string n){clientName = n;}
		std::string getClientName(){return clientName;}

};  //end class Client

#endif
