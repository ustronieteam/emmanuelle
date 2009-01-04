#ifndef REMOTECLIENTDISCONNECTEDOBSERVER_H
#define REMOTECLIENTDISCONNECTEDOBSERVER_H
//Begin section for file RemoteClientDisconnectedObserver.h
//TODO: Add definitions that you want preserved
//End section for file RemoteClientDisconnectedObserver.h

#include "IRemoteObserver.h"


class ClientsDataBase;
class ServerDataBase;

//<p>
//    1) Zaktualizuj wpis o kliencie(roz³¹cz)
//</p>
//<p>
//    2)Powiadom wszystkie serwery o zmianie
//</p>
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class RemoteClientDisconnectedObserver : IRemoteObserver
{

    //Begin section for RemoteClientDisconnectedObserver
    //TODO: Add attributes that you want preserved
    //End section for RemoteClientDisconnectedObserver

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsDataBase * clientsDataBase;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ServerDataBase * serverDataBase;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteClientDisconnectedObserver();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteClientDisconnectedObserver(RemoteClientDisconnectedObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteClientDisconnectedObserver & operator =(const RemoteClientDisconnectedObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~RemoteClientDisconnectedObserver();

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

};  //end class RemoteClientDisconnectedObserver

#endif
