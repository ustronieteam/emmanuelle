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

		IModel * GetModel();
        void SetModel(IModel * iModel);

        int AddRemoteObserver(IRemoteObserver & observer, ObserverType observerType);
        bool SendFile(int adresat, const char * fileName); // TODO: zmienic typ adresata
        int DeleteContact(const char * name, int number);
        bool SendMessage(const char * content, const char * dest);
        int AddDataObserver(DataObserver & dataObserver);
        int AddContact(const char * name, int number);
        int Disconnect();
        bool ConnectToServer();
        int GetContactsList(); // TODO: zmienic typ zwracany

		///
		///Parametry polaczenia
		void SetServerAddress(const char * serv);
		const char * GetServerAddress() const;
	
		void SetPortNumber(int p);
		int GetPortNumber() const;

};  //end class Controller

#endif
