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
	
	DomainData::Address addr;
	addr.localization = CORBA::string_dup( Server::GetRemotedAddress(SRVPORT.c_str()) );
	
	Server::GetInstance("")->GetServerImpl()->ClientStatusChanged(addr, en, usr);

	RemoteObserverData observData;
	observData.set_eventType(CLIENT_CONNECTED);
	observData.setClientAddress(addr); 
	observData.setClientEnability(en);
	
	DomainData::User u;
	u = usr;
	std::cout << "CLIENT name: " << usr.name << std::endl;
	observData.setClientUserData(u);

	this->Notify(observData);

	//TODO: mozna w przyszlosci dodac obsluge przeciazenia serwera

    ::DomainData::Address* _r = new ::DomainData::Address;
	_r->localization = CORBA::string_dup(Server::GetMyIP().localization.in());
    return _r;
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

	Server::GetInstance("")->GetServerImpl()->ClientStatusChanged(addr, en, usr);

	RemoteObserverData observData;
	observData.set_eventType(CLIENT_DISCONNECTED);
	observData.setClientAddress(addr); 
	observData.setClientEnability(en);
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
IServerClient_impl::SendMessage(const ::DomainData::Address& receiverAddress,
                                const ::DomainData::Message& msg)
    throw(::CORBA::SystemException)
{
	RemoteObserverData observData;
	observData.set_eventType(CLIENT_SEND_MESSAGE);
	observData.setClientMessage(msg);
	observData.setClientAddress(receiverAddress);

	this->Notify(observData);
}

//
// IDL:IServerClient/CheckClientStatus:1.0
//
::DomainData::Enability
IServerClient_impl::CheckClientStatus(const ::DomainData::Address& clientAddress)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
    ::DomainData::Enability _r;
    return _r;
}

//
// IDL:IServerClient/GetPipeHolder:1.0
//
::DomainData::Address*
IServerClient_impl::GetPipeHolder(const ::DomainData::Address& receiverAddress)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
    ::DomainData::Address* _r = new ::DomainData::Address;
    return _r;
}