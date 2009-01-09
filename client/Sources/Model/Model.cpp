#include "Model.h"
//Begin section for file Model.cpp
//TODO: Add definitions that you want preserved
//End section for file Model.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Model::Model() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Model::Model(Model & arg) 
{
    //TODO Auto-generated method stub
    this->client = arg.client;
    this->clientsData = arg.clientsData;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Model & Model::operator =(const Model & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->client = arg.client;
        this->clientsData = arg.clientsData;
    }

	return *this;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Model::~Model() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Client * & Model::get_client() 
{
    //TODO Auto-generated method stub
    return client;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void Model::set_client(Client * & client) 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
ClientsData * & Model::get_clientsData() 
{
    //TODO Auto-generated method stub
    return clientsData;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void Model::set_clientsData(ClientsData * & clientsData) 
{
    //TODO Auto-generated method stub
}
