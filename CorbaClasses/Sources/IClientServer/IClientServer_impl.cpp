#include <OB/CORBA.h>
#include <IClientServer_impl.h>

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include "CorbaConnector.h"
#include "Model.h"
//
// IDL:IClientServer:1.0
//
IClientServer_impl::IClientServer_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
	//logger
	logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("IClinetServer_impl"));
	logger->setLevel(LOGLEVEL);
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
IClientServer_impl::ReceiveMessage(const ::DomainData::User& sender,
                                   const ::DomainData::Message& msg)
    throw(::CORBA::SystemException)
{
	LOG4CXX_DEBUG(logger, "WYWOLANIE RECEIVEMESSAGE");

	RemoteObserverData observData;
	observData.SetObserverType(MESSAGE);
	observData.SetSenderMessage(msg);
	observData.SetUser(sender);

	this->Notify(observData);
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

// funkcja puszczana w odzienlnym watku do nasluchu czy utworzono pipe i mozna odebrac plik
void runGetFileThread(IClientClient_var client, DomainData::User sender, IClientServer_impl * cl)
{
	//logger
	log4cxx::LoggerPtr logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("IClinetServer_impl"));
	logger->setLevel(LOGLEVEL);

	try
	{
		while(true)
		{
			LOG4CXX_DEBUG(logger, "... proba wywolania GetFile.");

			DomainData::File * f = client->GetFile(sender);
			
			if(strcmp(f->name.in(), ""))
			{
				LOG4CXX_DEBUG(logger, "Znalezino plik na pipe holderze");
				RemoteObserverData observData;
				observData.SetObserverType(FFILE);
				observData.SetUser(sender);

				LOG4CXX_DEBUG(logger, "Zawartosc body: " << f->body.get_buffer());

				std::ofstream fileStream(f->name.in(), std::ios_base::binary);
				if(fileStream.is_open())
				{
					observData.SetFileName(f->name.in());

					char * content = const_cast<char *>(f->body.get_buffer());
					fileStream.write(content, f->size);

					fileStream.close();
				}

				cl->Notify(observData);
				

				break;
			}
			else
				LOG4CXX_DEBUG(logger, "... nie ma pliku na pipeholderze.");

#ifndef WIN32
			sleep(5);
#else
			Sleep(5000);
#endif
		}
	}
	catch(CORBA::SystemException & e)
	{
	}
}

//
// IDL:IClientServer/CreatePipeRequest:1.0
//
::CORBA::Boolean
IClientServer_impl::CreatePipeRequest(const ::DomainData::User& sender,
                                      const ::DomainData::User& pipeHolder)
    throw(::CORBA::SystemException)
{
	LOG4CXX_DEBUG(logger, "WYWOLANIE CREATEPIPEREQUEST ");
	
	try
	{
		IServerClient_var server = Model::GetInstance()->GetServerInstance();

		CORBA::ORB_var orb;
		IClientClient_var client;

		if(!CorbaConnector::connectToClientClient(server->GetUserAddressByName(pipeHolder)->localization.in(), orb, client))
		{
			LOG4CXX_ERROR(logger, "Nie mozna polaczyc sie z klientem");
			return false;
		}
		DomainData::User sender2 = sender;
		sender2.number = 0;
		client->CreatePipe(sender2);
		boost::thread watekGetFile(boost::bind(&runGetFileThread, client, sender2, this));
	}
	catch(CORBA::SystemException & e)
	{
		LOG4CXX_ERROR(logger, "nie mozna utworzyc pipe'a" << e._to_string());
		return false;
	}

	LOG4CXX_DEBUG(logger, "Powodzenie CREATEPIPEREQUEST");
    return true;
}
