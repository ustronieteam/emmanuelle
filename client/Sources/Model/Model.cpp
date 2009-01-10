#include "Model.h"
//Begin section for file Model.cpp
//TODO: Add definitions that you want preserved
//End section for file Model.cpp

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
		//serverImpl->RegisterObserv(new RemoteServerConnectedObserver(serverDataBaseObj));
		//serverImpl->RegisterObserv(new RemoteServerDisconnectedObserver(serverDataBaseObj));
		//serverImpl->RegisterObserv(new ServerCreatePipeObserver(clientDataBaseObj));
		//serverImpl->RegisterObserv(new PassMessageObserver(clientDataBaseObj));

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
		//clientImpl->RegisterObserv(new RemoteClientConnectedObserver(serverDataBaseObj, clientDataBaseObj));
		//clientImpl->RegisterObserv(new RemoteClientCreatePipeObserver(serverDataBaseObj, clientDataBaseObj));
		//clientImpl->RegisterObserv(new RemoteClientDisconnectedObserver(serverDataBaseObj, clientDataBaseObj));
		//clientImpl->RegisterObserv(new RemoteClientSendMessageObserver(serverDataBaseObj, clientDataBaseObj));
		//clientImpl->RegisterObserv(new RemoteServerUpdateClientObserver(serverDataBaseObj, clientDataBaseObj));

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

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
 int Model::SendPackage(FilePackage package)
 {
	 return 0;
 }

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
 int Model::DeleteContact() 
 {
	 return 0;
 }

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
 int Model::SendMessage() 
 {
	 return 0;
 }

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
 int Model::AddContact() 
 {
	 return 0;
 }

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
 int Model::Disconnect() 
 {
	 return 0;
 }

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
 bool Model::ConnectToServer() 
 {
	 return true;
 }

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
 int Model::AddFileObserver(IRemoteObserver & observer) 
 {
	 return 0;
 }

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
 int Model::AddMessageObserver(IRemoteObserver & observer) 
 {
	 return 0;
 }

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int Model::GetContactsList() // TODO: zmienic typ zwracany
{
	return 0;
}
