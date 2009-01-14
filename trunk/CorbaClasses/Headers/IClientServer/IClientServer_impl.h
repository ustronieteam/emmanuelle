#ifndef ___IClientServer_impl_h__
#define ___IClientServer_impl_h__

#include <IClientServer_skel.h>
#include "IRemoteObserverObject.h"

//
// IDL:IClientServer:1.0
//
class IClientServer_impl : virtual public POA_IClientServer,
                           virtual public PortableServer::RefCountServantBase,
						   virtual public IRemoteObserverObject
{
    IClientServer_impl(const IClientServer_impl&);
    void operator=(const IClientServer_impl&);

    PortableServer::POA_var poa_;

	//logger
	log4cxx::LoggerPtr logger;

public:

    IClientServer_impl(PortableServer::POA_ptr);
    ~IClientServer_impl();

    virtual PortableServer::POA_ptr _default_POA();

    //
    // IDL:IClientServer/ReceiveMessage:1.0
    //
    virtual void ReceiveMessage(const ::DomainData::User& sender,
                                const ::DomainData::Message& msg)
        throw(::CORBA::SystemException);

    //
    // IDL:IClientServer/ChangeServer:1.0
    //
    virtual void ChangeServer(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException);

    //
    // IDL:IClientServer/CreatePipeRequest:1.0
    //
    virtual ::CORBA::Boolean CreatePipeRequest(const ::DomainData::User& sender,
                                               const ::DomainData::User& pipeHolder)
        throw(::CORBA::SystemException);
};

#endif
