#include "Model.h"

void activateListeningThreadFun()
{
	log4cxx::LoggerPtr logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("ActivateListeningThreadFunction"));
	logger->setLevel(log4cxx::Level::getAll());
	try
	{
		LOG4CXX_DEBUG(logger, "Uruchamianie nasluchu...");
		Model::GetInstance()->activateListning();
		LOG4CXX_DEBUG(logger, "... zakonczenie nasluchu.");
	}
	catch(CORBA::SystemException & e)
	{
		LOG4CXX_ERROR(logger, "Wyjatek CORBA::SystemException w wyjatku nasluchu klienta" << e._name());
		return;
	}
	catch(std::exception & e)
	{
		LOG4CXX_ERROR(logger, "Wyjatek std::exception w wyjatku nasluchu klienta" << e.what());
		return;
	}
}
void Model::activateListning()
{
	log4cxx::LoggerPtr logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("ACTIVATE LISTENING"));
	logger->setLevel(log4cxx::Level::getAll());

	// uruchomienie brokera, stworzenie obiektow zdalnych, udostepnienie ich i wlaczenie nasluchiwania
	
	try
	{	
		LOG4CXX_DEBUG(logger, "CLNTPORT: " << CLNTPORT.c_str());
		char* orb_options[] = { "-OAport", const_cast<char *>(CLNTPORT.c_str()) };
		int optc = sizeof(orb_options)/sizeof(char *);

		orb = CORBA::ORB_init(optc, orb_options);

		PortableServer::POAManager_var manager;
		PortableServer::POA_var poa;

		CORBA::Object_var poaObj = orb->resolve_initial_references("RootPOA");

		if (CORBA::is_nil(poaObj))
		{
			throw std::exception("Bl�d podczas resolve'a RootPOA");
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
			throw std::exception("Bl�d podczas resolve'a BootManager'a");
		}

		OB::BootManager_var bootManager = OB::BootManager::_narrow(bootObj);
		if (CORBA::is_nil(bootManager))
		{
			throw std::exception("obiekt bootObj nie jest obiektem BootManager");
		}
		LOG4CXX_DEBUG(logger, "utworzono boot manager'a");

		// <dla serwer�w>
		serverImpl = new IClientServer_impl(poa);

		PortableServer::ObjectId_var oidServ = PortableServer::string_to_ObjectId("clientserver");
		PortableServer::ServantBase_var servantServ = serverImpl;
		poa->activate_object_with_id(oidServ, servantServ);
		LOG4CXX_DEBUG(logger, "utworzono i zarejestrowano zdalny obiekt klienta (udostepniany serwerom)");

		IClientServer_var server = serverImpl->_this();
		bootManager->add_binding(oidServ, server);

		// </dla serwer�w>

		// </dla klientow>
		clientImpl = new IClientClient_impl(poa);

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
		LOG4CXX_ERROR(logger, "WYJ�TEK" << e._name());

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


int Model::RegisterObserver(IRemoteObserver * observ, ObserverType type)
{
	if(type == MESSAGE)
	{
		LOG4CXX_DEBUG(logger, "rejestrowanie obseratora MESSAGE" );
		this->serverImpl->RegisterObserv(observ);
	}
	else if(type == FFILE)
	{
		LOG4CXX_DEBUG(logger, "rejestrowanie obseratora FILE" );
		this->clientImpl->RegisterObserv(observ);
	}
	else
	{
		LOG4CXX_DEBUG(logger, "zly typ obserwatora." );
		return 1;
	}

	return 0;
}

int Model::UnregisterObserver()
{
	this->serverImpl->UnregisterObserv();
	this->clientImpl->UnregisterObserv();

	return 0;
}

int Model::AddStatusObserver(DataObserver * observer) 
{
	int result = 0;
	LOG4CXX_DEBUG(logger, "Rejestracja obserwatora statusu w modelu");
	result= clientsData->Register(observer);
	LOG4CXX_DEBUG(logger, "Obserwator statusu zarejestrowany w modelu");
	return result;
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
 int Model::SendMessageToClient(DomainData::User sender, DomainData::User receiver, DomainData::Message msg)
 {
	 int result = 0;
	 LOG4CXX_DEBUG(logger, "Wywolanie send message w modelu");
	 result = client->SendMessageToClient(sender,receiver,msg);
	 LOG4CXX_DEBUG(logger, "Koniec Wywolania send message w modelu. Result: "<<result);
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
		LOG4CXX_DEBUG(logger, "Disconnect w Modelu...");
		DomainData::User ownUsrDt;
		ownUsrDt.name = CORBA::string_dup(GetOwnName().c_str());
		ownUsrDt.number = GetOwnNumber();
		int result = client->Disconnect(ownUsrDt);
		LOG4CXX_DEBUG(logger, "Disconnect w Modelu. Result: "<<result);
		if(result >= 0)
		{
			LOG4CXX_DEBUG(logger, "Konczenie nasluchu...");
			try
			{
			}
			catch(CORBA::SystemException & e)
			{
				LOG4CXX_ERROR(logger, "Wyjatek podczas konczenia nasluchu");
				return -1;
			}
		}

	}
	else
	{
		LOG4CXX_ERROR(logger, "Nie ma zainicjalizowanego objektu klienta w modelu");
		return -1;
	}
}
///
///@author Marian Szczykulski
///@date	2009-01-12
///@brief	Pod��czanie do servera
 bool Model::ConnectToServer()
 {
	 int result;
	 try
	 {
		client->setServerAddress(serverAddress);//Ustawiam, ale nie jest to konieczne

		if(!isActive)
		{
			isActive = true;
			LOG4CXX_DEBUG(logger, "ISACTIVE!!!!!!");
			boost::thread watekSluchacza(&activateListeningThreadFun);
		}

		LOG4CXX_DEBUG(logger, "Uruchomiono watek nasluchu");
		Sleep(5000);
		LOG4CXX_DEBUG(logger, "Connecting...");
		result = client->ConnectToServer();
		LOG4CXX_DEBUG(logger, "Connected");
		//mogla zajsc jakas zmiana wiec dla spojnosci danych nalezy uaktualnic
		this->serverAddress = client->getServerAddress(); 
		
	 }
	 catch(std::exception & e)
	 {
		LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas podlaczania sie do zdalnego serwera");
		throw e;
	 }
	 if(result==1)
	 {
		 //boost::thread watekSluchacza(&activateListeningThreadFun);
		 //LOG4CXX_DEBUG(logger, "Uruchomiono watek nasluchu");
		 //Sleep(5000);
		 return true;
	 }
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
	client->setClientName(c);
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
///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief uruchamia w odzielnym watku cheker-a ktory sprawdza 
///@brief co okreslony czas status wszystkich uzytkownikuw na liscie kontaktow
bool Model::runStatusChecker()
{
	LOG4CXX_DEBUG(logger, "Rozpoczynanie nasluchiwania statusu, uruchomienie w nowym watku");
	//Utworz logike watku
	StatusCheckerFunctor statusChecker(clientsData, client);
	//Utworz i uruchom watki
	boost::thread threadStatusChecker(statusChecker);

	LOG4CXX_DEBUG(logger, "Rozpoczeto nasluchiwac status w nowym watku");
	return true;
}

 void Model::TestClient(std::string addr)
{
	LOG4CXX_DEBUG(logger, "Uruchomiono test clienta ...");
	client->TestCLNT(addr);
	LOG4CXX_DEBUG(logger, "... test klineta zakonczony.");
}
