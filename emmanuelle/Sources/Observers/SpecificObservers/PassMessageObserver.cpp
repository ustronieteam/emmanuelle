#include "PassMessageObserver.h"
//Begin section for file PassMessageObserver.cpp
//TODO: Add definitions that you want preserved
//End section for file PassMessageObserver.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
PassMessageObserver::PassMessageObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
PassMessageObserver::PassMessageObserver(PassMessageObserver & arg) 
{
    //TODO Auto-generated method stub
    this->clientsDataBase = arg.clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
PassMessageObserver & PassMessageObserver::operator =(const PassMessageObserver & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->clientsDataBase = arg.clientsDataBase;
    }
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
PassMessageObserver::~PassMessageObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
ClientsDataBase * & PassMessageObserver::get_clientsDataBase() 
{
    //TODO Auto-generated method stub
    return clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void PassMessageObserver::set_clientsDataBase(ClientsDataBase * & clientsDataBase) 
{
    //TODO Auto-generated method stub
}
