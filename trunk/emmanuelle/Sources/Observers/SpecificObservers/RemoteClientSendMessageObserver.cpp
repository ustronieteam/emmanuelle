#include "RemoteClientSendMessageObserver.h"
//Begin section for file RemoteClientSendMessageObserver.cpp
//TODO: Add definitions that you want preserved
//End section for file RemoteClientSendMessageObserver.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientSendMessageObserver::RemoteClientSendMessageObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientSendMessageObserver::RemoteClientSendMessageObserver(RemoteClientSendMessageObserver & arg) 
{
    //TODO Auto-generated method stub
    this->clientsDataBase = arg.clientsDataBase;
    this->serverDataBase = arg.serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientSendMessageObserver & RemoteClientSendMessageObserver::operator =(const RemoteClientSendMessageObserver & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->clientsDataBase = arg.clientsDataBase;
        this->serverDataBase = arg.serverDataBase;
    }

	return const_cast<RemoteClientSendMessageObserver &>(arg);
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientSendMessageObserver::~RemoteClientSendMessageObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
ClientsDataBase * & RemoteClientSendMessageObserver::get_clientsDataBase() 
{
    //TODO Auto-generated method stub
    return clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteClientSendMessageObserver::set_clientsDataBase(ClientsDataBase * & clientsDataBase) 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
ServerDataBase * & RemoteClientSendMessageObserver::get_serverDataBase() 
{
    //TODO Auto-generated method stub
    return serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteClientSendMessageObserver::set_serverDataBase(ServerDataBase * & serverDataBase) 
{
    //TODO Auto-generated method stub
}
