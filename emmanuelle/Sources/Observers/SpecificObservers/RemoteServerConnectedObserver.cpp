#include "RemoteServerConnectedObserver.h"
//Begin section for file RemoteServerConnectedObserver.cpp
//TODO: Add definitions that you want preserved
//End section for file RemoteServerConnectedObserver.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteServerConnectedObserver::RemoteServerConnectedObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteServerConnectedObserver::RemoteServerConnectedObserver(RemoteServerConnectedObserver & arg) 
{
    //TODO Auto-generated method stub
    this->serverDataBase = arg.serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteServerConnectedObserver & RemoteServerConnectedObserver::operator =(const RemoteServerConnectedObserver & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->serverDataBase = arg.serverDataBase;
    }

	return const_cast<RemoteServerConnectedObserver &>(arg);
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteServerConnectedObserver::~RemoteServerConnectedObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
ServerDataBase * & RemoteServerConnectedObserver::get_serverDataBase() 
{
    //TODO Auto-generated method stub
    return serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteServerConnectedObserver::set_serverDataBase(ServerDataBase * & serverDataBase) 
{
    //TODO Auto-generated method stub
}
