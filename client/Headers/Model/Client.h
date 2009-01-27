#ifndef CLIENT_H
#define CLIENT_H

#include "IRemoteObserver.h"
#include "IServerClient.h"
#include "IClientClient.h"
//Do Tworzenia logow
#include <log4cxx/logger.h>
#include <log4cxx/level.h>
//Do pliku konfiguracyjnego
#include <boost/program_options.hpp>
#include <string>
#include <fstream>
#include "ClientsData.h"
#include "ContactRecord.h"

#include "CorbaConnector.h"

namespace po = boost::program_options;

///
///@author Marian Szczykulski
///@date	2009-01-10
///@brief	Model klienta zapewnia komunikacje sieciowa, poprzez objekt CORBY
///
class Client : public CorbaConnector
{

	private:
		static const int defaultPortNumber;
		static const std::string configFileName;
		///
		///Namiastka serwera
		///
		IServerClient_var connectedServerInstance; //Namiastka serwera do którego jestesmy pod³¹czeni
		CORBA::ORB_var orb;

		///
		///Adres zdalnego serwera do ktorego podlaczamy sie
		///
		DomainData::Address serverAddress;

		///
		///port
		///
		int port;
		///
		///tryb polaczenia (active/passive)
		///
		DomainData::Mode mode;
		///
		///nazwa klienta/
		///
		std::string clientName;

		///
		///numer klienta
		///
		long clientNumber;

		// logger
		log4cxx::LoggerPtr logger;

		void readServerAddress();
		
		///
		///Pobiera zdalna instancje
		///
		bool getRemoteServerInstance();
		IClientClient_var getRemoteClientInstance(CORBA::ORB_var & orbClient, DomainData::Address clAddr);
		//Laczy sie z serverem(pobiera instancje)
		//bool connectToServerClient(std::string address, CORBA::ORB_out orb, IServerClient_out server);
    public:

		//korzysta z pliku konfiguracyjnego
        Client();
		//Nie korzysta z pliku konfiguracyjnego
		Client(DomainData::Address servAddr);
        virtual ~Client();
        int AddFileObserver(IRemoteObserver & fileObserver);
        int SendPackage(DomainData::User usr, DomainData::User sender, DomainData::File & file);

        int ConnectToServer();
		int Disconnect(DomainData::User & usr);

		int SendMessageToClient(DomainData::User sender, DomainData::User receiver, DomainData::Message msg);
        int AddMessageObserver(IRemoteObserver & messageObserver);

		bool CheckStatus(DomainData::User usr);

		///
		///gettery i settery dla nazwy serwera do ktorego sie podlaczamy
		///
		void setServerAddress(const DomainData::Address & a) {serverAddress = a;readServerAddress();}//TODO dokonczyc
		const DomainData::Address & getServerAddress() const{ return serverAddress;}

		///
		///gettery i settery dla nazwy lokalnego klienta
		///
		void setClientName(const std::string & n){clientName = n;}
		const std::string & getClientName() const {return clientName;}

		///
		///gettery i settery dla portu
		///
		void setPortNumber(const int & p){port = p;}
		const int & getPortNumber()const {return port;}

		void TestCLNT(std::string address)
		{
			CORBA::ORB_var orb;
			IClientClient_ptr client;
			LOG4CXX_DEBUG(logger, "Uruchomiono test na kliencie ...");
			connectToClientClient(address, orb, client); 
			LOG4CXX_DEBUG(logger, "...koniec testu na kliencie.");
		}

};  //end class Client

#endif
