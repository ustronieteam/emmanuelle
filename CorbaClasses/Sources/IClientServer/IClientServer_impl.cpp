#include <OB/CORBA.h>
#include <IClientServer_impl.h>

//
// IDL:IClientServer:1.0
//
IClientServer_impl::IClientServer_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
	//logger
	logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("IClientServer_impl"));
	logger->setLevel(log4cxx::Level::getAll());
}

IClientServer_impl::~IClientServer_impl()
{
}

PortableServer::POA_ptr
IClientServer_impl::_default_POA()
{
    return PortableServer::POA::_duplicate(poa_);
}

//
// IDL:IClientServer/ReceiveMessage:1.0
//
void
IClientServer_impl::ReceiveMessage(const ::DomainData::Address& senderAddress,
                                   const ::DomainData::Message& msg)
    throw(::CORBA::SystemException)
{
	//RemoteObserverData observData;
	//observData.set_eventType(re);
	//observData.setClientMessage(msg);
	//observData.setClientAddress(receiverAddress);

	//this->Notify(observData);
}

//
// IDL:IClientServer/ChangeServer:1.0
//
void
IClientServer_impl::ChangeServer(const ::DomainData::Address& serverAddress)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:IClientServer/CreatePipeRequest:1.0
//
::CORBA::Boolean
IClientServer_impl::CreatePipeRequest(const ::DomainData::Address& pipeHolderAddress,
                                      const ::DomainData::Address& senderAddress)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
    ::CORBA::Boolean _r = false;
    return _r;
}
