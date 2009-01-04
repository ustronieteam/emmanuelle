#ifndef REMOTESERVERCONNECTEDOBSERVER_H
#define REMOTESERVERCONNECTEDOBSERVER_H
//Begin section for file RemoteServerConnectedObserver.h
//TODO: Add definitions that you want preserved
//End section for file RemoteServerConnectedObserver.h

#include "IRemoteObserver.h"


class ServerDataBase;

//<h4>
//    Odpowiedz na Join()
//</h4>
//<p>
//    1) Dodaj nowy serwer do bazy
//</p>
//<p>
//    2) Pobierz liste wszystkich serwerów
//</p>
//<p>
//    3) Do ka¿dego serwera z listy dodaj nowy serwer (AddServer)
//</p>
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class RemoteServerConnectedObserver : IRemoteObserver
{

    //Begin section for RemoteServerConnectedObserver
    //TODO: Add attributes that you want preserved
    //End section for RemoteServerConnectedObserver

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ServerDataBase * serverDataBase;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteServerConnectedObserver();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteServerConnectedObserver(RemoteServerConnectedObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteServerConnectedObserver & operator =(const RemoteServerConnectedObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~RemoteServerConnectedObserver();

        //get serverDataBase
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline ServerDataBase * & get_serverDataBase();

        //set serverDataBase
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline void set_serverDataBase(ServerDataBase * & serverDataBase);

};  //end class RemoteServerConnectedObserver

#endif
