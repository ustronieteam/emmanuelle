#ifndef REMOTESERVERDISCONNECTEDOBSERVER_H
#define REMOTESERVERDISCONNECTEDOBSERVER_H
//Begin section for file RemoteServerDisconnectedObserver.h
//TODO: Add definitions that you want preserved
//End section for file RemoteServerDisconnectedObserver.h

#include "IRemoteObserver.h"


class ServerDataBase;

//<p>
//    1) ZnajdŸ odpowiedni serwer(ten który siê roz³¹cza)
//</p>
//<p>
//    2) zaktualizuj jego wpis(usun?)
//</p>
//<p>
//    3)Powiadom wszystkie serwery o zmianie
//</p>
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class RemoteServerDisconnectedObserver : IRemoteObserver
{

    //Begin section for RemoteServerDisconnectedObserver
    //TODO: Add attributes that you want preserved
    //End section for RemoteServerDisconnectedObserver

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ServerDataBase * serverDataBase;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteServerDisconnectedObserver();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteServerDisconnectedObserver(RemoteServerDisconnectedObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteServerDisconnectedObserver & operator =(const RemoteServerDisconnectedObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~RemoteServerDisconnectedObserver();

        //get serverDataBase
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline ServerDataBase * & get_serverDataBase();

        //set serverDataBase
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline void set_serverDataBase(ServerDataBase * & serverDataBase);

};  //end class RemoteServerDisconnectedObserver

#endif
