#include "Controller.h"
//Begin section for file Controller.cpp
//TODO: Add definitions that you want preserved
//End section for file Controller.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Controller::Controller() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Controller::Controller(Controller & arg) 
{
    //TODO Auto-generated method stub
    this->iModel = arg.iModel;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Controller & Controller::operator =(const Controller & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->iModel = arg.iModel;
    }

	return *this;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Controller::~Controller() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
IModel * & Controller::get_iModel() 
{
    //TODO Auto-generated method stub
    return iModel;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void Controller::set_iModel(IModel * & iModel) 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int Controller::AddRemoteObserver(IRemoteObserver_0 & observer, ObserverType observerType) 
{
    //TODO Auto-generated method stub
    return 0;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
bool Controller::SendFile(int adresat, const char * fileName) 
{
    //TODO Auto-generated method stub
    return 0;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int Controller::DeleteContact(const char * name, int number) 
{
    //TODO Auto-generated method stub
    return 0;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
bool Controller::SendMessage(const char * content, const char * dest) 
{
    //TODO Auto-generated method stub
    return 0;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int Controller::AddDataObserver(DataObserver & dataObserver) 
{
    //TODO Auto-generated method stub
    return 0;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int Controller::AddContact(const char * name, int number) 
{
    //TODO Auto-generated method stub
    return 0;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int Controller::Disconnect() 
{
    //TODO Auto-generated method stub
    return 0;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
bool Controller::ConnectToServer(const char * adres, int port) 
{
    //TODO Auto-generated method stub
    return 0;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int Controller::GetContactsList() // TODO: poprawic typ zwracany
{
    //TODO Auto-generated method stub
    return 0;
}
