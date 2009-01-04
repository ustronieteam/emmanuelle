#ifndef PASSMESSAGEOBSERVER_H
#define PASSMESSAGEOBSERVER_H
//Begin section for file PassMessageObserver.h
//TODO: Add definitions that you want preserved
//End section for file PassMessageObserver.h

#include "IRemoteObserver.h"


class ClientsDataBase;

//<p>
//    1)Znajdz klienta docelowego(adresata) - musi byc do nas pod³¹czony (Je¿eli nie to b³¹d.)
//</p>
//<p>
//    2)Przekaz mu wiadomoœæ
//</p>
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class PassMessageObserver : IRemoteObserver
{

    //Begin section for PassMessageObserver
    //TODO: Add attributes that you want preserved
    //End section for PassMessageObserver

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsDataBase * clientsDataBase;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        PassMessageObserver();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        PassMessageObserver(PassMessageObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        PassMessageObserver & operator =(const PassMessageObserver & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~PassMessageObserver();

        //get clientsDataBase
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline ClientsDataBase * & get_clientsDataBase();

        //set clientsDataBase
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline void set_clientsDataBase(ClientsDataBase * & clientsDataBase);

};  //end class PassMessageObserver

#endif
