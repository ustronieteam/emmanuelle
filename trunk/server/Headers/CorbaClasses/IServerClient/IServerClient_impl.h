///
/// @author	Mateusz Ko³odziejczyk
/// @date	06.01.2009
///
/// @brief	Wygenerowano z IServerClient.idl
///

#ifndef ___IServerClient_impl_h__
#define ___IServerClient_impl_h__

#include <IServerClient_skel.h>
#include "IRemoteObjects.h"

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

public:

    IServerClient_impl(PortableServer::POA_ptr);
    ~IServerClient_impl();

    virtual PortableServer::POA_ptr _default_POA();

    //
    // IDL:IServerClient/Connect:1.0
    //
    virtual ::DomainData::Address* Connect(::DomainData::Mode m,
                                           const ::DomainData::User& usr)
        throw(::CORBA::SystemException);

    //
    // IDL:IServerClient/Disconnect:1.0
    //
    virtual void Disconnect()
        throw(::CORBA::SystemException);

    //
    // IDL:IServerClient/Register:1.0
    //
    virtual ::DomainData::User* Register(const ::DomainData::User& usr)
        throw(::CORBA::SystemException);

    //
    // IDL:IServerClient/SendMessage:1.0
    //
    virtual void SendMessage(const ::DomainData::Address& receiverAddress,
                             const ::DomainData::Message& msg)
        throw(::CORBA::SystemException);

    //
    // IDL:IServerClient/CheckClientStatus:1.0
    //
    virtual ::DomainData::Enability CheckClientStatus(const ::DomainData::Address& clientAddress)
        throw(::CORBA::SystemException);

    //
    // IDL:IServerClient/GetPipeHolder:1.0
    //
    virtual ::DomainData::Address* GetPipeHolder(const ::DomainData::Address& receiverAddress)
        throw(::CORBA::SystemException);
};

#endif
