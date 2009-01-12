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

#ifndef ___IServerClient_skel_h__
#define ___IServerClient_skel_h__

#include <IServerClient.h>

#ifndef OB_INTEGER_VERSION
#   error No ORBacus version defined! Is <OB/CORBA.h> included?
#endif

#ifndef OB_NO_VERSION_CHECK
#   if (OB_INTEGER_VERSION != 4030300L)
#       error ORBacus version mismatch!
#   endif
#endif

//
// IDL:IServerClient:1.0
//
class POA_IServerClient : virtual public PortableServer::ServantBase
{
    POA_IServerClient(const POA_IServerClient&);
    void operator=(const POA_IServerClient&);

protected:

    //
    // IDL:IServerClient/Connect:1.0
    //
    void _OB_op_Connect(OB::Upcall_ptr);

    //
    // IDL:IServerClient/Disconnect:1.0
    //
    void _OB_op_Disconnect(OB::Upcall_ptr);

    //
    // IDL:IServerClient/Register:1.0
    //
    void _OB_op_Register(OB::Upcall_ptr);

    //
    // IDL:IServerClient/SendMessage:1.0
    //
    void _OB_op_SendMessage(OB::Upcall_ptr);

    //
    // IDL:IServerClient/CheckClientStatus:1.0
    //
    void _OB_op_CheckClientStatus(OB::Upcall_ptr);

    //
    // IDL:IServerClient/GetPipeHolder:1.0
    //
    void _OB_op_GetPipeHolder(OB::Upcall_ptr);

public:

    POA_IServerClient() { }

    virtual ::CORBA::Boolean _is_a(const char*)
        throw(::CORBA::SystemException);

    virtual ::CORBA::RepositoryId _primary_interface(
        const PortableServer::ObjectId&,
        PortableServer::POA_ptr);

    IServerClient_ptr _this();

    virtual OB::DirectStubImpl_ptr _OB_createDirectStubImpl(
        PortableServer::POA_ptr,
        const PortableServer::ObjectId&);
    virtual void _OB_dispatch(OB::Upcall_ptr);

    //
    // IDL:IServerClient/Connect:1.0
    //
    virtual ::DomainData::Address* Connect(const ::DomainData::Address& server,
                                           ::DomainData::Mode m,
                                           const ::DomainData::User& usr)
        throw(::CORBA::SystemException) = 0;

    //
    // IDL:IServerClient/Disconnect:1.0
    //
    virtual void Disconnect(const ::DomainData::User& usr)
        throw(::CORBA::SystemException) = 0;

    //
    // IDL:IServerClient/Register:1.0
    //
    virtual ::DomainData::User* Register(const ::DomainData::User& usr)
        throw(::CORBA::SystemException) = 0;

    //
    // IDL:IServerClient/SendMessage:1.0
    //
    virtual void SendMessage(const ::DomainData::Address& receiverAddress,
                             const ::DomainData::Message& msg)
        throw(::CORBA::SystemException) = 0;

    //
    // IDL:IServerClient/CheckClientStatus:1.0
    //
    virtual ::DomainData::Enability CheckClientStatus(const ::DomainData::Address& clientAddress)
        throw(::CORBA::SystemException) = 0;

    //
    // IDL:IServerClient/GetPipeHolder:1.0
    //
    virtual ::DomainData::Address* GetPipeHolder(const ::DomainData::Address& receiverAddress)
        throw(::CORBA::SystemException) = 0;
};

//
// IDL:IServerClient:1.0
//
class OBDirectStubImpl_IServerClient : virtual public OBStubImpl_IServerClient,
                                       virtual public OB::DirectStubImpl
{
    OBDirectStubImpl_IServerClient(const OBDirectStubImpl_IServerClient&);
    void operator=(const OBDirectStubImpl_IServerClient&);

protected:

#ifdef HAVE_VCPLUSPLUS_BUGS

    OBDirectStubImpl_IServerClient() { }

#endif

    OBDirectStubImpl_IServerClient(PortableServer::POA_ptr,
                                   const PortableServer::ObjectId&,
                                   PortableServer::ServantBase*);

    friend class POA_IServerClient;

public:

    //
    // IDL:IServerClient/Connect:1.0
    //
    virtual ::DomainData::Address* Connect(const ::DomainData::Address& server,
                                           ::DomainData::Mode m,
                                           const ::DomainData::User& usr);

    //
    // IDL:IServerClient/Disconnect:1.0
    //
    virtual void Disconnect(const ::DomainData::User& usr);

    //
    // IDL:IServerClient/Register:1.0
    //
    virtual ::DomainData::User* Register(const ::DomainData::User& usr);

    //
    // IDL:IServerClient/SendMessage:1.0
    //
    virtual void SendMessage(const ::DomainData::Address& receiverAddress,
                             const ::DomainData::Message& msg);

    //
    // IDL:IServerClient/CheckClientStatus:1.0
    //
    virtual ::DomainData::Enability CheckClientStatus(const ::DomainData::Address& clientAddress);

    //
    // IDL:IServerClient/GetPipeHolder:1.0
    //
    virtual ::DomainData::Address* GetPipeHolder(const ::DomainData::Address& receiverAddress);
};

#endif
