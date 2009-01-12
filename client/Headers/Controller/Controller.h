#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "IRemoteObserver.h"
#include "ObserverType.h"
#include "DataObserver.h"
#include <boost/shared_ptr.hpp>
#include "IModel.h"
#include "Model.h"



class IModel;

///
///@author Mateusz Ko³odziejszczyk, Marian Szczykulski
///@date 2009-01-12
///@brief klasa kontrolera
class Controller
{
    private:

        //model
		boost::shared_ptr<IModel> model;
		//prywatny konstruktor (klasa jest singleton-em)
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

		//imp
		IModel * GetModel();
		//imp
        void SetModel(IModel * iModel);

        int AddRemoteObserver(IRemoteObserver & observer, ObserverType observerType);
        bool SendFile(int adresat, const char * fileName); // TODO: zmienic typ adresata
		int AddDataObserver(DataObserver & dataObserver);


		//imp
        int DeleteContact(const char * name, long number);
		//imp
		bool SendMessageToClient(const char * content, const char * dest);
        
		
		
		//imp
        int AddContact(const char * name, long number);
		//imp
        int Disconnect();
		//imp
        bool ConnectToServer();
		//imp
		std::vector<ContactRecord> GetContactsList(); // TODO: zmienic typ zwracany

		///
		///Parametry polaczenia
		void SetServerAddress(const char * serv);
		const char * GetServerAddress() const;
	
		void SetPortNumber(int p);
		int GetPortNumber() const;

		std::string GetOwnName();
		const long & GetOwnNumber();
		bool GetMyAvailability();

		void SetOwnName(const char * c);
		void SetOwnNumber(long l);
		void SetMyAvailability(bool b);

};  //end class Controller

#endif
