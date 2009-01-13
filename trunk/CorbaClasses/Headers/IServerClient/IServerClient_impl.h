#ifndef ___IServerClient_impl_h__
#define ___IServerClient_impl_h__

#include <IServerClient_skel.h>
#include "IRemoteObjects.h"

#include <log4cxx/logger.h>
#include <log4cxx/level.h>
//
// IDL:IServerClient:1.0
//
class IServerClient_impl : virtual public POA_IServerClient,
                           virtual public PortableServer::RefCountServantBase,
						   virtual public IRemoteObjects
{
    IServerClient_impl(const IServerClient_impl&);
    void operator=(const IServerClient_impl&);

    PortableServer::POA_var poa_;

	// logger
	log4cxx::LoggerPtr logger;

public:

    IServerClient_impl(PortableServer::POA_ptr);
    ~IServerClient_impl();

    virtual PortableServer::POA_ptr _default_POA();

    //
    // IDL:IServerClient/Connect:1.0
    //
    virtual ::DomainData::Address* Connect(const ::DomainData::Address& server,
                                           ::DomainData::Mode m,
                                           const ::DomainData::User& usr)
        throw(::CORBA::SystemException);

    //
    // IDL:IServerClient/Disconnect:1.0
    //
    virtual void Disconnect(const ::DomainData::User& usr)
        throw(::CORBA::SystemException);

    //
    // IDL:IServerClient/Register:1.0
    //
    virtual ::DomainData::User* Register(const ::DomainData::User& usr)
        throw(::CORBA::SystemException);

    //
    // IDL:IServerClient/SendMessage:1.0
    //
    virtual void SendMessage(const ::DomainData::User& ssender,
                             const ::DomainData::User& receiver,
                             const ::DomainData::Message& msg)
        throw(::CORBA::SystemException);

    //
    // IDL:IServerClient/CheckClientStatus:1.0
    //
    virtual ::DomainData::Enability CheckClientStatus(const ::DomainData::User& usr)
        throw(::CORBA::SystemException);

    //
    // IDL:IServerClient/GetPipeHolder:1.0
    //
    virtual ::DomainData::User* GetPipeHolder(const ::DomainData::User& receiver)
        throw(::CORBA::SystemException);

    //
    // IDL:IServerClient/GetUserAddressByName:1.0
    //
    virtual ::DomainData::Address* GetUserAddressByName(const ::DomainData::User& usr)
        throw(::CORBA::SystemException);
};

#endif
