#include "Controller.h"
//Begin section for file Controller.cpp
//TODO: Add definitions that you want preserved
//End section for file Controller.cpp

///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief prywatny konstruktor domyslny
Controller::Controller() 
{
	//Do tworzenia logow
    logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("Model"));
	logger->setLevel(log4cxx::Level::getAll());
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
    return model.get();
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
///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief Metoda wykonuje logike potrzebna do wyslania wiadomosci do innego klienta
///@param[in] content	tresc wiadomosci do wyslania
///@param[in] dest		nazwa klienta do ktorego wysylana jest wiadomosc
///@return				true  - wiadomosc wyslana pomyslnie
///						false - w przeciwnym przypadku
bool Controller::SendMessage(const char * content, const char * dest) 
{
	//1) Znajdz klienta w naszych kontaktach
	//2) Wypelnij struktury DomainData::Address i DomainData::Message
	//3) wywolaj metode na modelu SendMessage
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
		LOG4CXX_DEBUG(logger, "Podlaczanie do pierwszego servera");
		while(!model->ConnectToServer())//Dopuki serwer nam odsyla inny adres do podlaczenia
		{
			LOG4CXX_INFO(logger, "Podlaczanie do kolejnego servera");
		}
	}
	catch(std::exception & e)
	{
		LOG4CXX_DEBUG(logger, "Wyjatek kontrolera - podczas podlaczania sie do serwera");
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
///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief setter adresu serwera do ktorego mamy sie podlaczyc
///@param[in]	serv	adres serwera do ktorego mamy sie podlaczyc
void Controller::SetServerAddress(const char * serv)
{
	model->SetServerAddress(serv);
}
///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief getter adresu serwera do ktorego mamy sie podlaczyc
///@return	adres serwera do ktorego mamy sie podlaczyc
const char * Controller::GetServerAddress() const
{
	return model->GetServerAddress().localization.in();
}
///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief setter portu przez ktory mamy sie laczyc
///@param[in]	p	port przez ktory mamy sie laczyc
void Controller::SetPortNumber(int p)
{
	model->SetPortNumber(p);
}
///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief getter portu przez ktory mamy sie laczyc
///@return	port przez ktory mamy sie laczyc
int Controller::GetPortNumber() const
{
	return model->GetPortNumber();
}
