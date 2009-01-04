#ifndef REMOTECLIENTCONNECTEDOBSERVER_H
#define REMOTECLIENTCONNECTEDOBSERVER_H
//Begin section for file RemoteClientConnectedObserver.h
//TODO: Add definitions that you want preserved
//End section for file RemoteClientConnectedObserver.h

#include "IRemoteObserver.h"


class ClientsDataBase;
class ServerDataBase;

//<p>
//    1) Znajdz klienta
//</p>
//<p>
//    2) zaktualizuj jego wpis w bazie (dodaj jak nie ma)
//</p>
//<p>
//    3) Powiadom wszystkie serwery o zmianie
//</p>
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class RemoteClientConnectedObserver : IRemoteObserver
{

    //Begin section for RemoteClientConnectedObserver
    //TODO: Add attributes that you want preserved
    //End section for RemoteClientConnectedObserver

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsDataBase * clientsDataBase;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ServerDataBase * serverDataBase;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteClientConnectedObserver();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteClientConnectedObserver(RemoteClientConnectedObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteClientConnectedObserver & operator =(const RemoteClientConnectedObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~RemoteClientConnectedObserver();

        //get clientsDataBase
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline ClientsDataBase * & get_clientsDataBase();

        //set clientsDataBase
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline void set_clientsDataBase(ClientsDataBase * & clientsDataBase);

        //get serverDataBase
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline ServerDataBase * & get_serverDataBase();

        //set serverDataBase
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline void set_serverDataBase(ServerDataBase * & serverDataBase);

};  //end class RemoteClientConnectedObserver

#endif
