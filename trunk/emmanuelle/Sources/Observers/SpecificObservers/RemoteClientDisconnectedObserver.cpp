#include "RemoteClientDisconnectedObserver.h"
//Begin section for file RemoteClientDisconnectedObserver.cpp
//TODO: Add definitions that you want preserved
//End section for file RemoteClientDisconnectedObserver.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientDisconnectedObserver::RemoteClientDisconnectedObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientDisconnectedObserver::RemoteClientDisconnectedObserver(RemoteClientDisconnectedObserver & arg) 
{
    //TODO Auto-generated method stub
    this->clientsDataBase = arg.clientsDataBase;
    this->serverDataBase = arg.serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientDisconnectedObserver & RemoteClientDisconnectedObserver::operator =(const RemoteClientDisconnectedObserver & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->clientsDataBase = arg.clientsDataBase;
        this->serverDataBase = arg.serverDataBase;
    }
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientDisconnectedObserver::~RemoteClientDisconnectedObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
ClientsDataBase * & RemoteClientDisconnectedObserver::get_clientsDataBase() 
{
    //TODO Auto-generated method stub
    return clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteClientDisconnectedObserver::set_clientsDataBase(ClientsDataBase * & clientsDataBase) 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
ServerDataBase * & RemoteClientDisconnectedObserver::get_serverDataBase() 
{
    //TODO Auto-generated method stub
    return serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteClientDisconnectedObserver::set_serverDataBase(ServerDataBase * & serverDataBase) 
{
    //TODO Auto-generated method stub
}
