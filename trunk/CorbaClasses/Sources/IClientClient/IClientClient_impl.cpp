#include <OB/CORBA.h>
#include <IClientClient_impl.h>
#include <fstream>

//
// IDL:IClientClient:1.0
//
IClientClient_impl::IClientClient_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
	//logger
	logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("IClinetServer_impl"));
	logger->setLevel(log4cxx::Level::getAll());
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
	LOG4CXX_DEBUG(logger, "WYWOLANIE SENDFILE");

	RemoteObserverData observData;
	observData.SetObserverType(FFILE);
	observData.SetUser(receiver);

	LOG4CXX_DEBUG(logger, "Zawartosc body: " << f.body.get_buffer());

	std::ofstream fileStream(f.name.in(), std::ios_base::binary);
	if(fileStream.is_open())
	{
		observData.SetFileName(f.name.in());

		char * content = const_cast<char *>(f.body.get_buffer());
		fileStream.write(content, f.size);

		fileStream.close();
	}

	this->Notify(observData);
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
