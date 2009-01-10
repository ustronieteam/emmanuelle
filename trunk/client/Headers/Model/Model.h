#ifndef MODEL_H
#define MODEL_H
//Begin section for file Model.h
//TODO: Add definitions that you want preserved
//End section for file Model.h

#include "IModel.h"


class Client;
class ClientsData;

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class Model : IModel
{

    //Begin section for Model
    //TODO: Add attributes that you want preserved
    //End section for Model

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Client * client;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsData * clientsData;

		Model();

    public:

        static Model * GetInstance()
		{
			static Model * instance = new Model();

			return instance;
		}

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~Model();

        //get client
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Client * & get_client();

        //set client
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        void set_client(Client * & client);

        //get clientsData
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsData * & get_clientsData();

        //set clientsData
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        void set_clientsData(ClientsData * & clientsData);

		//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         int AddStatusObserver(DataObserver & observer) ;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         int SendPackage(FilePackage package);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         int DeleteContact() ;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         int SendMessage() ;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         int AddContact() ;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         int Disconnect() ;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         bool ConnectToServer() ;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         int AddFileObserver(IRemoteObserver & observer) ;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         int AddMessageObserver(IRemoteObserver & observer) ;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
          int GetContactsList(); // TODO: zmienic typ zwracany

};  //end class Model

#endif
