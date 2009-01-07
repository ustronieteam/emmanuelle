#include "Server.h"

using namespace std;

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

	activateListning();

    return 0;
}

bool Server::init(string address, string port) 
{
	CORBA::ORB_var orb;
	IServerServer_var parentServer;

	try
	{
		if(connectToServer(address, port, orb, parentServer))
		{
			LOG4CXX_ERROR(logger, "Nie mo¿na po³¹czyc z sewerem macierzystym");
			return 1;
		}
		
		LOG4CXX_DEBUG(logger, "Poczatek komunikacji z serwerem macierzystym ... ");
	
		parentServer->Join();
		// TODO: dokonczyc ...	nawiazanie kontaktu z macierzystym serwerem, zapisanie obiektu zdalnego
		//						zapisanie obiektu orb

		LOG4CXX_DEBUG(logger, "... koniec komunikacji z serwerem macierzystym. ");

	}
	catch(const CORBA::SystemException& e)
	{
		LOG4CXX_ERROR(logger, "WYJ¥TEK: " << e._name());

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

bool Server::connectToServer(string address, string port, CORBA::ORB_out orb, IServerServer_out server)
{
	LOG4CXX_DEBUG(logger, "Laczenie z serwerem o adresie " << address.c_str() << " na porcie " << port.c_str());

	char* orb_options[] = { const_cast<char *>(address.c_str()) , const_cast<char *>(port.c_str()) };
	int optc = sizeof(orb_options)/sizeof(char *);

	orb = CORBA::ORB_init(optc, orb_options);
	LOG4CXX_DEBUG(logger, "Zainicjalizowano obiekt ORB");

	CORBA::String_var strIOR = CORBA::string_dup("corbaloc:iiop:");
	strIOR += address.c_str();
	strIOR += ":";
	strIOR += port.c_str();
	strIOR += "/serverserver";

	CORBA::Object_var oServer = orb->string_to_object(strIOR);
	if (CORBA::is_nil(oServer))
	{
		LOG4CXX_ERROR(logger, "Nie znaleziono serwera, ktory spelnia wymagania zawarte w 'strIOR'");
		return 1;
	}

	server = IServerServer::_narrow(oServer);
    
	if (CORBA::is_nil(server))
	{
		LOG4CXX_ERROR(logger, "obiekt 'oServer' nie jest obiektem klasy IServerServer");
		return 1;
	}

	LOG4CXX_DEBUG(logger, "Po³¹czono !");
	return 0;
}

void Server::activateListning()
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
		IServerServer_impl * serverImpl = new IServerServer_impl(poa);
		PortableServer::ObjectId_var oidServ = PortableServer::string_to_ObjectId("serverserver");
		PortableServer::ServantBase_var servantServ = serverImpl;
		poa->activate_object_with_id(oidServ, servantServ);
		LOG4CXX_DEBUG(logger, "utworzono i zarejestrowano zdalny obiekt serwera (udostepniany serwerom)");
		
		IServerServer_var server = serverImpl->_this();
		bootManager->add_binding(oidServ, server);
		// </dla serwerów>

		// </dla klientow>
		IServerClient_impl * clientImpl = new IServerClient_impl(poa);
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
