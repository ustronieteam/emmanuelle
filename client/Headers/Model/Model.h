#ifndef MODEL_H
#define MODEL_H
//Begin section for file Model.h
//TODO: Add definitions that you want preserved
//End section for file Model.h

#include "IModel.h"


class Client;
class ClientsData;

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class Model : IModel
{

    //Begin section for Model
    //TODO: Add attributes that you want preserved
    //End section for Model

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Client * client;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientsData * clientsData;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Model();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Model(Model & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Model & operator =(const Model & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~Model();

        //get client
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline Client * & get_client();

        //set client
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline void set_client(Client * & client);

        //get clientsData
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline ClientsData * & get_clientsData();

        //set clientsData
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline void set_clientsData(ClientsData * & clientsData);

};  //end class Model

#endif
