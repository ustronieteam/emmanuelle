#include "Server.h"

using namespace std;

DomainData::Address Server::myIPAddress;

void activateRunnable()
{
	Server::GetInstance("")->ActivateListning();
}

bool Server::Run() 
{
	string address = "";

	// wczytanie danych konfiguracyjnych z pliku: port i address
	if(openConfFile(address))
	{
		LOG4CXX_ERROR(logger, "Brak pliku konfiguracyjnego");
		return 1;
	}
	else
	{
		LOG4CXX_DEBUG(logger, "Wczytano plik konfiguracyjny " << configFileName << " (" << address.c_str() << ")");
	}
	
	boost::thread thrd(&activateRunnable);
	LOG4CXX_DEBUG(logger, "Usypianie lokalnego watku ...");
	Sleep(5000);
	LOG4CXX_DEBUG(logger, "... wybudzenie lokalnego watku!");

	// jesli uruchomilismy serwer macierzysty to nie podlaczamy sie do zadnego 
	if(!address.empty())
	{
		if(!init(address, LPORT))
		{
			LOG4CXX_DEBUG(logger, "polaczono z serverem " << address.c_str() << " nasluchujacym na porcie " << LPORT.c_str());
		}
		else
		{
			LOG4CXX_ERROR(logger,"Niepoprawna komunikacja z macierzystym serwerem");
			return 1;
		}
	}
	else
	{
		LOG4CXX_DEBUG(logger, "odpalono serwer macierzysty ...");
	}

	thrd.join();

    return 0;
}

void Server::ActivateListning()
{
	// uruchomienie brokera, stworzenie obiektow zdalnych, udostepnienie ich i wlaczenie nasluchiwania
	CORBA::ORB_var orb;

	try
	{
		char* orb_options[] = { "-OAport", const_cast<char *>(LPORT.c_str()) };
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
		serverImpl = new IServerServer_impl(poa);
		
		// dodanie i zarejestrowanie observatorow
		serverImpl->RegisterObserv(new RemoteServerConnectedObserver(serverDataBaseObj));
		serverImpl->RegisterObserv(new RemoteServerDisconnectedObserver(serverDataBaseObj));
		serverImpl->RegisterObserv(new ServerCreatePipeObserver(clientDataBaseObj));
		serverImpl->RegisterObserv(new PassMessageObserver(clientDataBaseObj));

		PortableServer::ObjectId_var oidServ = PortableServer::string_to_ObjectId("serverserver");
		PortableServer::ServantBase_var servantServ = serverImpl;
		poa->activate_object_with_id(oidServ, servantServ);
		LOG4CXX_DEBUG(logger, "utworzono i zarejestrowano zdalny obiekt serwera (udostepniany serwerom)");

		IServerServer_var server = serverImpl->_this();
		bootManager->add_binding(oidServ, server);

		// </dla serwerów>

		// </dla klientow>
		clientImpl = new IServerClient_impl(poa);

		// dodanie i zarejestrowanie observatorow
		clientImpl->RegisterObserv(new RemoteClientConnectedObserver(serverDataBaseObj, clientDataBaseObj));
		clientImpl->RegisterObserv(new RemoteClientCreatePipeObserver(serverDataBaseObj, clientDataBaseObj));
		clientImpl->RegisterObserv(new RemoteClientDisconnectedObserver(serverDataBaseObj, clientDataBaseObj));
		clientImpl->RegisterObserv(new RemoteClientSendMessageObserver(serverDataBaseObj, clientDataBaseObj));
		clientImpl->RegisterObserv(new RemoteServerUpdateClientObserver(serverDataBaseObj, clientDataBaseObj));

		PortableServer::ObjectId_var oidClnt = PortableServer::string_to_ObjectId("serverclient");
		PortableServer::ServantBase_var servantClnt = clientImpl;
		poa->activate_object_with_id(oidClnt, servantClnt);
		LOG4CXX_DEBUG(logger, "utworzono i zarejestrowano zdalny obiekt serwera (udostepniany klientom)");
		
		IServerClient_var client = clientImpl->_this();
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

bool Server::init(string address, string port) 
{
	CORBA::ORB_var orb;
	IServerServer_var parentServer;

	try
	{
		if(!Server::connectToServerServer(address, orb, parentServer))
		{
			LOG4CXX_ERROR(logger, "Nie mo¿na po³¹czyc z sewerem macierzystym");
			return 1;
		}
		
		LOG4CXX_DEBUG(logger, "Poczatek komunikacji z serwerem macierzystym ... ");

		DomainData::Address addr;
		addr.localization = CORBA::string_dup(address.c_str());
		AddressesList * l = parentServer->Join(addr);

		ServerDataBase::GetInstance()->Clear();
		for(unsigned int i = 0; i < l->length(); ++i)
		{
			ServerRecord rcd;
			rcd.SetAddress((*l)[i]);

			ServerDataBase::GetInstance()->InsertRecord(rcd);
		}

		cout << "WYPISANIE BAZY Z INITA: " << endl;
		cout << "***************************" << endl;
		cout << *(ServerDataBase::GetInstance());
		cout << "***************************" << endl;

		// TODO: dokonczyc ...	nawiazanie kontaktu z macierzystym serwerem, zapisanie obiektu zdalnego
		//						zapisanie obiektu orb

		LOG4CXX_DEBUG(logger, "... koniec komunikacji z serwerem macierzystym. ");

	}
	catch(const CORBA::SystemException& e)
	{
		LOG4CXX_ERROR(logger, "WYJ¥TEK: " << e._name() << ": " << e._to_string());

		if (!CORBA::is_nil(orb))
		{
			orb->destroy();
		}

		return 1;
	}

    return 0;
}

bool Server::openConfFile(string & address)
{
	fstream conf;
	conf.open(configFileName, ios_base::out | ios_base::in);

	if(!conf.is_open())
	{
		LOG4CXX_ERROR(logger, "Nie ma takiego pliku konfiguracyjnego !");

		return 1;
	}

	if(conf.fail())
		conf.clear();

	conf.seekp(0, ios_base::beg);

	string line;
	while(getline(conf, line))
	{
		string::const_iterator it = line.begin();

		if(*it == '#')
			continue;

		string name = "";
		string value = "";

		for(it; it < line.end(); ++it)
		{
			if(*it != ' ' && *it != '=')
			{
				name += *it;
			}
			else if(*it == '=')
				break;
		}

		if(*it == '=')
		{		
			for(++it; it < line.end(); ++it)
			{
				if(*it != '\n' && *it != ' ')
					value += *it;
			}

			if(!name.compare(NADDRESS))
			{
				address = value;
			}
		}
	}

	conf.close();

	return 0;
}
