#ifndef REMOTECLIENTSENDMESSAGEOBSERVER_H
#define REMOTECLIENTSENDMESSAGEOBSERVER_H
//Begin section for file RemoteClientSendMessageObserver.h
//TODO: Add definitions that you want preserved
//End section for file RemoteClientSendMessageObserver.h

#include "IRemoteObserver.h"


class ClientsDataBase;
class ServerDataBase;

//<p>
//    1) Znajdz odpowiedniego klienta (adresata)
//</p>
//<p>
//    2) Jezeli jest do nas pod³¹czony przekaz mu wiadomoœæ
//</p>
//<p>
//    3) Je¿eli nie jest to wykonaj PassMessage na serwerze do którego jest pod³¹czony
//</p>
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class RemoteClientSendMessageObserver : IRemoteObserver
{

    //Begin section for RemoteClientSendMessageObserver
    //TODO: Add attributes that you want preserved
    //End section for RemoteClientSendMessageObserver

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsDataBase * clientsDataBase;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ServerDataBase * serverDataBase;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteClientSendMessageObserver();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteClientSendMessageObserver(RemoteClientSendMessageObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteClientSendMessageObserver & operator =(const RemoteClientSendMessageObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~RemoteClientSendMessageObserver();

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

};  //end class RemoteClientSendMessageObserver

#endif
