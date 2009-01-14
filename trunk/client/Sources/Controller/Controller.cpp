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

///
///@author Marian szczykulski
///@date 2009-01-14
///@brief Rejestruje odpowiedniego obserwatora zdalnej instancji
///@param[in]	observer	Wskaznik na odpowiedniego obserwatora
///@param[in]	observerType	Typ obserwatora
///@return status wykonania operacji
int Controller::AddRemoteObserver(IRemoteObserver * observer, ObserverType observerType) 
{
	return model->RegisterObserver(observer, observerType);
}

///
///@author Marian Szczykulski
///@date 2009-01-14
///@brief Wysylanie pliku
///@param[in]	adresat	Adresat do ktorego wysylany jest plik
///@param[in]	filename	nazwa pliku
///@return	status wysylania
bool Controller::SendFile(const char * adresat, const char * fileName) // TODO: zmienic typ adresata 
{
	LOG4CXX_DEBUG(logger, "Kontroler, wysylanie pliku rozpoczete. Adresat: "<<adresat);
	try
	{
		std::ifstream inStream(fileName, std::ios_base::binary);
		if(!inStream.is_open())
		{
			LOG4CXX_DEBUG(logger, "Kontroler, nie udalo sie otworzyc pliku "<<fileName);
			return false;
		}
		
		inStream.seekg(0,std::ios_base::end);
		int size = inStream.tellg();
		LOG4CXX_DEBUG(logger, "Plik otwarto. Rozmiar: "<<size);
		inStream.seekg(0,std::ios_base::beg);
		char * cont = new char[size];
		LOG4CXX_DEBUG(logger, "Zaalokowano pamiec, wczytywanie danych");
		inStream>>cont;
		LOG4CXX_DEBUG(logger, "Dane wczytano. Wkladanie ich do structury File - dane[" << cont << "]");
		DomainData::File fl;
		//fl.body.length(size+10);
		fl.body	= DomainData::Content(size,size,&cont[0]);
		LOG4CXX_DEBUG(logger, "Dane wlozono do struktury file");
		fl.name = CORBA::string_dup(fileName);
		fl.size = size;
		DomainData::User usr;
		usr.name = CORBA::string_dup(adresat);
		LOG4CXX_DEBUG(logger, "Wysylanie do modelu");
		int result = 0;
		result = model->SendPackage(usr, fl);
		LOG4CXX_DEBUG(logger, "Odp z modelu");
		if(result<0)
			return false;
		else
			return true;
	}
	catch(CORBA::SystemException & exp)
	{
		LOG4CXX_ERROR(logger, "Zlapano wyjatek CORBY w kontrolerze podczas wysylania pliku: "<<exp._name());
		return false;
	}
	catch(std::exception & e)
	{
		LOG4CXX_ERROR(logger, "Zlapano wyjatek w kontrolerze podczas wysylania pliku: "<<e.what());
		return false;
	}
	
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
	DomainData::User receiver;
	receiver.name = CORBA::string_dup(dest);

	DomainData::Message msg;
	msg.content = CORBA::string_dup(content);

	DomainData::User sender;
	sender.name = CORBA::string_dup(model->GetOwnName().c_str());

	int result = 0;
	LOG4CXX_DEBUG(logger, "Wysylanie diadomosci do : " <<dest);
	result = model->SendMessageToClient(sender, receiver, msg);
	
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
///
///@author Marian Szczykulski
///@date 2008-01-13
///@brief dodaje obserwatora statusu (danych w ogolnosci)
///@param[in]	dataObserver	Obserwator danych
///@return		status wykonania operacji
int Controller::AddDataObserver(DataObserver * dataObserver) 
{
	int result = 0;
	LOG4CXX_DEBUG(logger, "Dodawanie Obserwatora statusu(kontroler)");
	result = model->AddStatusObserver(dataObserver);
	LOG4CXX_DEBUG(logger, "Obserwator statusu(kontroler) dodany");
    return result;
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
	model->SetOwnName(model->GetOwnName().c_str());
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
		LOG4CXX_DEBUG(logger, "Wyjatek kontrolera - podczas podlaczania sie do serwera"<<e.what());
		return false;
	}
	LOG4CXX_DEBUG(logger, "Uruchom nasluchiwanie statusu");
	//model->runStatusChecker(); //TODO : Pozniej
	LOG4CXX_DEBUG(logger, "Nasluchiwanie statusu uruchomiono");
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
///
///@author Marian Szczykulski
///@date 2008-01-13
///@brief Testuje polaczenie Klient-Server (dwustronne)
void Controller::testClient(std::string str)
{
	LOG4CXX_DEBUG(logger, "Test Client Kontroller begin");
	model->TestClient(str);
	LOG4CXX_DEBUG(logger, "Test Client Kontroller end");
}