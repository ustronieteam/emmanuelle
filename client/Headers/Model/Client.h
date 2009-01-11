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

		///
		///Adres zdalnego serwera do ktorego podlaczamy sie
		DomainData::Address serverAddress;

		// logger
		log4cxx::LoggerPtr logger;

		//
		void readServerAddress();
    public:

        Client();
        virtual ~Client();
        int AddFileObserver(IRemoteObserver & fileObserver);
        int SendPackage();
        int ConnectToServer();
        int Disconnect();
        int SendMessage();
        int AddMessageObserver(IRemoteObserver & messageObserver);
		void setServerAddress(std::string address) {}//TODO dokonczyc
		std::string ServerAddress() { return serverAddress.localization.in();}//TODO dokonczyc

};  //end class Client

#endif
