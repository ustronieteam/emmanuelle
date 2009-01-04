#include <OB/CORBA.h>
#include <ServerInterfaces_impl.h>

//
// IDL:DomainData:1.0
//

//
// IDL:ServerInterfaces:1.0
//

//
// IDL:ServerInterfaces/IServerServer:1.0
//
ServerInterfaces::IServerServer_impl::IServerServer_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
}

ServerInterfaces::IServerServer_impl::~IServerServer_impl()
{
}

PortableServer::POA_ptr
ServerInterfaces::IServerServer_impl::_default_POA()
{
    return PortableServer::POA::_duplicate(poa_);
}

//
// IDL:ServerInterfaces/IServerServer/Join:1.0
//
::ServerInterfaces::AddressesList*
ServerInterfaces::IServerServer_impl::Join()
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
    ::ServerInterfaces::AddressesList* _r = new ::ServerInterfaces::AddressesList;
    return _r;
}

//
// IDL:ServerInterfaces/IServerServer/Unjoin:1.0
//
void
ServerInterfaces::IServerServer_impl::Unjoin()
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:ServerInterfaces/IServerServer/AddServer:1.0
//
void
ServerInterfaces::IServerServer_impl::AddServer(const ::DomainData::Address& serverAddress)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:ServerInterfaces/IServerServer/RemoveServer:1.0
//
void
ServerInterfaces::IServerServer_impl::RemoveServer(const ::DomainData::Address& serverAddress)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:ServerInterfaces/IServerServer/PassMessage:1.0
//
void
ServerInterfaces::IServerServer_impl::PassMessage(const ::DomainData::Message& msg,
                                                  const ::DomainData::Address& senderAddress,
                                                  const ::DomainData::Address& receiverAddress)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:ServerInterfaces/IServerServer/PassCreatePipeRequest:1.0
//
void
ServerInterfaces::IServerServer_impl::PassCreatePipeRequest(const ::DomainData::Address& pipeHolderAddress,
                                                            const ::DomainData::Address& senderAddress,
                                                            const ::DomainData::Address& receiverAddress)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:ServerInterfaces/IServerServer/ClientStatusChanged:1.0
//
void
ServerInterfaces::IServerServer_impl::ClientStatusChanged(const ::DomainData::Address& clientAddress,
                                                          const ::DomainData::Enability& en)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:ServerInterfaces/IServerClient:1.0
//
ServerInterfaces::IServerClient_impl::IServerClient_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
}

ServerInterfaces::IServerClient_impl::~IServerClient_impl()
{
}

PortableServer::POA_ptr
ServerInterfaces::IServerClient_impl::_default_POA()
{
    return PortableServer::POA::_duplicate(poa_);
}

//
// IDL:ServerInterfaces/IServerClient/Connect:1.0
//
::DomainData::Address*
ServerInterfaces::IServerClient_impl::Connect(::DomainData::Mode m,
                                              const ::DomainData::User& usr)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
    ::DomainData::Address* _r = new ::DomainData::Address;
    return _r;
}

//
// IDL:ServerInterfaces/IServerClient/Disconnect:1.0
//
void
ServerInterfaces::IServerClient_impl::Disconnect()
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:ServerInterfaces/IServerClient/Register:1.0
//
::DomainData::User*
ServerInterfaces::IServerClient_impl::Register(const ::DomainData::User& usr)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
    ::DomainData::User* _r = new ::DomainData::User;
    return _r;
}

//
// IDL:ServerInterfaces/IServerClient/SendMessage:1.0
//
void
ServerInterfaces::IServerClient_impl::SendMessage(const ::DomainData::Address& receiverAddress,
                                                  const ::DomainData::Message& msg)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:ServerInterfaces/IServerClient/CheckClientStatus:1.0
//
::DomainData::Enability
ServerInterfaces::IServerClient_impl::CheckClientStatus(const ::DomainData::Address& clientAddress)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
    ::DomainData::Enability _r;
    return _r;
}

//
// IDL:ServerInterfaces/IServerClient/GetPipeHolder:1.0
//
::DomainData::Address*
ServerInterfaces::IServerClient_impl::GetPipeHolder(const ::DomainData::Address& receiverAddress)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
    ::DomainData::Address* _r = new ::DomainData::Address;
    return _r;
}
