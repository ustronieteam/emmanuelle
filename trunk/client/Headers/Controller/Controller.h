#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "IRemoteObserver.h"
#include "ObserverType.h"
#include "DataObserver.h"
#include <boost/shared_ptr.hpp>
#include "IModel.h"
#include "Model.h"
#include <fstream>


class IModel;

///
///@author Mateusz Ko³odziejszczyk, Marian Szczykulski
///@date 2009-01-12
///@brief klasa kontrolera
class Controller
{
    private:

		///
        /// wkaznik obiektu modelu
		///
		boost::shared_ptr<IModel> model;
		
		///
		/// prywatny konstruktor domyslny
		///
        Controller();

		// logger
		log4cxx::LoggerPtr logger;

    public:
	
        static Controller * GetInstance()
		{
			static Controller * instance = new Controller();

			return instance;
		}
        virtual ~Controller();

		///
		/// getter modelu
		///
		IModel * GetModel();
		
		///
		/// setter modelu
		///
        void SetModel(IModel * iModel);

		///
		/// @brief Rejestruje odpowiedniego obserwatora zdalnej instancji
		/// @param [in]	observer	Wskaznik na odpowiedniego obserwatora
		/// @param [in]	observerType	Typ obserwatora
		/// @return status wykonania operacji
		///
        int AddRemoteObserver(IRemoteObserver * observer, ObserverType observerType);

		///
		///@brief Wysylanie pliku
		///@param[in]	adresat	Adresat do ktorego wysylany jest plik
		///@param[in]	filename	nazwa pliku
		///@return	status wysylania
		///
        bool SendFile(const char *adresat, const char * fileName);

		///
		///@brief	Usuwa kontakt z bazy kontaktow
		///@return	0  udalo sie usunac kontakt
		///			-1 nie udalo sie usunac
		///
		int AddDataObserver(DataObserver * dataObserver);

		///
		///@brief Metoda wykonuje logike potrzebna do wyslania wiadomosci do innego klienta
		///@param[in] content	tresc wiadomosci do wyslania
		///@param[in] dest		nazwa klienta do ktorego wysylana jest wiadomosc
		///@return				true  - wiadomosc wyslana pomyslnie
		///						false - w przeciwnym przypadku
		///
        int DeleteContact(const char * name, long number);

		///
		///@brief dodaje obserwatora statusu (danych w ogolnosci)
		///@param[in]	dataObserver	Obserwator danych
		///@return		status wykonania operacji
		///
		bool SendMessageToClient(const char * content, const char * dest);
        
		///
		///@brief Dodanie kontaktu do bazy
		///@param[in]	name	nazwa klienta(ktorego chcemy miec w liscie kontaktow)
		///@param[in]	number	numer klienta(ktorego chcemy miec w liscie kontaktow)
		///
        int AddContact(const char * name, long number);

		///
		///@brief Rozlaczanie sie klienta od serwera
		///@return -2 nie zainicjowana zdalna instancja (nie podlaczylismy sie)
		///@return -1 serwer nie jest dostepny (wystapil wyjatek przy wywolywaniu zdalnej metody)
		///@return	0 udalo sie rozlaczyc
		///
        int Disconnect();
		
		///
		///@brief  skupia logike, wykonywana podczas ³¹czenia siê do serwera.
		///
        bool ConnectToServer();
		
		///
		///@brief Pobiera liste kontaktow z Modelu
		///@return	vector kontaktow
		///
		std::vector<ContactRecord> GetContactsList(); // TODO: zmienic typ zwracany

		///
		///@brief setter adresu serwera do ktorego mamy sie podlaczyc
		///@param[in]	serv	adres serwera do ktorego mamy sie podlaczyc
		///
		void SetServerAddress(const char * serv);

		///
		///@brief getter adresu serwera do ktorego mamy sie podlaczyc
		///@return	adres serwera do ktorego mamy sie podlaczyc
		///
		const char * GetServerAddress() const;
	
		///
		///@brief setter portu przez ktory mamy sie laczyc
		///@param[in]	p	port przez ktory mamy sie laczyc
		///
		void SetPortNumber(int p);

		///
		///@brief getter portu przez ktory mamy sie laczyc
		///@return	port przez ktory mamy sie laczyc
		///
		int GetPortNumber() const;

		///
		///@brief getter portu przez ktory mamy sie laczyc
		///@return	port przez ktory mamy sie laczyc
		///
		std::string GetOwnName();

		///
		///@brief	Zwraca wlasny rekord z danymi
		///@return	wlasny rekord z danymi
		///
		const long GetOwnNumber();

		///
		///@brief	Zwraca wlasny rekord z danymi
		///@return	wlasny rekord z danym
		///
		bool GetMyAvailability();

		///
		///@brief setter nazwy lokalnego klienta
		///
		void SetOwnName(const char * c);

		///
		///@brief setter numeru lokalnego klienta
		///
		void SetOwnNumber(long l);
		
		///
		///@brief setter dostepnosci lokalnego klienta
		///
		void SetMyAvailability(bool b);
		void testClient(std::string str);
		void setOwnMode(DomainData::Mode m){model->setOwnMode(m);}
		DomainData::Mode getOwnMode(){return model->getOwnMode();}

};  //end class Controller

#endif
