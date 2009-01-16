#include "Controller.h"


Controller::Controller() 
{
	//Do tworzenia logow
    logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("Kontroler"));
	logger->setLevel(LOGLEVEL);
}

Controller::~Controller() 
{
}

IModel * Controller::GetModel() 
{
    return model.get();
}

void Controller::SetModel(IModel * iModel) 
{
	model = boost::shared_ptr<IModel>(iModel);
}

int Controller::AddRemoteObserver(IRemoteObserver * observer, ObserverType observerType) 
{
	return model->RegisterObserver(observer, observerType);
}

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
		inStream.read(cont,size);
		inStream.close();
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

int Controller::AddDataObserver(DataObserver * dataObserver) 
{
	int result = 0;
	LOG4CXX_DEBUG(logger, "Dodawanie Obserwatora statusu(kontroler)");
	result = model->AddStatusObserver(dataObserver);
	LOG4CXX_DEBUG(logger, "Obserwator statusu(kontroler) dodany");
    return result;
}

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

int Controller::Disconnect() 
{
	int result = 0;
	result = model->Disconnect();
	return result;
}

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

std::vector<ContactRecord> Controller::GetContactsList() // TODO: zmienic typ zwracany
{
	return model->GetContactsList();
}

void Controller::SetServerAddress(const char * serv)
{
	model->SetServerAddress(serv);
}

const char * Controller::GetServerAddress() const
{
	return model->GetServerAddress().localization.in();
}

void Controller::SetPortNumber(int p)
{
	model->SetPortNumber(p);
}

int Controller::GetPortNumber() const
{
	return model->GetPortNumber();
}

std::string Controller::GetOwnName()
{
	return model->GetOwnName();
}
///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief	Zwraca wlasny rekord z danymi
///@return	wlasny rekord z danymi
const long Controller::GetOwnNumber()
{
	return model->GetOwnNumber();
}

bool Controller::GetMyAvailability()
{
	return model->GetMyAvailability();
}

void Controller::SetOwnName(const char * c)
{
	model->SetOwnName(c);
} 

void Controller::SetOwnNumber(long l)
{
	model->SetOwnNumber(l);
}

void Controller::SetMyAvailability(bool b)
{
	model->SetMyAvailability(b);
}

void Controller::testClient(std::string str)
{
	LOG4CXX_DEBUG(logger, "Test Client Kontroller begin");
	model->TestClient(str);
	LOG4CXX_DEBUG(logger, "Test Client Kontroller end");
}