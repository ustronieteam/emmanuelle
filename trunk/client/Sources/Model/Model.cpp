#include "Model.h"

void Model::activateListning()
{
	// uruchomienie brokera, stworzenie obiektow zdalnych, udostepnienie ich i wlaczenie nasluchiwania
	CORBA::ORB_var orb;

	try
	{
		char* orb_options[] = { "-OAport", const_cast<char *>(CLNTPORT.c_str()) };
		int optc = sizeof(orb_options)/sizeof(char *);

		orb = CORBA::ORB_init(optc, orb_options);

		PortableServer::POAManager_var manager;
		PortableServer::POA_var poa;

		CORBA::Object_var poaObj = orb->resolve_initial_references("RootPOA");

		if (CORBA::is_nil(poaObj))
		{
			throw std::exception("Bl¹d podczas resolve'a RootPOA");
		}

		PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(poaObj);
		if (CORBA::is_nil(rootPOA))
		{
			throw std::exception("rootPOA nie jest referencja POA");
		}
    
		manager = rootPOA->the_POAManager();
		LOG4CXX_DEBUG(logger, "uzyskano obiekt POA i POAmanager'a");

		CORBA::PolicyList policies;
		policies.length(2);
		policies[0] = rootPOA->create_id_assignment_policy(PortableServer::USER_ID);
		policies[1] = rootPOA->create_lifespan_policy(PortableServer::PERSISTENT);

		poa = rootPOA->create_POA("servPOA", manager, policies);
		
		if (CORBA::is_nil(poa))
		{
			throw std::exception("nie mozna stworzyc obiektu POA dla 'servPOA'");;
		}
		LOG4CXX_DEBUG(logger, "obiekt POA dla 'servPOA' utworzony");

		CORBA::Object_var bootObj = orb->resolve_initial_references("BootManager");
		if (CORBA::is_nil(bootObj))
		{
			throw std::exception("Bl¹d podczas resolve'a BootManager'a");
		}

		OB::BootManager_var bootManager = OB::BootManager::_narrow(bootObj);
		if (CORBA::is_nil(bootManager))
		{
			throw std::exception("obiekt bootObj nie jest obiektem BootManager");
		}
		LOG4CXX_DEBUG(logger, "utworzono boot manager'a");

		// <dla serwerów>
		serverImpl = new IClientServer_impl(poa);
		
		// dodanie i zarejestrowanie observatorow
		serverImpl->RegisterObserv(new MessageObserver());
		serverImpl->RegisterObserv(new FileObserver());

		PortableServer::ObjectId_var oidServ = PortableServer::string_to_ObjectId("clientserver");
		PortableServer::ServantBase_var servantServ = serverImpl;
		poa->activate_object_with_id(oidServ, servantServ);
		LOG4CXX_DEBUG(logger, "utworzono i zarejestrowano zdalny obiekt klienta (udostepniany serwerom)");

		IClientServer_var server = serverImpl->_this();
		bootManager->add_binding(oidServ, server);

		// </dla serwerów>

		// </dla klientow>
		clientImpl = new IClientClient_impl(poa);

		// dodanie i zarejestrowanie observatorow
		clientImpl->RegisterObserv(new FileObserver());

		PortableServer::ObjectId_var oidClnt = PortableServer::string_to_ObjectId("clientclient");
		PortableServer::ServantBase_var servantClnt = clientImpl;
		poa->activate_object_with_id(oidClnt, servantClnt);
		LOG4CXX_DEBUG(logger, "utworzono i zarejestrowano zdalny obiekt klienta (udostepniany klientom)");
		
		IClientClient_var client = clientImpl->_this();
		bootManager->add_binding(oidClnt, client);
		// </dla klientow>

		manager->activate();
		
		LOG4CXX_DEBUG(logger, "Wlaczono nasluchiwanie ... ");
		orb->run();
	}
	catch(const CORBA::SystemException& e)
	{
		LOG4CXX_ERROR(logger, "WYJ¥TEK" << e._name());

		if (!CORBA::is_nil(orb))
		{
			orb->destroy();
		}
	}
	catch(const std::exception & e)
	{
		LOG4CXX_ERROR(logger, e.what());

		if (!CORBA::is_nil(orb))
		{
			orb->destroy();
		}
	}
}

int Model::AddStatusObserver(DataObserver & observer) 
{
 return 0;
}

int Model::SendPackage(FilePackage package)
{
 return 0;
}

///
///@author Marian Szczykulski
///@date	2009-01-12
///@brief	Usuwa kontakt z bazy
///@param[in]	usr	Dane o usuwanym kontakcie
///@return		0 udalo sie usunac lub rzuca wyjatek ContactNotFoundException jak sie nie udalo
int Model::DeleteContact(const DomainData::User & usr) 
{
	try
	{
		clientsData->DeleteContact(usr);
	}
	catch(ContactNotFoundException & e)
	{
		LOG4CXX_DEBUG(logger, "Zlapano wyjatek podczas usuwania kontakty: ContactNotFoundException : "<<e.what());
		throw e;
	}
	return 0;
}
///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief Wysylanie wiadomosci do klienta
///@param[in] recAddr	adresat wiadomosci
///@param[in] msg		wiadomosc
///@return				status (-2 zdalna instancja serwera nie zainicjowana,
///								-1 blad podczas wywolywania zdalnej metody serwera)
 int Model::SendMessage(DomainData::Address recAddr, DomainData::Message msg) 
 {
	 int result = 0;
	 result = client->SendMessage(recAddr, msg);
	 return result;
 }
///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief	Dodaje kontakt do bazy kontaktow
///@param[in]	usr	Dane o dodawanym uzytkowniku
///@return		0	lub rzuca wyjatek jezeli nie udalo sie dodac
 int Model::AddContact(const DomainData::User &usr) 
{
	try
	{
		clientsData->AddContact(usr);
		return 0;
	}
	catch(ContactAlreadyExistsException & e)
	{
		LOG4CXX_DEBUG(logger, "Wyjatek w modelu: ContactAlreadyExists : "<<e.what());
		throw e;
	}
	return 0;
}
///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief Rozlaczanie sie z serwera
int Model::Disconnect() 
{
	if(client != boost::shared_ptr<Client>())
	{
		return client->Disconnect();
	}
	else
		return -1;
}
///
///@author Marian Szczykulski
///@date	2009-01-12
///@brief	Pod³¹czanie do servera
 bool Model::ConnectToServer()
 {
	 int result;
	 try
	 {
		client->setServerAddress(serverAddress);//Ustawiam, ale nie jest to konieczne

		result = client->ConnectToServer();
		//mogla zajsc jakas zmiana wiec dla spojnosci danych nalezy uaktualnic
		this->serverAddress = client->getServerAddress(); 
		
	 }
	 catch(std::exception & e)
	 {
		LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas podlaczania sie do zdalnego serwera");
		throw e;
	 }
	 if(result==1)
		 return true;
	 else
		return false;
 }

 int Model::AddFileObserver(IRemoteObserver & observer) 
 {
	 return 0;
 }

 int Model::AddMessageObserver(IRemoteObserver & observer) 
 {
	 return 0;
 }

///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief Pobiera liste kontaktow z bazy
///@return	vector kontaktow
std::vector<ContactRecord> Model::GetContactsList()
{
	return clientsData->GetContactsList();
}
///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief setter portu
void Model::SetPortNumber(const int & p)
{
	client->setPortNumber(p);
}
///
///@author Marian Szczykulski
///@date 2009-01-12
///@brief getter portu
int Model::GetPortNumber() const
{
	return client->getPortNumber();
}
///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief	Zwraca wlasny rekord z danymi
///@return	wlasny rekord z danymi
std::string Model::GetOwnName()
{
	return clientsData->GetOwnRecord().userDesc.name.in();
}
///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief	Zwraca wlasny rekord z danymi
///@return	wlasny rekord z danymi
const long & Model::GetOwnNumber()
{
	ContactRecord c = clientsData->GetOwnRecord();
	return c.userDesc.number;
}
///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief	Zwraca wlasny rekord z danymi
///@return	wlasny rekord z danymi
bool Model::GetMyAvailability()
{
	ContactRecord c = clientsData->GetOwnRecord();
	return c.isAvailable;
}
///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief setter nazwy lokalnego klienta
void Model::SetOwnName(const char * c)
{
	clientsData->SetOwnName(c);
} 
///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief setter numeru lokalnego klienta
void Model::SetOwnNumber(long l)
{
	clientsData->SetOwnNumber(l);
}
///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief setter dostepnosci lokalnego klienta
void Model::SetMyAvailability(bool b)
{
	clientsData->SetMyAvailability(b);
}
