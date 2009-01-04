#ifndef REMOTECLIENTCREATEPIPEOBSERVER_H
#define REMOTECLIENTCREATEPIPEOBSERVER_H
//Begin section for file RemoteClientCreatePipeObserver.h
//TODO: Add definitions that you want preserved
//End section for file RemoteClientCreatePipeObserver.h

#include "IRemoteObserver.h"


class ClientsDataBase;
class ServerDataBase;

//<p>
//    1) Znajdz w bazie o klientach, takiego który nie blokuje po³¹czeñ przychodz¹cych i jest pod³¹czony
//</p>
//<p>
//    z aktualnym serwerem i przekaz mu odpowiedni komunikat o tworzeniu pipe'u
//</p>
//<p>
//    2) Je¿eli takiego nie ma to znajdŸ takiego który jest pod³¹czony do innego serwera i przeka¿ temu serwerowi
//</p>
//<p>
//    odpowiedni komunikat (PassCreatePipe?)
//</p>
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class RemoteClientCreatePipeObserver : IRemoteObserver
{

    //Begin section for RemoteClientCreatePipeObserver
    //TODO: Add attributes that you want preserved
    //End section for RemoteClientCreatePipeObserver

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsDataBase * clientsDataBase;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ServerDataBase * serverDataBase;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteClientCreatePipeObserver();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteClientCreatePipeObserver(RemoteClientCreatePipeObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteClientCreatePipeObserver & operator =(const RemoteClientCreatePipeObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~RemoteClientCreatePipeObserver();

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

};  //end class RemoteClientCreatePipeObserver

#endif
