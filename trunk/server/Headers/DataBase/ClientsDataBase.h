#ifndef CLIENTSDATABASE_H
#define CLIENTSDATABASE_H
//Begin section for file ClientsDataBase.h
//TODO: Add definitions that you want preserved
//End section for file ClientsDataBase.h

#include "DataBase.h"


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class ClientsDataBase : DataBase
{

    //Begin section for ClientsDataBase
    //TODO: Add attributes that you want preserved
    //End section for ClientsDataBase



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsDataBase();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsDataBase(ClientsDataBase & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsDataBase & operator =(const ClientsDataBase & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~ClientsDataBase();

		virtual int Close();

		virtual int Initialize();

};  //end class ClientsDataBase

#endif
