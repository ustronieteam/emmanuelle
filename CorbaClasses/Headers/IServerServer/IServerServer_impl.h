#ifndef ___IServerServer_impl_h__
#define ___IServerServer_impl_h__

#include <IServerServer_skel.h>
#include "IRemoteObjects.h"

//
// IDL:IServerServer:1.0
//
class IServerServer_impl : virtual public POA_IServerServer,
                           virtual public PortableServer::RefCountServantBase,
						   virtual public IRemoteObjects
{
    IServerServer_impl(const IServerServer_impl&);
    void operator=(const IServerServer_impl&);

    PortableServer::POA_var poa_;

public:

    IServerServer_impl(PortableServer::POA_ptr);
    ~IServerServer_impl();

    virtual PortableServer::POA_ptr _default_POA();

    //
    // IDL:IServerServer/Join:1.0
    //
    virtual ::AddressesList* Join(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException);

    //
    // IDL:IServerServer/Unjoin:1.0
    //
    virtual void Unjoin()
        throw(::CORBA::SystemException);

    //
    // IDL:IServerServer/AddServer:1.0
    //
    virtual void AddServer(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException);

    //
    // IDL:IServerServer/RemoveServer:1.0
    //
    virtual void RemoveServer(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException);

    //
    // IDL:IServerServer/PassMessage:1.0
    //
    virtual void PassMessage(const ::DomainData::Message& msg,
                             const ::DomainData::Address& senderAddress,
                             const ::DomainData::Address& receiverAddress)
        throw(::CORBA::SystemException);

    //
    // IDL:IServerServer/PassCreatePipeRequest:1.0
    //
    virtual void PassCreatePipeRequest(const ::DomainData::Address& pipeHolderAddress,
                                       const ::DomainData::Address& senderAddress,
                                       const ::DomainData::Address& receiverAddress)
        throw(::CORBA::SystemException);

    //
    // IDL:IServerServer/ClientStatusChanged:1.0
    //
    virtual void ClientStatusChanged(const ::DomainData::Address& clientAddress,
                                     const ::DomainData::Enability& en,
                                     const ::DomainData::User& usr,
                                     const ::DomainData::Address& senderAddress)
        throw(::CORBA::SystemException);
};

#endif
