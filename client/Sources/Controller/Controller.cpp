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
Controller::~Controller() 
{
    //TODO Auto-generated method stub
}

///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief getter modelu
IModel * Controller::GetModel() 
{
    return model->get();
}

///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief setter modelu
void Controller::SetModel(IModel * iModel) 
{
	model = boost::shared_ptr<IModel>(iModel);
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int Controller::AddRemoteObserver(IRemoteObserver & observer, ObserverType observerType) 
{
    //TODO Auto-generated method stub
    return 0;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
bool Controller::SendFile(int adresat, const char * fileName) // TODO: zmienic typ adresata 
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

///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief Rozlaczanie sie klienta od serwera
///@return -2 nie zainicjowana zdalna instancja (nie podlaczylismy sie)
///@return -1 serwer nie jest dostepny (wystapil wyjatek przy wywolywaniu zdalnej metody)
///@return	0 udalo sie rozlaczyc
int Controller::Disconnect() 
{
	int result = 0;
	result = model->Disconnect();
	return result;
}

///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief  skupia logike, wykonywana podczas ³¹czenia siê do serwera.
bool Controller::ConnectToServer(const char * adres, int port) 
{
	try
	{
		LOG4CXX_DEBUG(logger "Podlaczanie do pierwszego servera");
		while(!model->ConnectToServer())//Dopuki serwer nam odsyla inny adres do podlaczenia
		{
			LOG4CXX_INFO(logger "Podlaczanie do kolejnego servera");
		}
	}
	catch(std::exception & e)
	{
		LOG4CXX_DEBUG(logger "Wyjatek kontrolera - podczas podlaczania sie do serwera");
		return false;
	}
    return true;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int Controller::GetContactsList() // TODO: zmienic typ zwracany
{
    //TODO Auto-generated method stub
    return 0;
}
