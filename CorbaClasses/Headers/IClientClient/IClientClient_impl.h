#ifndef ___IClientClient_impl_h__
#define ___IClientClient_impl_h__

#include <IClientClient_skel.h>
#include "IRemoteObserverObject.h"

//
// IDL:IClientClient:1.0
//
class IClientClient_impl : virtual public POA_IClientClient,
                           virtual public PortableServer::RefCountServantBase,
						   virtual public IRemoteObserverObject
{
    IClientClient_impl(const IClientClient_impl&);
    void operator=(const IClientClient_impl&);

    PortableServer::POA_var poa_;

	//logger
	log4cxx::LoggerPtr logger;

public:

    IClientClient_impl(PortableServer::POA_ptr);
    ~IClientClient_impl();

    virtual PortableServer::POA_ptr _default_POA();

    //
    // IDL:IClientClient/SendFile:1.0
    //
    virtual void SendFile(const ::DomainData::File& f,
                          const ::DomainData::Address& receiverAddress)
        throw(::CORBA::SystemException);

    //
    // IDL:IClientClient/CreatePipe:1.0
    //
    virtual void CreatePipe()
        throw(::CORBA::SystemException);

    //
    // IDL:IClientClient/GetFile:1.0
    //
    virtual ::DomainData::File* GetFile(const ::DomainData::Address& senderAddress)
        throw(::CORBA::SystemException);
};

#endif
