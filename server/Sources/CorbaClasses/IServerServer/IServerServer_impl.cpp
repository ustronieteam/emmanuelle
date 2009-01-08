#include <OB/CORBA.h>
#include <IServerServer_impl.h>
#include <Server.h>

//
// IDL:IServerServer:1.0
//
IServerServer_impl::IServerServer_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
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
IServerServer_impl::Join()
    throw(::CORBA::SystemException)
{
	std::cout << "WYWOLANIE JOIN z adresu: " << Server::GetRemotedAddress() << std::endl;

	std::vector<ServerRecord> & serversList = ServerDataBase::GetInstance()->GetAllRecords();

	RemoteObserverData observData;
	observData.set_eventType(EventType::SERVER_CONNECTED);
	
	::DomainData::Address adres;
	adres.localization = Server::GetRemotedAddress();
	
	observData.setServerAddress(adres);

	this->Notify(observData);

	// TODO: dokonczyc
	::AddressesList* _r = new ::AddressesList(serversList.size() + 1);
	
	std::cout << "dlugosc: " << _r->length()  << ", max: " << _r->maximum() << std::endl;

	//for(int i = 0; i < serversList.size(); ++i)
	//	(*_r)[i] = serversList[i].GetAddress();

    return _r;
}

//
// IDL:IServerServer/Unjoin:1.0
//
void
IServerServer_impl::Unjoin()
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:IServerServer/AddServer:1.0
//
void
IServerServer_impl::AddServer(const ::DomainData::Address& serverAddress)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:IServerServer/RemoveServer:1.0
//
void
IServerServer_impl::RemoveServer(const ::DomainData::Address& serverAddress)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
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
    // TODO: Implementation
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
                                        const ::DomainData::Enability& en)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}
