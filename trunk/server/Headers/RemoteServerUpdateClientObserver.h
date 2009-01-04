#ifndef REMOTESERVERUPDATECLIENTOBSERVER_H
#define REMOTESERVERUPDATECLIENTOBSERVER_H
//Begin section for file RemoteServerUpdateClientObserver.h
//TODO: Add definitions that you want preserved
//End section for file RemoteServerUpdateClientObserver.h

#include "IRemoteObserver.h"


class ClientsDataBase;
class ServerDataBase;

//<br />
//<p>
//    1)Znajdz klienta
//</p>
//<p>
//    2) Wprowaz zmiany w jego rekordzie
//</p>
//<p>
//    3)Powiadom wszystkie serwery o zmianie
//</p><br />
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class RemoteServerUpdateClientObserver : IRemoteObserver
{

    //Begin section for RemoteServerUpdateClientObserver
    //TODO: Add attributes that you want preserved
    //End section for RemoteServerUpdateClientObserver

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsDataBase * clientsDataBase;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ServerDataBase * serverDataBase;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteServerUpdateClientObserver();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteServerUpdateClientObserver(RemoteServerUpdateClientObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteServerUpdateClientObserver & operator =(const RemoteServerUpdateClientObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~RemoteServerUpdateClientObserver();

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

};  //end class RemoteServerUpdateClientObserver

#endif
