#include "Server.h"

using namespace std;

bool Server::Run() 
{
	string address = "";
	string port = "";

	// wczytanie danych konfiguracyjnych z pliku: port i address
	if(openConfFile(address,port))
	{
		LOG4CXX_ERROR(logger, "Brak pliku konfiguracyjnego");
		return 1;
	}
	else
	{
		LOG4CXX_DEBUG(logger, string("Wczytano plik konfiguracyjny ") + configFileName + string(" (") + address + string(",") + port + string(")"));
	}
	
	// jesli uruchomilismy serwer macierzysty to nie podlaczamy sie do zadnego 
	if(address.compare("null"))
	{
		if(!init(address, port))
		{
			LOG4CXX_DEBUG(logger, string("polaczono z serverem ") + address + string(" nasluchujacym na porcie ") + port);
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

	// uruchomienie brokera, stworzenie obiektow zdalnych, udostepnienie ich i wlaczenie nasluchiwania
	CORBA::ORB_var orb;

	try
	{
		char* orb_options[] = { "-OAport", const_cast<char *>(port.c_str()) };
		int optc = sizeof(orb_options)/sizeof(char *);

		orb = CORBA::ORB_init(optc, orb_options);

		PortableServer::POAManager_var manager;
		PortableServer::POA_var poa;

		CORBA::Object_var poaObj = orb->resolve_initial_references("RootPOA");

		if (CORBA::is_nil(poaObj))
		{
			LOG4CXX_ERROR(logger, "Bl¹d podczas resolve'a RootPOA");
			return 1;
		}

		PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(poaObj);
		if (CORBA::is_nil(rootPOA))
		{
			LOG4CXX_ERROR(logger, "rootPOA nie jest referencja POA");
			return 1;
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
			return 1;
		}
		LOG4CXX_DEBUG(logger, "obiekt POA dla 'servPOA' utworzony");

		ServerInterfaces::IServerServer_impl * serverImpl = new ServerInterfaces::IServerServer_impl(poa);
		PortableServer::ObjectId_var oid = PortableServer::string_to_ObjectId("serverserver");
		PortableServer::ServantBase_var servant = serverImpl;
		poa->activate_object_with_id(oid, servant);
		LOG4CXX_DEBUG(logger, "utworzono i zarejestrowano zdalny obiekt serwera");

		CORBA::Object_var bootObj = orb->resolve_initial_references("BootManager");
		if (CORBA::is_nil(bootObj))
		{
			LOG4CXX_ERROR(logger, "Bl¹d podczas resolve'a BootManager'a");
			return 1;
		}

		OB::BootManager_var bootManager = OB::BootManager::_narrow(bootObj);
		if (CORBA::is_nil(bootManager))
		{
			LOG4CXX_ERROR(logger, "obietk bootObj nie jest obiektem BootManager");
			return 1;
		}
		LOG4CXX_DEBUG(logger, "utworzono boot manager'a");
		
		ServerInterfaces::IServerServer_var server = serverImpl->_this();
		bootManager->add_binding(oid, server);

		manager->activate();
		
		LOG4CXX_DEBUG(logger, "Wlaczono nasluchiwanie ... ");
		orb->run();
	}
	catch(const CORBA::SystemException& e)
	{
		LOG4CXX_ERROR(logger, string("WYJ¥TEK") + e._name());

		if (!CORBA::is_nil(orb))
		{
			orb->destroy();
		}

		return 1;
	}

    return 0;
}


bool Server::init(string address, string port) 
{
	char* orb_options[] = { const_cast<char *>(address.c_str()) , const_cast<char *>(port.c_str()) };
	int optc = sizeof(orb_options)/sizeof(char *);

	CORBA::ORB_var orb;

	try
	{
		orb = CORBA::ORB_init(optc, orb_options);
		LOG4CXX_DEBUG(logger, "Zainicjalizowano obiekt ORB");

		CORBA::String_var strIOR = CORBA::string_dup("corbaloc:iiop:");
		strIOR += address.c_str();
		strIOR += ":";
		strIOR += port.c_str();
		strIOR += "/serverserver";

		ServerInterfaces::IServerServer_var parentServer;

		CORBA::Object_var oServer = orb->string_to_object(strIOR);
		if (CORBA::is_nil(oServer))
		{
			LOG4CXX_ERROR(logger, "Nie znaleziono serwera, ktory spelnia wymagania zawarte w 'strIOR'");
			return 1;
		}

		parentServer = ServerInterfaces::IServerServer::_narrow(oServer);
    
		if (CORBA::is_nil(parentServer))
		{
			LOG4CXX_ERROR(logger, "obiekt 'oServer' nie jest obiektem klasy IServerServer");
			return 1;
		}

		LOG4CXX_DEBUG(logger, "Poczatek komunikacji z serwerem macierzystym ... ");
		
		parentServer->Join();
		// TODO: dokonczyc ... nawiazanie kontaktu z macierzystym serwerem, zapisanie obiektu zdalnego
		
		LOG4CXX_DEBUG(logger, "... koniec komunikacji z serwerem macierzystym. ");

		// zastanowic sie jeszcze co z tym zrobic
		if (!CORBA::is_nil(orb))
		{
			orb->destroy();
		}

	}
	catch(const CORBA::SystemException& e)
	{
		LOG4CXX_ERROR(logger, string("WYJ¥TEK: ") + e._name());

		if (!CORBA::is_nil(orb))
		{
			orb->destroy();
		}

		return 1;
	}

    return 0;
}

bool Server::openConfFile(string & address, string & port)
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
		string::const_iterator it;
		string name = "";
		string value = "";

		for(it = line.begin(); it < line.end(); ++it)
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
			else if(!name.compare(NPORT))
			{
				port = value;
			}
		}
	}

	// ustawienie domyslnych portow jest nie ma ich w pliku konfiguracyjnym
	if(address.empty())
		address = VADDRESS;
	if(port.empty())
		port = VPORT;

	conf.close();

	return 0;
}
