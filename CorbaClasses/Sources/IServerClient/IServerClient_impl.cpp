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
	logger->setLevel(log4cxx::Level::getAll());

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
    // TODO: Implementation
    ::DomainData::Enability _r;
    return _r;
}

//
// IDL:IServerClient/GetPipeHolder:1.0
//
::DomainData::User*
IServerClient_impl::GetPipeHolder(const ::DomainData::User& receiver)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
    ::DomainData::User* _r = new ::DomainData::User;
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
