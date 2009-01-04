#ifndef ___ServerInterfaces_impl_h__
#define ___ServerInterfaces_impl_h__

#include <ServerInterfaces_skel.h>

//
// IDL:DomainData:1.0
//
namespace DomainData
{

} // End of namespace DomainData

//
// IDL:ServerInterfaces:1.0
//
namespace ServerInterfaces
{

//
// IDL:ServerInterfaces/IServerServer:1.0
//
class IServerServer_impl : virtual public POA_ServerInterfaces::IServerServer,
                           virtual public PortableServer::RefCountServantBase
{
    IServerServer_impl(const IServerServer_impl&);
    void operator=(const IServerServer_impl&);

    PortableServer::POA_var poa_;

public:

    IServerServer_impl(PortableServer::POA_ptr);
    ~IServerServer_impl();

    virtual PortableServer::POA_ptr _default_POA();

    //
    // IDL:ServerInterfaces/IServerServer/Join:1.0
    //
    virtual ::ServerInterfaces::AddressesList* Join()
        throw(::CORBA::SystemException);

    //
    // IDL:ServerInterfaces/IServerServer/Unjoin:1.0
    //
    virtual void Unjoin()
        throw(::CORBA::SystemException);

    //
    // IDL:ServerInterfaces/IServerServer/AddServer:1.0
    //
    virtual void AddServer(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException);

    //
    // IDL:ServerInterfaces/IServerServer/RemoveServer:1.0
    //
    virtual void RemoveServer(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException);

    //
    // IDL:ServerInterfaces/IServerServer/PassMessage:1.0
    //
    virtual void PassMessage(const ::DomainData::Message& msg,
                             const ::DomainData::Address& senderAddress,
                             const ::DomainData::Address& receiverAddress)
        throw(::CORBA::SystemException);

    //
    // IDL:ServerInterfaces/IServerServer/PassCreatePipeRequest:1.0
    //
    virtual void PassCreatePipeRequest(const ::DomainData::Address& pipeHolderAddress,
                                       const ::DomainData::Address& senderAddress,
                                       const ::DomainData::Address& receiverAddress)
        throw(::CORBA::SystemException);

    //
    // IDL:ServerInterfaces/IServerServer/ClientStatusChanged:1.0
    //
    virtual void ClientStatusChanged(const ::DomainData::Address& clientAddress,
                                     const ::DomainData::Enability& en)
        throw(::CORBA::SystemException);
};

//
// IDL:ServerInterfaces/IServerClient:1.0
//
class IServerClient_impl : virtual public POA_ServerInterfaces::IServerClient,
                           virtual public PortableServer::RefCountServantBase
{
    IServerClient_impl(const IServerClient_impl&);
    void operator=(const IServerClient_impl&);

    PortableServer::POA_var poa_;

public:

    IServerClient_impl(PortableServer::POA_ptr);
    ~IServerClient_impl();

    virtual PortableServer::POA_ptr _default_POA();

    //
    // IDL:ServerInterfaces/IServerClient/Connect:1.0
    //
    virtual ::DomainData::Address* Connect(::DomainData::Mode m,
                                           const ::DomainData::User& usr)
        throw(::CORBA::SystemException);

    //
    // IDL:ServerInterfaces/IServerClient/Disconnect:1.0
    //
    virtual void Disconnect()
        throw(::CORBA::SystemException);

    //
    // IDL:ServerInterfaces/IServerClient/Register:1.0
    //
    virtual ::DomainData::User* Register(const ::DomainData::User& usr)
        throw(::CORBA::SystemException);

    //
    // IDL:ServerInterfaces/IServerClient/SendMessage:1.0
    //
    virtual void SendMessage(const ::DomainData::Address& receiverAddress,
                             const ::DomainData::Message& msg)
        throw(::CORBA::SystemException);

    //
    // IDL:ServerInterfaces/IServerClient/CheckClientStatus:1.0
    //
    virtual ::DomainData::Enability CheckClientStatus(const ::DomainData::Address& clientAddress)
        throw(::CORBA::SystemException);

    //
    // IDL:ServerInterfaces/IServerClient/GetPipeHolder:1.0
    //
    virtual ::DomainData::Address* GetPipeHolder(const ::DomainData::Address& receiverAddress)
        throw(::CORBA::SystemException);
};

} // End of namespace ServerInterfaces

#endif
