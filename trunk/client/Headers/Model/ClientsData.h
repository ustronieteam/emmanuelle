#ifndef CLIENTSDATA_H
#define CLIENTSDATA_H
//Begin section for file ClientsData.h
//TODO: Add definitions that you want preserved
//End section for file ClientsData.h

#include "ClientDataObject.h"


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class ClientsData : ClientDataObject
{

    //Begin section for ClientsData
    //TODO: Add attributes that you want preserved
    //End section for ClientsData



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsData();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsData(ClientsData & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsData & operator =(const ClientsData & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~ClientsData();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int GetContactsList(); // poprawic typ zwracany

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int DeleteContact();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int AddContact();

};  //end class ClientsData

#endif
