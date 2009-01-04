#ifndef SERVERCREATEPIPEOBSERVER_H
#define SERVERCREATEPIPEOBSERVER_H
//Begin section for file ServerCreatePipeObserver.h
//TODO: Add definitions that you want preserved
//End section for file ServerCreatePipeObserver.h

#include "IRemoteObserver.h"


class ClientsDataBase;

//<p>
//    1)Klientowi kt�ry ma tworzy� pipe przeka� odpowiedni� wiadomo��.
//</p>
//<p>
//    &nbsp;Klient ten musi by� z nami pod��czony, je�eli nie to b�ad integralno�ci danych w bazie.
//</p>
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class ServerCreatePipeObserver : IRemoteObserver
{

    //Begin section for ServerCreatePipeObserver
    //TODO: Add attributes that you want preserved
    //End section for ServerCreatePipeObserver

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsDataBase * clientsDataBase;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ServerCreatePipeObserver();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ServerCreatePipeObserver(ServerCreatePipeObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ServerCreatePipeObserver & operator =(const ServerCreatePipeObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~ServerCreatePipeObserver();

        //get clientsDataBase
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline ClientsDataBase * & get_clientsDataBase();

        //set clientsDataBase
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline void set_clientsDataBase(ClientsDataBase * & clientsDataBase);

};  //end class ServerCreatePipeObserver

#endif
