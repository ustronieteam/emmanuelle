#ifndef CONTROLLER_H
#define CONTROLLER_H
//Begin section for file Controller.h
//TODO: Add definitions that you want preserved
//End section for file Controller.h

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

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~Controller();

        //get iModel
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
		IModel * GetModel();

        //set iModel
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        void SetModel(IModel * iModel);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int AddRemoteObserver(IRemoteObserver & observer, ObserverType observerType);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        bool SendFile(int adresat, const char * fileName); // TODO: zmienic typ adresata

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int DeleteContact(const char * name, int number);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        bool SendMessage(const char * content, const char * dest);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int AddDataObserver(DataObserver & dataObserver);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int AddContact(const char * name, int number);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int Disconnect();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        bool ConnectToServer(const char * adres, int port);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int GetContactsList(); // TODO: zmienic typ zwracany

};  //end class Controller

#endif
