#include <OB/CORBA.h>
#include <IServerServer_impl.h>
#include "Server.h"

//
// IDL:IServerServer:1.0
//
IServerServer_impl::IServerServer_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
	//logger
	logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("IServerServer_impl"));
	logger->setLevel(LOGLEVEL);
}

IServerServer_impl::~IServerServer_impl()
{
}

PortableServer::POA_ptr
IServerServer_impl::_default_POA()
{
    return PortableServer::POA::_duplicate(poa_);
}


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

	LOG4CXX_DEBUG(logger, "Wywolanie AddServer na samym sobie");
	this->AddServer(addr);

	// stworzenie obiektu z danymi dla obserwatora
	RemoteObserverData observData;
	observData.set_eventType(SERVER_CONNECTED);
	observData.setServerAddress(addr);

	LOG4CXX_DEBUG(logger, "Uruchomienie obserwatorow...");
	// wywolanie notify() na obserwatorach (jesli dany obserwator w kolekcji obserwatorow
	// bedzie zobowiazany do zareagowania na zdarzenie to to zrobi)
	this->Notify(observData);

	//pobranie wszystkich rekordow z bazy danych serwera
	std::vector<ServerRecord> serversList = serverDB->GetAllRecords();

	// utworzenie listy typu AddressList i przepisanie danych uzyskanych z bazy
	AddressesList * _r =  new  AddressesList();
	_r->length(serversList.size()+1);
	unsigned int i = 0;
	for( i = 0; i < serversList.size(); ++i)
		(*_r)[i] = serversList[i].GetAddress();

	DomainData::Address connectorAddress;
	connectorAddress.localization = CORBA::string_dup(Server::GetRemotedAddress(SRVPORT.c_str()));

	(*_r)[i] = connectorAddress;

	LOG4CXX_DEBUG(logger, "zakonczenie wywolania JOIN!");
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
	LOG4CXX_DEBUG(logger, "Wywolanie AddServer z adresu: " << Server::GetRemotedAddress(SRVPORT.c_str()));
	int serverId;
	ServerRecord record;

	LOG4CXX_DEBUG(logger, "Wyszukanie serwera[name: " << serverAddress.localization.in() << "]");
	serverId = ServerDataBase::GetInstance()->Find(serverAddress);

	if(serverId < 0)
	{
		LOG4CXX_DEBUG(logger,"Nie znaleziono recordu w bazie ... wstawianie rekordu...");
		record.SetAddress(serverAddress);
	
		try
		{
			ServerDataBase::GetInstance()->InsertRecord(record);
		}
		catch(std::exception &)
		{}
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
                             const ::DomainData::User& sender,
                             const ::DomainData::User& receiver)
    throw(::CORBA::SystemException)
{

	// stworzenie obiektu z danymi dla obserwatora
	RemoteObserverData observData;
	observData.set_eventType(SERVER_PASS_MESSAGE);

	observData.setDestination(receiver);
	observData.setSenderClientData(sender);
	observData.setClientMessage(msg);

	this->Notify(observData);
}

//
// IDL:IServerServer/PassCreatePipeRequest:1.0
//
void
IServerServer_impl::PassCreatePipeRequest(const ::DomainData::User& pipeHolder,
										  const ::DomainData::User& sender,
										  const ::DomainData::User& receiver)
    throw(::CORBA::SystemException)
{
	LOG4CXX_DEBUG(logger, "WYWOLANIE PASSCREATEPIPEREQUEST z adresu: " << Server::GetRemotedAddress(SRVPORT.c_str()));

	try
	{
		int receiverId = ClientsDataBase::GetInstance()->Find(receiver);

		if(receiverId <= 0)
		{
			LOG4CXX_ERROR(logger, "Nie ma takiego klienta w bazie danych");
			return;
		}

		ClientRecord crReceiver = ClientsDataBase::GetInstance()->GetRecord(receiverId);

		IClientServer_var receiverRI = crReceiver.GetClientRemoteInstance();

		if(CORBA::is_nil(receiverRI))
		{
			CORBA::ORB_var orb;
			if(!Server::connectToClientServer(crReceiver.GetAddress().localization.in(), orb, receiverRI))
			{
				LOG4CXX_ERROR(logger, "Nie udalo sie polaczyc");
				return;
			}

			crReceiver.SetClientRemoteInstance(receiverRI);
			crReceiver.SetBroker(orb);

			ClientsDataBase::GetInstance()->ModifyRecord(crReceiver);
		}

		receiverRI->CreatePipeRequest(sender, pipeHolder);
	}
	catch(std::exception & e)
	{
		LOG4CXX_ERROR(logger, "Wyjatek: " << e.what());
		return;
	}
}

//
// IDL:IServerServer/ClientStatusChanged:1.0
//
void
IServerServer_impl::ClientStatusChanged(const ::DomainData::User& client,
                                        const ::DomainData::Address& clientAddress,
                                        const ::DomainData::Enability& en,
                                        const ::DomainData::Address& senderServerAddress)
    throw(::CORBA::SystemException)
{
	// pobranie instancji bazy danych uzytkownikow
	ClientsDataBase * clientsDB = ClientsDataBase::GetInstance();

	int recordId;
	ClientRecord record;

	//DomainData::Address addr;
	//addr.localization = CORBA::string_dup(Server::GetRemotedAddress(SRVPORT.c_str()));

	int servId;
	if((servId = ServerDataBase::GetInstance()->Find(senderServerAddress)) < 0)
	{
		LOG4CXX_ERROR(logger, "Nie znaleziono serwera do ktorego jest podlaczony klient. Adres servera: " << senderServerAddress.localization.in());
		return;
	}

	LOG4CXX_DEBUG(logger, "Znaleziono serwer do ktorego jest podlaczony klient");

	if((recordId = clientsDB->Find(client)) < 0)
	{
		LOG4CXX_DEBUG(logger, "Nie znaleziono klienta w bazie danych.");

		record.SetAddress(clientAddress);
		record.SetEnability(en);
		record.SetUser(client);
		record.SetClientServerId(servId);

		try
		{
			clientsDB->InsertRecord(record);
		}
		catch(std::exception &)
		{

		}
	}
	else
	{
		LOG4CXX_DEBUG(logger, "Znaleziono klienta w bazie danych.");

		record = clientsDB->GetRecord(recordId);

		record.SetAddress(clientAddress);
		record.SetEnability(en);
		record.SetClientServerId(servId);

		try
		{
			clientsDB->ModifyRecord(record);
		}
		catch(std::exception &)
		{

		}
	}

	std::cout << "WYPISANIE BAZY Z CLIENTSTATUSCHANGED" << std::endl;
	std::cout << "---------------------------------------" << std::endl;
	std::cout << *(ClientsDataBase::GetInstance());
	std::cout << "---------------------------------------" << std::endl;
}
