#include "Model.h"

void activateListeningThreadFun()
{
	log4cxx::LoggerPtr logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("ActivateListeningThreadFunction"));
	logger->setLevel(LOGLEVEL);
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
	logger->setLevel(LOGLEVEL);

	// uruchomienie brokera, stworzenie obiektow zdalnych, udostepnienie ich i wlaczenie nasluchiwania
	
	try
	{	
		LOG4CXX_DEBUG(logger, "CLNTPORT: " << CLNTPORT.c_str());
		const char * opt = "-OAport";
		const char* orb_options[] = { opt, CLNTPORT.c_str() };
		int optc = sizeof(orb_options)/sizeof(char *);

		orb = CORBA::ORB_init(optc, const_cast<char **>(orb_options));

		PortableServer::POAManager_var manager;
		PortableServer::POA_var poa;

		CORBA::Object_var poaObj = orb->resolve_initial_references("RootPOA");

		if (CORBA::is_nil(poaObj))
		{
			LOG4CXX_ERROR(logger, "Bl¹d podczas resolve'a RootPOA");
			throw std::exception();
		}

		PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(poaObj);
		if (CORBA::is_nil(rootPOA))
		{
			LOG4CXX_ERROR(logger, "rootPOA nie jest referencja POA");
			throw std::exception();
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
			LOG4CXX_ERROR(logger, "nie mozna stworzyc obiektu POA dla 'servPOA'");
			throw std::exception();;
		}
		LOG4CXX_DEBUG(logger, "obiekt POA dla 'servPOA' utworzony");

		CORBA::Object_var bootObj = orb->resolve_initial_references("BootManager");
		if (CORBA::is_nil(bootObj))
		{
			LOG4CXX_ERROR(logger, "Bl¹d podczas resolve'a BootManager'a");
			throw std::exception();
		}

		OB::BootManager_var bootManager = OB::BootManager::_narrow(bootObj);
		if (CORBA::is_nil(bootManager))
		{
			LOG4CXX_ERROR(logger, "obiekt bootObj nie jest obiektem BootManager");
			throw std::exception();
		}
		LOG4CXX_DEBUG(logger, "utworzono boot manager'a");

		// <dla serwerów>
		serverImpl = new IClientServer_impl(poa);

		PortableServer::ObjectId_var oidServ = PortableServer::string_to_ObjectId("clientserver");
		PortableServer::ServantBase_var servantServ = serverImpl;
		poa->activate_object_with_id(oidServ, servantServ);
		LOG4CXX_DEBUG(logger, "utworzono i zarejestrowano zdalny obiekt klienta (udostepniany serwerom)");

		IClientServer_var server = serverImpl->_this();
		bootManager->add_binding(oidServ, server);

		// </dla serwerów>

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

int Model::SendPackage(DomainData::User & usr, DomainData::File & f)
{
	int result = 0;
	LOG4CXX_DEBUG(logger,"Model->WysylaniePliku...");
	result = client->SendPackage(usr, clientsData->GetOwnRecord().userDesc, f);
	LOG4CXX_DEBUG(logger,"Model->Wyslano plik. Result = "<<result);
	return result;
}

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

 int Model::SendMessageToClient(DomainData::User sender, DomainData::User receiver, DomainData::Message msg)
 {
	 int result = 0;
	 LOG4CXX_DEBUG(logger, "Wywolanie send message w modelu");
	 result = client->SendMessageToClient(sender,receiver,msg);
	 LOG4CXX_DEBUG(logger, "Koniec Wywolania send message w modelu. Result: "<<result);
	 return result;
 }

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
			catch(CORBA::SystemException &)
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

	return 0;
}

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

#ifndef WIN32
		sleep(5);
#else
		Sleep(5000);
#endif

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
		 StatusCheckerFunctor checkerFunctor(clientsData,client);
		//Utworz i uruchom watki
	     boost::thread threadStatusChecker(checkerFunctor);
		 LOG4CXX_DEBUG(logger, "Uruchomiono nas³uchiwanie statusu");
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

std::vector<ContactRecord> Model::GetContactsList()
{
	return clientsData->GetContactsList();
}

void Model::SetPortNumber(const int & p)
{
	client->setPortNumber(p);
}

int Model::GetPortNumber() const
{
	return client->getPortNumber();
}

std::string Model::GetOwnName()
{
	return clientsData->GetOwnRecord().userDesc.name.in();
}

const long Model::GetOwnNumber()
{
	ContactRecord c = clientsData->GetOwnRecord();
	return c.userDesc.number;
}

bool Model::GetMyAvailability()
{
	ContactRecord c = clientsData->GetOwnRecord();
	return c.isAvailable;
}

void Model::SetOwnName(const char * c)
{
	clientsData->SetOwnName(c);
	client->setClientName(c);
} 

void Model::SetOwnNumber(long l)
{
	clientsData->SetOwnNumber(l);
	
}

void Model::SetMyAvailability(bool b)
{
	clientsData->SetMyAvailability(b);
}

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
