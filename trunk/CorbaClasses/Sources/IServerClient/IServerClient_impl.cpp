#include <OB/CORBA.h>
#include <IServerClient_impl.h>
#include "Server.h"

//
// IDL:IServerClient:1.0
//
IServerClient_impl::IServerClient_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
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
	// testowa implementacja

	std::cout << "WYWOLANIE CONNECT z addresu [" << Server::GetRemotedAddress(SRVPORT.c_str()) << "]" << std::endl;
	CORBA::ORB_var o;
	IClientServer_var cs;
	std::cout << "Wywolywanie connectToClientServer ... " << std::endl;
	Server::connectToClientServer(Server::GetRemotedAddress(SRVPORT.c_str()),o, cs);
	std::cout << "... WYWOLANO CONNECTTOCLIENTSERVER !!!" << std::endl;
    
	// TODO: Implementation
    ::DomainData::Address* _r = new ::DomainData::Address;
    return _r;
}

//
// IDL:IServerClient/Disconnect:1.0
//
void
IServerClient_impl::Disconnect(const ::DomainData::User& usr)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
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
    // TODO: Implementation
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
