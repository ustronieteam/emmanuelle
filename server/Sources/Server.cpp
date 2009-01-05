#include "Server.h"
//Begin section for file Server.cpp
//TODO: Add definitions that you want preserved
//End section for file Server.cpp

using namespace std;

Server::Server(const char * fileName) 
{
    // stworzenie obiektow baz danych: klienta i serwera
	this->clientDataBaseObj = new ClientsDataBase();
	this->serverDataBaseObj = new ServerDataBase();

	configFileName = fileName;
}

/*
Server::Server(const Server & arg) 
{
    return arg;
}

*/

Server::~Server() 
{
    //TODO Auto-generated method stub
}



bool Server::Run() 
{
	string address = "";
	string port = "";

	if(openConfFile(address,port))
	{
		// brak pliku konfiguracyjnego
		cout << "Brak pliku konfiguracyjnego" << endl;
		return 1;
	}
	else
	{
		cout << "Wczytano plik konfiguracyjny " << configFileName << " (" << address << "," << port << ")" <<endl;
	}
	
	if(address.compare("null"))
	{
		if(!init(address, port))
			cout << "polaczono z serverem " << address << " nasluchujacym na porcie " << port << endl;	
		else
		{
			cout << "Niepoprawna komunikacja z macierzystym serwerem" << endl;
			return 1;
		}
	}
	else
	{
		cout << "odpalono serwer macierzysty ..." << endl;
	}

	try
	{
cout << "1" << endl;
		char* orb_options[] = { "-OAport", const_cast<char *>(port.c_str()) };
		int optc = sizeof(orb_options)/sizeof(char *);

		CORBA::ORB_var orb = CORBA::ORB_init(optc, orb_options);
cout << "1.5" << endl;
		PortableServer::POAManager_var manager;
		PortableServer::POA_var poa;
cout << "1.75" << endl;
		CORBA::Object_var poaObj = orb->resolve_initial_references("RootPOA");
cout << "1.8" << endl;
		if (CORBA::is_nil(poaObj))
		{
			// blad
		}
cout << "2" << endl;
		PortableServer::POA_var rootPOA = PortableServer::POA::_narrow(poaObj);
		if (CORBA::is_nil(rootPOA))
		{
			// blad
		}
    
		manager = rootPOA->the_POAManager();

		CORBA::PolicyList policies;
		policies.length(2);
		policies[0] = rootPOA->create_id_assignment_policy(PortableServer::USER_ID);
		policies[1] = rootPOA->create_lifespan_policy(PortableServer::PERSISTENT);

		poa = rootPOA->create_POA("servPOA", manager, policies);
		
		if (CORBA::is_nil(poa))
		{
			// blad
		}
cout << "3" << endl;

		ServerInterfaces::IServerServer_impl * serverImpl = new ServerInterfaces::IServerServer_impl(poa);
		PortableServer::ObjectId_var oid = PortableServer::string_to_ObjectId("serverserver");
		PortableServer::ServantBase_var servant = serverImpl;
		poa->activate_object_with_id(oid, servant);

		CORBA::Object_var bootObj = orb->resolve_initial_references("BootManager");
		if (CORBA::is_nil(bootObj))
		{
			// blad
		}
cout << "4" << endl;

		OB::BootManager_var bootManager = OB::BootManager::_narrow(bootObj);
		if (CORBA::is_nil(bootManager))
		{
			// blad
		}
		
		ServerInterfaces::IServerServer_var server = serverImpl->_this();
		bootManager->add_binding(oid, server);

		manager->activate();
		
		cout << "Wlaczono nasluchiwanie ... " << endl;
		orb->run();
	}
	catch(const CORBA::SystemException& e)
	{
		// wyjatek
		cout << "POLECIAL WYJATEK: " << endl;
		cout << e._name() << endl;
	}

    return 0;
}


bool Server::init(string address, string port) 
{
	char* orb_options[] = { const_cast<char *>(address.c_str()) , const_cast<char *>(port.c_str()) };
	int optc = sizeof(orb_options)/sizeof(char *);

	try
	{
		CORBA::ORB_var orb = CORBA::ORB_init(optc, orb_options);

		CORBA::String_var strIOR = CORBA::string_dup("corbaloc:iiop:");
		strIOR += address.c_str();
		strIOR += ":";
		strIOR += port.c_str();
		strIOR += "/serverserver";

		ServerInterfaces::IServerServer_var parentServer;

		CORBA::Object_var oServer = orb->string_to_object(strIOR);
		if (CORBA::is_nil(oServer))
		{
			// blad
			return 1;
		}

		parentServer = ServerInterfaces::IServerServer::_narrow(oServer);
    
		if (CORBA::is_nil(parentServer))
		{
			//blad
			return 1;
		}

		// wywolania
		parentServer->Join();
		// TODO: dokonczyc ... nawiazanie kontaktu z macierzystym serwerem, zapisanie obiektu zdalnego
		

		if (!CORBA::is_nil(orb))
		{
			orb->destroy();
		}

	}
	catch(const CORBA::SystemException& e)
	{
		// wyjatek
		cout << "POLECIAL WYJATEK: " << endl;
		cout << e._name() << endl;
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
		// nie otwarto pliku
		cout << "Nie ma takiego pliku" << endl;
		return 1;
	}

	if(conf.fail())
		conf.clear();

	//conf.seekg(0, ios_base::beg);
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
