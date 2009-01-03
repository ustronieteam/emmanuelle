#include "RemoteServerDisconnectedObserver.h"
//Begin section for file RemoteServerDisconnectedObserver.cpp
//TODO: Add definitions that you want preserved
//End section for file RemoteServerDisconnectedObserver.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteServerDisconnectedObserver::RemoteServerDisconnectedObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteServerDisconnectedObserver::RemoteServerDisconnectedObserver(RemoteServerDisconnectedObserver & arg) 
{
    //TODO Auto-generated method stub
    this->serverDataBase = arg.serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteServerDisconnectedObserver & RemoteServerDisconnectedObserver::operator =(const RemoteServerDisconnectedObserver & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->serverDataBase = arg.serverDataBase;
    }
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteServerDisconnectedObserver::~RemoteServerDisconnectedObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
ServerDataBase * & RemoteServerDisconnectedObserver::get_serverDataBase() 
{
    //TODO Auto-generated method stub
    return serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteServerDisconnectedObserver::set_serverDataBase(ServerDataBase * & serverDataBase) 
{
    //TODO Auto-generated method stub
}
