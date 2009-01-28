#include <OB/CORBA.h>
#include <IServerClient_impl.h>
#include "Server.h"

//
// IDL:IServerClient:1.0
//
IServerClient_impl::IServerClient_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
	//logger
	logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("IServerClient_impl"));
	logger->setLevel(LOGLEVEL);

}

IServerClient_impl::~IServerClient_impl()
{
}

PortableServer::POA_ptr
IServerClient_impl::_default_POA()
{
    return PortableServer::POA::_duplicate(poa_);
}

//
// IDL:IServerClient/Connect:1.0
//
::DomainData::Address*
IServerClient_impl::Connect(const ::DomainData::Address& server,
                            ::DomainData::Mode m,
                            const ::DomainData::User& usr)
    throw(::CORBA::SystemException)
{
	std::cout << "WYWOLANIE CONNECT z adresu: " << Server::GetRemotedAddress(SRVPORT.c_str()) << std::endl;

	// zapisanie adresu wlasnego serwera
    if(strcmp(Server::GetMyIP().localization.in(),"null")==0)
	{
		Server::SetMyIP(server);
	}

	::DomainData::Address* _r = new ::DomainData::Address;
	_r->localization = CORBA::string_dup(Server::GetMyIP().localization.in());

	//pobranie instancji bazy danych
	ServerDataBase * serverDB = ServerDataBase::GetInstance();

	// dodanie serwera macierzystego do bazy o ile nie istnieje juz w niej
	if(!serverDB->Size())
	{
		Server::GetInstance("")->GetServerImpl()->AddServer(server);
	}

	// dodanie klienta do lokalnej bazy danych 
	DomainData::Enability en;
	en.status = true;
	en.mode_ = m;
	
	// wywolanie na samym sobie
	DomainData::Address address;
	address.localization = CORBA::string_dup(Server::GetRemotedAddress(SRVPORT.c_str()));
	Server::GetInstance("")->GetServerImpl()->ClientStatusChanged(usr, address, en, Server::GetMyIP());

	RemoteObserverData observData;
	observData.set_eventType(CLIENT_CONNECTED);
	observData.setClientUserData(usr); 
	observData.setClientEnability(en);

	this->Notify(observData);

	//TODO: mozna w przyszlosci dodac obsluge przeciazenia serwera

    return _r;

	/*
	// testowa implementacja
	std::cout << "WYWOLANIE CONNECT z addresu [" << Server::GetRemotedAddress(SRVPORT.c_str()) << "]" << std::endl;
	CORBA::ORB_var o;
	IClientServer_var cs;
	std::cout << "Wywolywanie connectToClientServer ... " << std::endl;
	Server::connectToClientServer(Server::GetRemotedAddress(SRVPORT.c_str()),o, cs);
	std::cout << "... WYWOLANO CONNECTTOCLIENTSERVER !!!" << std::endl;
    
    ::DomainData::Address* _r = new ::DomainData::Address;
	// po drugiej stronie poleci wyjatek ale jest ok
    return _r;
	*/
}

//
// IDL:IServerClient/Disconnect:1.0
//
void
IServerClient_impl::Disconnect(const ::DomainData::User& usr)
    throw(::CORBA::SystemException)
{
	std::cout << "WYWOLANIE DISCONNECT z adresu: " << Server::GetRemotedAddress(SRVPORT.c_str()) << std::endl;

	// dodanie klienta do lokalnej bazy danych 
	DomainData::Enability en;
	en.status = false;
	
	DomainData::Address addr;
	addr.localization = CORBA::string_dup( Server::GetRemotedAddress(SRVPORT.c_str()) );

	Server::GetInstance("")->GetServerImpl()->ClientStatusChanged(usr, addr, en, Server::GetMyIP());

	RemoteObserverData observData;
	observData.set_eventType(CLIENT_DISCONNECTED);
	observData.setClientUserData(usr);

	this->Notify(observData);
}

//
// IDL:IServerClient/Register:1.0
//
::DomainData::User*
IServerClient_impl::Register(const ::DomainData::User& usr)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
    ::DomainData::User* _r = new ::DomainData::User;
    return _r;
}

//
// IDL:IServerClient/SendMessage:1.0
//
void
IServerClient_impl::SendMessage(const ::DomainData::User& ssender,
                                const ::DomainData::User& receiver,
                                const ::DomainData::Message& msg)
    throw(::CORBA::SystemException)
{
	std::cout << "WYWOLANIE SENDMESSAGE z adresu: " << Server::GetRemotedAddress(SRVPORT.c_str()) << std::endl;

	LOG4CXX_DEBUG(logger, "WYWOLANIE SENDMESSAGE z adresu: " << Server::GetRemotedAddress(SRVPORT.c_str()));
	
	RemoteObserverData observData;
	observData.setClientMessage(msg);
	observData.setDestination(receiver);
	observData.setSenderClientData(ssender);
	observData.set_eventType(CLIENT_SEND_MESSAGE);

	this->Notify(observData);
}

//
// IDL:IServerClient/CheckClientStatus:1.0
//
::DomainData::Enability
IServerClient_impl::CheckClientStatus(const ::DomainData::User& usr)
    throw(::CORBA::SystemException)
{
    std::cout << "WYWOLANIE CHECKENABILITYSTATUS z adresu: " << Server::GetRemotedAddress(SRVPORT.c_str()) << std::endl;

	int clientId = ClientsDataBase::GetInstance()->Find(usr);

	LOG4CXX_DEBUG(logger, "Pobrano indeks klienta...");
	if(clientId < 0)
	{
		LOG4CXX_DEBUG(logger, "Nie znaleziono takiego klienta...");
		::DomainData::Enability _r;
		_r.status = false;
		return _r;
	}

	LOG4CXX_DEBUG(logger, "Zwrocenie statusu klienta");
	std:: cout << ClientsDataBase::GetInstance()->GetRecord(clientId).GetUser().name.in() << ": " << ClientsDataBase::GetInstance()->GetRecord(clientId).GetEnability().status << std::endl;

    return ClientsDataBase::GetInstance()->GetRecord(clientId).GetEnability();
}

//
// IDL:IServerClient/GetPipeHolder:1.0
//
::DomainData::User*
IServerClient_impl::GetPipeHolder(const ::DomainData::User& receiver)
    throw(::CORBA::SystemException)
{
	LOG4CXX_DEBUG(logger, "Wywolanie GETPIPEHOLDER z adresu:" << Server::GetRemotedAddress(SRVPORT.c_str()));
	::DomainData::User* _r = new ::DomainData::User;

	DomainData::User sender;
	DomainData::Address address;
	address.localization = CORBA::string_dup(Server::GetInstance("")->GetRemotedAddress(SRVPORT.c_str()));
	
	LOG4CXX_DEBUG(logger, "Adres sendera[" << address.localization.in() << "]");

	int senderId = ClientsDataBase::GetInstance()->FindByAddress(address);
	sender = ClientsDataBase::GetInstance()->GetRecord(senderId).GetUser();

	int localServId = ServerDataBase::GetInstance()->Find(Server::GetMyIP());
	if(localServId <= 0)
	{
		LOG4CXX_ERROR(logger, "Id lokalnego servera mniejsze od 0 - nie istnieje");
		return _r;
	}

	int clientId = ClientsDataBase::GetInstance()->FindActiveClient(sender);

		if(clientId <= 0)
		{
			LOG4CXX_ERROR(logger, "Brak aktywnego klienta");
			return _r;
		}

	try
	{
		ClientRecord crPipeHolder = ClientsDataBase::GetInstance()->GetRecord(clientId);

		int receiverId = ClientsDataBase::GetInstance()->Find(receiver);
		if(receiverId <= 0)
		{
			LOG4CXX_ERROR(logger, "Nie udalo sie znalezc receivera");
			return _r;
		}
		ClientRecord crReceiver = ClientsDataBase::GetInstance()->GetRecord(receiverId);

		if(crReceiver.GetClientServerId() == localServId)
		{
			// client jest lokalnie
			LOG4CXX_DEBUG(logger, "Klient znajduje sie na lokalnym serwerze - znaleziony to [" << crPipeHolder.GetUser().name.in() << "]");

			IClientServer_var clientRInst = crReceiver.GetClientRemoteInstance();
			if(CORBA::is_nil(clientRInst))
			{
				CORBA::ORB_var orb;
				if(!Server::connectToClientServer(crReceiver.GetAddress().localization.in(), orb, clientRInst))
				{
					LOG4CXX_ERROR(logger, "Nie udalo sie pod³¹czyæ do znalezionego klienta");
					return _r;
				}

				crReceiver.SetClientRemoteInstance(clientRInst);
				crReceiver.SetBroker(orb);

				ClientsDataBase::GetInstance()->ModifyRecord(crReceiver);
			}

			int counter = 5; // do wywalenia gdzies na zewnatrz
			while(counter--)
			{
				LOG4CXX_DEBUG(logger, "Odpalenie CREATEPIPEREQUEST na kliencie[" << crPipeHolder.GetUser().name.in() << "]");
				if(!clientRInst->CreatePipeRequest(sender, crPipeHolder.GetUser()))
				{
					LOG4CXX_DEBUG(logger, "nie mozna utworzyc pipe");

					clientId = ClientsDataBase::GetInstance()->FindActiveClient(sender);

					if(clientId <= 0)
					{
						LOG4CXX_ERROR(logger, "Brak aktywnego klienta");
						return _r;
					}

					crPipeHolder = ClientsDataBase::GetInstance()->GetRecord(clientId);
				}
				else
				{
					LOG4CXX_DEBUG(logger, "Znaleziono pipe Holdera i utworzono pipe'a");
					_r->name = CORBA::string_dup(crPipeHolder.GetUser().name.in());
					return _r;
				}
			}
			
		}
		else
		{
			// client jest na innym serverze
			LOG4CXX_DEBUG(logger, "Klient znajduje sie na innym serwerze");

			ServerRecord servRecord = ServerDataBase::GetInstance()->GetRecord(crReceiver.GetClientServerId());
			IServerServer_var servRI = servRecord.GetServerRemoteInstance();

			if(CORBA::is_nil(servRI))
			{
				CORBA::ORB_var orb;
				if(!Server::connectToServerServer(servRecord.GetAddress().localization.in() ,orb, servRI))
				{
					LOG4CXX_ERROR(logger, "Nie mo¿na pod³¹czyc do drugiego serwera");
					return _r;
				}

				servRecord.SetServerRemoteInstance(servRI);
				servRecord.SetBroker(orb);

				ServerDataBase::GetInstance()->ModifyRecord(servRecord);
			}

			LOG4CXX_DEBUG(logger, "... wywolywane PassCreatePipeRequest(" << crPipeHolder.GetUser().name.in() << "," << sender.name.in() <<"," << receiver.name.in() <<")");
			servRI->PassCreatePipeRequest(crPipeHolder.GetUser(), sender, receiver);

			_r->name = CORBA::string_dup(crPipeHolder.GetUser().name.in());
		}

	}
	catch(std::exception & e)
	{
		LOG4CXX_ERROR(logger, "Pobranie recordu - wyjatek: " << e.what());
		return _r;
	}
	catch(CORBA::SystemException & exp)
	{
		LOG4CXX_ERROR(logger, "B³¹d po³¹czenia: " << exp._to_string());
		return _r;
	}
    
	LOG4CXX_DEBUG(logger, "koniec GetPipeHolder method");
    return _r;
}

//
// IDL:IServerClient/GetUserAddressByName:1.0
//
::DomainData::Address*
IServerClient_impl::GetUserAddressByName(const ::DomainData::User& usr)
    throw(::CORBA::SystemException)
{
	std::cout << "WYWOLANIE GETUSERADDRESSBYNAME z adresu: " << Server::GetRemotedAddress(SRVPORT.c_str()) << std::endl;

	LOG4CXX_DEBUG(logger, "WYWOLANIE GETUSERADDRESSBYNAME z adresu: " << Server::GetRemotedAddress(SRVPORT.c_str()));
	
	int clientId = ClientsDataBase::GetInstance()->Find(usr);

	DomainData::Address* _r = new ::DomainData::Address;
	
	if(clientId < 0)
	{
		_r->localization = CORBA::string_dup("");
	}
	else
	{
		*_r = ClientsDataBase::GetInstance()->GetRecord(clientId).GetAddress();
	}

	return _r;
}
