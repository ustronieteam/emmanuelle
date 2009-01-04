#include "RemoteClientCreatePipeObserver.h"
//Begin section for file RemoteClientCreatePipeObserver.cpp
//TODO: Add definitions that you want preserved
//End section for file RemoteClientCreatePipeObserver.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientCreatePipeObserver::RemoteClientCreatePipeObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientCreatePipeObserver::RemoteClientCreatePipeObserver(RemoteClientCreatePipeObserver & arg) 
{
    //TODO Auto-generated method stub
    this->clientsDataBase = arg.clientsDataBase;
    this->serverDataBase = arg.serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientCreatePipeObserver & RemoteClientCreatePipeObserver::operator =(const RemoteClientCreatePipeObserver & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->clientsDataBase = arg.clientsDataBase;
        this->serverDataBase = arg.serverDataBase;
    }

	return const_cast<RemoteClientCreatePipeObserver &>(arg);
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientCreatePipeObserver::~RemoteClientCreatePipeObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
ClientsDataBase * & RemoteClientCreatePipeObserver::get_clientsDataBase() 
{
    //TODO Auto-generated method stub
    return clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteClientCreatePipeObserver::set_clientsDataBase(ClientsDataBase * & clientsDataBase) 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
ServerDataBase * & RemoteClientCreatePipeObserver::get_serverDataBase() 
{
    //TODO Auto-generated method stub
    return serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteClientCreatePipeObserver::set_serverDataBase(ServerDataBase * & serverDataBase) 
{
    //TODO Auto-generated method stub
}
