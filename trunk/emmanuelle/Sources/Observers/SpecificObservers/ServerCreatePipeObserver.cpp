#include "ServerCreatePipeObserver.h"
//Begin section for file ServerCreatePipeObserver.cpp
//TODO: Add definitions that you want preserved
//End section for file ServerCreatePipeObserver.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
ServerCreatePipeObserver::ServerCreatePipeObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
ServerCreatePipeObserver::ServerCreatePipeObserver(ServerCreatePipeObserver & arg) 
{
    //TODO Auto-generated method stub
    this->clientsDataBase = arg.clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
ServerCreatePipeObserver & ServerCreatePipeObserver::operator =(const ServerCreatePipeObserver & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->clientsDataBase = arg.clientsDataBase;
    }

	return *this;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
ServerCreatePipeObserver::~ServerCreatePipeObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
ClientsDataBase * & ServerCreatePipeObserver::get_clientsDataBase() 
{
    //TODO Auto-generated method stub
    return clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void ServerCreatePipeObserver::set_clientsDataBase(ClientsDataBase * & clientsDataBase) 
{
    //TODO Auto-generated method stub
}
