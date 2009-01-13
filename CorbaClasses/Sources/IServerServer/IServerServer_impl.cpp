#include <IServerServer_impl.h>
#include <Server.h>

//
// IDL:IServerServer:1.0
//
IServerServer_impl::IServerServer_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
	//logger
	logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("IServerServer_impl"));
	logger->setLevel(log4cxx::Level::getAll());
}

IServerServer_impl::~IServerServer_impl()
{
}

PortableServer::POA_ptr
IServerServer_impl::_default_POA()
{
    return PortableServer::POA::_duplicate(poa_);
}

//
// IDL:IServerServer/Join:1.0
//
::AddressesList*
IServerServer_impl::Join(const ::DomainData::Address& serverAddress)
    throw(::CORBA::SystemException)
{
	LOG4CXX_DEBUG(logger, "WYWOLANIE JOIN z adresu: " << Server::GetRemotedAddress(SRVPORT.c_str()));
	std::cout << "WYWOLANIE JOIN z adresu: " << Server::GetRemotedAddress(SRVPORT.c_str()) << std::endl;

	// zapisanie adresu wlasnego serwera
	if(!strcmp(Server::GetMyIP().localization.in(), "null"))
		Server::SetMyIP(serverAddress);

	//pobranie instancji bazy danych
	ServerDataBase * serverDB = ServerDataBase::GetInstance();

	if(!serverDB->Size())
	{
		this->AddServer(serverAddress);
	}

	// dodanie nowego serwera do bazy danych
	DomainData::Address addr;
	addr.localization = CORBA::string_dup( Server::GetRemotedAddress(SRVPORT.c_str()) );

	this->AddServer(addr);

	// stworzenie obiektu z danymi dla obserwatora
	RemoteObserverData observData;
	observData.set_eventType(SERVER_CONNECTED);
	observData.setServerAddress(addr);

	// wywolanie notify() na obserwatorach (jesli dany obserwator w kolekcji obserwatorow
	// bedzie zobowiazany do zareagowania na zdarzenie to to zrobi)
	this->Notify(observData);

	//pobranie wszystkich rekordow z bazy danych serwera
	std::vector<ServerRecord> & serversList = serverDB->GetAllRecords();

	// utworzenie listy typu AddressList i przepisanie danych uzyskanych z bazy
	AddressesList * _r =  new  AddressesList();
	_r->length(serversList.size());
	
	for(unsigned int i = 0; i < serversList.size(); ++i)
		(*_r)[i] = serversList[i].GetAddress();

	return _r;
}

//
// IDL:IServerServer/Unjoin:1.0
//
void
IServerServer_impl::Unjoin()
    throw(::CORBA::SystemException)
{
    // adres serwera do usuniecia
	DomainData::Address addr;
	addr.localization = CORBA::string_dup(Server::GetRemotedAddress(SRVPORT.c_str()));

	this->RemoveServer(addr);

	// stworzenie obiektu z danymi dla obserwatora
	RemoteObserverData observData;
	observData.set_eventType(SERVER_DISCONNECTED);
	observData.setServerAddress(addr); // ??? czy napewno??

	this->Notify(observData);
}

//
// IDL:IServerServer/AddServer:1.0
//
void
IServerServer_impl::AddServer(const ::DomainData::Address& serverAddress)
    throw(::CORBA::SystemException)
{

	int serverId;
	ServerRecord record;

	serverId = ServerDataBase::GetInstance()->Find(serverAddress);

	if(serverId < 0)
	{
		record.SetAddress(serverAddress);
	
		try
		{
			ServerDataBase::GetInstance()->InsertRecord(record);
		}
		catch(std::exception &)
		{}
	}
	else
	{
		record = ServerDataBase::GetInstance()->GetRecord(serverId);

		CORBA::ORB_var orb = record.GetBroker();

		if(!CORBA::is_nil(orb))
		{
			orb->destroy();
		}
		record.SetBroker(orb);

		IServerServer_var serv = record.GetServerRemoteInstance();

		if(!CORBA::is_nil(serv))
		{
			CORBA::release(serv);
		}
		record.SetServerRemoteInstance(serv);

		ServerDataBase::GetInstance()->ModifyRecord(record);
	}

	std::cout << "WYPISANIE BAZY Z ADDSERVER" << std::endl;
	std::cout << "---------------------------------------" << std::endl;
	std::cout << *(ServerDataBase::GetInstance());
	std::cout << "---------------------------------------" << std::endl;

}

//
// IDL:IServerServer/RemoveServer:1.0
//
void
IServerServer_impl::RemoveServer(const ::DomainData::Address& serverAddress)
    throw(::CORBA::SystemException)
{
	// wydobycie z bazy rekordu dla tego serwera
	int recordId;
	if((recordId = ServerDataBase::GetInstance()->Find(const_cast<DomainData::Address&>(serverAddress))) < 0)
		return;

	//usuniecie rekordu
	try
	{
		ServerDataBase::GetInstance()->DeleteRecord(recordId);
	}
	catch(std::exception &)
	{}
}

//
// IDL:IServerServer/PassMessage:1.0
//
void
IServerServer_impl::PassMessage(const ::DomainData::Message& msg,
                                const ::DomainData::Address& senderAddress,
                                const ::DomainData::Address& receiverAddress)
    throw(::CORBA::SystemException)
{
	// stworzenie obiektu z danymi dla obserwatora
	RemoteObserverData observData;
	observData.set_eventType(SERVER_PASS_MESSAGE);
	observData.setSenderClientAddress(senderAddress);
	observData.setClientAddress(receiverAddress);
	observData.setClientMessage(msg);

	this->Notify(observData);
}

//
// IDL:IServerServer/PassCreatePipeRequest:1.0
//
void
IServerServer_impl::PassCreatePipeRequest(const ::DomainData::Address& pipeHolderAddress,
                                          const ::DomainData::Address& senderAddress,
                                          const ::DomainData::Address& receiverAddress)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:IServerServer/ClientStatusChanged:1.0
//
void
IServerServer_impl::ClientStatusChanged(const ::DomainData::Address& clientAddress,
                                        const ::DomainData::Enability& en,
                                        const ::DomainData::User& usr)
    throw(::CORBA::SystemException)
{
	// pobranie instancji bazy danych uzytkownikow
	ClientsDataBase * clientsDB = ClientsDataBase::GetInstance();

	int recordId;
	ClientRecord record;

	DomainData::Address addr;
	addr.localization = CORBA::string_dup(Server::GetRemotedAddress(SRVPORT.c_str()));

	int servId;
	if((servId = ServerDataBase::GetInstance()->Find(addr)) < 0)
	{
		LOG4CXX_ERROR(logger, "Nie znaleziono serwera do ktorego jest podlaczony klient");
		return;
	}
	else
	{
		LOG4CXX_DEBUG(logger, "Zanaleziono serwer - wstawianie ... ");
		record.SetClientServerId(servId);
	}

	if((recordId = clientsDB->Find(usr)) < 0)
	{
		// nie znaleziono w bazie takiego rekordu
		record.SetAddress(clientAddress);
		record.SetEnability(en);
		record.SetUser(usr);

		try
		{
			clientsDB->InsertRecord(record);
		}
		catch(std::exception &)
		{}
	}
	else
	{
		record = clientsDB->GetRecord(recordId);
		record.SetEnability(en);


		clientsDB->ModifyRecord(record);
	}

	std::cout << "WYPISANIE BAZY Z CLIENTSTATUSCHANGED" << std::endl;
	std::cout << "---------------------------------------" << std::endl;
	std::cout << *(ClientsDataBase::GetInstance());
	std::cout << "---------------------------------------" << std::endl;
}
