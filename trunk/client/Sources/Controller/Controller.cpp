#include "Controller.h"


///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief prywatny konstruktor domyslny
Controller::Controller() 
{
	//Do tworzenia logow
    logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("Kontroler"));
	logger->setLevel(log4cxx::Level::getAll());
}

Controller::~Controller() 
{
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

///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief	Usuwa kontakt z bazy kontaktow
///@return	0  udalo sie usunac kontakt
///			-1 nie udalo sie usunac
int Controller::DeleteContact(const char * name, long number) 
{
	try
	{
		DomainData::User usr;
		usr.name = CORBA::string_dup(name);
		usr.number = number;
		model->DeleteContact(usr);
	}
	catch(ContactNotFoundException & e)
	{
		LOG4CXX_DEBUG(logger, "Zlapano wyjatek w kontrolerze: ContactNotFoundException: "<<e.what());
		return -1;
	}
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
bool Controller::SendMessageToClient(const char * content, const char * dest) 
{
	DomainData::Address addr;
	addr.localization = CORBA::string_dup(dest);

	DomainData::Message msg;
	msg.content = CORBA::string_dup(content);

	int result = 0;
	result = model->SendMessage(addr, msg);
	
	if(result < 0)
	{
		LOG4CXX_DEBUG(logger, "Blad podczas wysylania wiadomosci. Kod bledu: "<<result);
		return false;
	}
	else
	{
		LOG4CXX_DEBUG(logger, "Wiadomosc wyslana poprawnie ze statusem: "<<result);
		return true;
	}
    return 0;
}



//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int Controller::AddDataObserver(DataObserver & dataObserver) 
{
    //TODO Auto-generated method stub
    return 0;
}
///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief Dodanie kontaktu do bazy
///@param[in]	name	nazwa klienta(ktorego chcemy miec w liscie kontaktow)
///@param[in]	number	numer klienta(ktorego chcemy miec w liscie kontaktow)
///@return		?
int Controller::AddContact(const char * name, long number) 
{
	try
	{
		DomainData::User usr;
		usr.name = CORBA::string_dup(name);
		usr.number	= number;
		model->AddContact(usr);
	}
	catch(ContactAlreadyExistsException & e)
	{
		LOG4CXX_DEBUG(logger, "Zlapano wyjatek w kontrolerze: ContactAlreadyExists : " << e.what());
		return -1;
	}
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
bool Controller::ConnectToServer() 
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




///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief Pobiera liste kontaktow z Modelu
///@return	vector kontaktow
std::vector<ContactRecord> Controller::GetContactsList() // TODO: zmienic typ zwracany
{
	return model->GetContactsList();
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


///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief	Zwraca wlasny rekord z danymi
///@return	wlasny rekord z danymi
std::string Controller::GetOwnName()
{
	return model->GetOwnName();
}
///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief	Zwraca wlasny rekord z danymi
///@return	wlasny rekord z danymi
const long & Controller::GetOwnNumber()
{
	return model->GetOwnNumber();
}
///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief	Zwraca wlasny rekord z danymi
///@return	wlasny rekord z danymi
bool Controller::GetMyAvailability()
{
	return model->GetMyAvailability();
}
///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief setter nazwy lokalnego klienta
void Controller::SetOwnName(const char * c)
{
	model->SetOwnName(c);
} 
///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief setter numeru lokalnego klienta
void Controller::SetOwnNumber(long l)
{
	model->SetOwnNumber(l);
}
///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief setter dostepnosci lokalnego klienta
void Controller::SetMyAvailability(bool b)
{
	model->SetMyAvailability(b);
}
