#include <OB/CORBA.h>
#include <IClientClient_impl.h>

//
// IDL:IClientClient:1.0
//
IClientClient_impl::IClientClient_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
}

IClientClient_impl::~IClientClient_impl()
{
}

PortableServer::POA_ptr
IClientClient_impl::_default_POA()
{
    return PortableServer::POA::_duplicate(poa_);
}

//
// IDL:IClientClient/SendFile:1.0
//
void
IClientClient_impl::SendFile(const ::DomainData::File& f,
                             const ::DomainData::User& receiver)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:IClientClient/CreatePipe:1.0
//
void
IClientClient_impl::CreatePipe(const ::DomainData::User& receiver)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:IClientClient/GetFile:1.0
//
::DomainData::File*
IClientClient_impl::GetFile(const ::DomainData::User& sender)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
    ::DomainData::File* _r = new ::DomainData::File;
    return _r;
}
