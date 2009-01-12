// **********************************************************************
//
// Generated by the ORBacus IDL-to-C++ Translator
//
// Copyright (c) 2005
// IONA Technologies, Inc.
// Waltham, MA, USA
//
// All Rights Reserved
//
// **********************************************************************

// Version: 4.3.3

#ifndef ___IServerServer_skel_h__
#define ___IServerServer_skel_h__

#include <IServerServer.h>

#ifndef OB_INTEGER_VERSION
#   error No ORBacus version defined! Is <OB/CORBA.h> included?
#endif

#ifndef OB_NO_VERSION_CHECK
#   if (OB_INTEGER_VERSION != 4030300L)
#       error ORBacus version mismatch!
#   endif
#endif

//
// IDL:IServerServer:1.0
//
class POA_IServerServer : virtual public PortableServer::ServantBase
{
    POA_IServerServer(const POA_IServerServer&);
    void operator=(const POA_IServerServer&);

protected:

    //
    // IDL:IServerServer/Join:1.0
    //
    void _OB_op_Join(OB::Upcall_ptr);

    //
    // IDL:IServerServer/Unjoin:1.0
    //
    void _OB_op_Unjoin(OB::Upcall_ptr);

    //
    // IDL:IServerServer/AddServer:1.0
    //
    void _OB_op_AddServer(OB::Upcall_ptr);

    //
    // IDL:IServerServer/RemoveServer:1.0
    //
    void _OB_op_RemoveServer(OB::Upcall_ptr);

    //
    // IDL:IServerServer/PassMessage:1.0
    //
    void _OB_op_PassMessage(OB::Upcall_ptr);

    //
    // IDL:IServerServer/PassCreatePipeRequest:1.0
    //
    void _OB_op_PassCreatePipeRequest(OB::Upcall_ptr);

    //
    // IDL:IServerServer/ClientStatusChanged:1.0
    //
    void _OB_op_ClientStatusChanged(OB::Upcall_ptr);

public:

    POA_IServerServer() { }

    virtual ::CORBA::Boolean _is_a(const char*)
        throw(::CORBA::SystemException);

    virtual ::CORBA::RepositoryId _primary_interface(
        const PortableServer::ObjectId&,
        PortableServer::POA_ptr);

    IServerServer_ptr _this();

    virtual OB::DirectStubImpl_ptr _OB_createDirectStubImpl(
        PortableServer::POA_ptr,
        const PortableServer::ObjectId&);
    virtual void _OB_dispatch(OB::Upcall_ptr);

    //
    // IDL:IServerServer/Join:1.0
    //
    virtual ::AddressesList* Join(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException) = 0;

    //
    // IDL:IServerServer/Unjoin:1.0
    //
    virtual void Unjoin()
        throw(::CORBA::SystemException) = 0;

    //
    // IDL:IServerServer/AddServer:1.0
    //
    virtual void AddServer(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException) = 0;

    //
    // IDL:IServerServer/RemoveServer:1.0
    //
    virtual void RemoveServer(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException) = 0;

    //
    // IDL:IServerServer/PassMessage:1.0
    //
    virtual void PassMessage(const ::DomainData::Message& msg,
                             const ::DomainData::Address& senderAddress,
                             const ::DomainData::Address& receiverAddress)
        throw(::CORBA::SystemException) = 0;

    //
    // IDL:IServerServer/PassCreatePipeRequest:1.0
    //
    virtual void PassCreatePipeRequest(const ::DomainData::Address& pipeHolderAddress,
                                       const ::DomainData::Address& senderAddress,
                                       const ::DomainData::Address& receiverAddress)
        throw(::CORBA::SystemException) = 0;

    //
    // IDL:IServerServer/ClientStatusChanged:1.0
    //
    virtual void ClientStatusChanged(const ::DomainData::Address& clientAddress,
                                     const ::DomainData::Enability& en,
                                     const ::DomainData::User& usr)
        throw(::CORBA::SystemException) = 0;
};

//
// IDL:IServerServer:1.0
//
class OBDirectStubImpl_IServerServer : virtual public OBStubImpl_IServerServer,
                                       virtual public OB::DirectStubImpl
{
    OBDirectStubImpl_IServerServer(const OBDirectStubImpl_IServerServer&);
    void operator=(const OBDirectStubImpl_IServerServer&);

protected:

#ifdef HAVE_VCPLUSPLUS_BUGS

    OBDirectStubImpl_IServerServer() { }

#endif

    OBDirectStubImpl_IServerServer(PortableServer::POA_ptr,
                                   const PortableServer::ObjectId&,
                                   PortableServer::ServantBase*);

    friend class POA_IServerServer;

public:

    //
    // IDL:IServerServer/Join:1.0
    //
    virtual ::AddressesList* Join(const ::DomainData::Address& serverAddress);

    //
    // IDL:IServerServer/Unjoin:1.0
    //
    virtual void Unjoin();

    //
    // IDL:IServerServer/AddServer:1.0
    //
    virtual void AddServer(const ::DomainData::Address& serverAddress);

    //
    // IDL:IServerServer/RemoveServer:1.0
    //
    virtual void RemoveServer(const ::DomainData::Address& serverAddress);

    //
    // IDL:IServerServer/PassMessage:1.0
    //
    virtual void PassMessage(const ::DomainData::Message& msg,
                             const ::DomainData::Address& senderAddress,
                             const ::DomainData::Address& receiverAddress);

    //
    // IDL:IServerServer/PassCreatePipeRequest:1.0
    //
    virtual void PassCreatePipeRequest(const ::DomainData::Address& pipeHolderAddress,
                                       const ::DomainData::Address& senderAddress,
                                       const ::DomainData::Address& receiverAddress);

    //
    // IDL:IServerServer/ClientStatusChanged:1.0
    //
    virtual void ClientStatusChanged(const ::DomainData::Address& clientAddress,
                                     const ::DomainData::Enability& en,
                                     const ::DomainData::User& usr);
};

#endif
