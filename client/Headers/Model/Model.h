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
		
		///
		/// obiekt brokera
		///
		CORBA::ORB_var orb;

		///
		/// wskaznik do obiektu klienta
		///
		boost::shared_ptr<Client> client;

		///
		/// wskaznik do bazy klienta 
		///
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

		///
		/// aktywnosc klienta
		///
		bool isActive;

		// logger
		log4cxx::LoggerPtr logger;

		///
		/// prywatny konstruktor
		///
		Model()
		{
			isActive = false;
			
			//logger
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("Model"));
			logger->setLevel(LOGLEVEL);

			client = boost::shared_ptr<Client>(new Client(serverAddress) );
			clientsData = boost::shared_ptr<ClientsData>(new ClientsData(true));
		}



    public:

		///
		/// Stworzenie brokera po stronie klienta, zarejestrownie obiektow zdalnych i uruchomienie
		/// nasluchiwania na porcie CLNTPORT; musi zostac wywolana dopiero po polaczeniu z serwerem
		///
		virtual void activateListning();
		
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

		///
		/// setter portu
		///
		virtual void SetPortNumber(const int & p);
		
		///
		/// getter portu
		///
		virtual int GetPortNumber() const;

		///
		/// @param [in] observ		wsk na obserwatora
		/// @param [in]	type		typ obserwatora
		///
		/// rejestruje obserwatora w programie
		///
		virtual int RegisterObserver(IRemoteObserver * observ, ObserverType type);
		
		///
		/// wyrejstrowuje obserwatora
		///
		virtual int UnregisterObserver();

		///
		///
		///
        int AddStatusObserver(DataObserver * observer) ;

		///
		///
		///
		int SendPackage(DomainData::User & usr,DomainData::File & f);

		///
		/// @param [in]	usr		usuwany kontakt
		/// @return				0 udalo sie usunac lub rzuca wyjatek ContactNotFoundException jak sie nie udalo
		///
		/// Usuwa kontakt z bazy
		///
        int DeleteContact(const DomainData::User & usr) ;

		///
		/// @param [in] sender		nadawca wiadomosci
		/// @param [in] receiver	adresat wiadomosci
		/// @param [in] msg			wiadomosc
		/// @return					status (-2 zdalna instancja serwera nie zainicjowana,
		///							-1 blad podczas wywolywania zdalnej metody serwera)
		///
		/// Wysylanie wiadomosci do klienta
		///
        virtual int SendMessageToClient(DomainData::User sender, DomainData::User receiver, DomainData::Message msg);

		///
		/// @param [in]	usr		Dane o dodawanym uzytkowniku
		/// @return				0 lub rzuca wyjatek jezeli nie udalo sie dodac
		///
		/// Dodaje kontakt do bazy kontaktow
		///
        int AddContact(const DomainData::User &usr) ;

		///
		/// Rozlaczanie sie z serwera
		///
        int Disconnect() ;

		/// 
		/// Pod³¹czanie do servera
		///
        bool ConnectToServer() ;

		///
		///
		///
        int AddFileObserver(IRemoteObserver & observer) ;

		///
		///
		///
        int AddMessageObserver(IRemoteObserver & observer) ;

		///
		/// @return		vector kontaktow
		///
		/// Pobiera liste kontaktow z bazy
		///
		virtual std::vector<ContactRecord> GetContactsList(); 

		///
		/// @return		wlasny rekord z danymi
		/// 
		/// Zwraca wlasny rekord z danymi
		///
		virtual std::string GetOwnName();

		///
		/// @return		wlasny rekord z danymi
		///
		/// Zwraca wlasny rekord z danymi
		///
		virtual const long GetOwnNumber();

		///
		/// @return		wlasny rekord z danymi
		///
		/// Zwraca wlasny rekord z danymi
		///
		virtual bool GetMyAvailability();

		///
		/// setter nazwy lokalnego klienta
		/// 
		virtual void SetOwnName(const char * c);

		///
		/// setter numeru lokalnego klienta
		///
		virtual void SetOwnNumber(long l);
		
		///
		/// setter dostepnosci lokalnego klienta
		///
		virtual void SetMyAvailability(bool b);
		
		///
		/// uruchamia w odzielnym watku cheker-a ktory sprawdza 
		/// co okreslony czas status wszystkich uzytkownikuw na liscie kontaktow
		///
		virtual bool runStatusChecker();

		// test
		virtual void TestClient(std::string addrClient);

};  //end class Model

#endif
