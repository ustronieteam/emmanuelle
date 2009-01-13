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

#ifndef ___IServerServer_h__
#define ___IServerServer_h__

#include <DomainData.h>

#ifndef OB_INTEGER_VERSION
#   error No ORBacus version defined! Is <OB/CORBA.h> included?
#endif

#ifndef OB_NO_VERSION_CHECK
#   if (OB_INTEGER_VERSION != 4030300L)
#       error ORBacus version mismatch!
#   endif
#endif

class IServerServer;
typedef IServerServer* IServerServer_ptr;
typedef IServerServer* IServerServerRef;

extern OB::TypeCodeConst _tc_IServerServer;

void OBDuplicate(IServerServer_ptr);
void OBRelease(IServerServer_ptr);

void OBMarshal(IServerServer_ptr, OB::OutputStreamImpl*);
void OBUnmarshal(IServerServer_ptr&, OB::InputStreamImpl*);

typedef OB::ObjVar< IServerServer > IServerServer_var;
typedef OB::ObjOut< IServerServer > IServerServer_out;

class OBStubImpl_IServerServer;
typedef OBStubImpl_IServerServer* OBStubImpl_IServerServer_ptr;

void OBDuplicate(OBStubImpl_IServerServer_ptr);
void OBRelease(OBStubImpl_IServerServer_ptr);

typedef OB::ObjVar< OBStubImpl_IServerServer > OBStubImpl_IServerServer_var;

//
// IDL:AddressesList:1.0
//
class OBUnique_AddressesList { };

typedef OB::VarSeq< ::DomainData::Address, OBUnique_AddressesList > AddressesList;
typedef OB::SeqVar< OB::VarSeq< ::DomainData::Address, OBUnique_AddressesList > > AddressesList_var;
typedef OB::SeqOut< OB::VarSeq< ::DomainData::Address, OBUnique_AddressesList > > AddressesList_out;
extern OB::TypeCodeConst _tc_AddressesList;

struct OBInfo_AddressesList : public OB::ConstructedInfo
{
    OBInfo_AddressesList() { }

    virtual void free(void* p) const
    {
        delete (AddressesList*)p;
    }

    virtual void* dup(const void* p) const
    {
        return new AddressesList(*(const AddressesList*)p);
    }

    virtual void marshal(const void*, OB::OutputStreamImpl*) const;
    virtual void unmarshal(void*, OB::InputStreamImpl*) const;
};

//
// IDL:IServerServer:1.0
//
class IServerServer : virtual public ::CORBA::Object
{
    IServerServer(const IServerServer&);
    void operator=(const IServerServer&);

protected:

    static const char* ids_[];

public:

    IServerServer() { }
    virtual ~IServerServer() { }

    typedef IServerServer_ptr _ptr_type;
    typedef IServerServer_var _var_type;

    static inline IServerServer_ptr
    _duplicate(IServerServer_ptr p)
    {
        if(p)
            p -> _add_ref();
        return p;
    }

    static inline IServerServer_ptr
    _nil()
    {
        return 0;
    }

    static IServerServer_ptr _narrow(::CORBA::Object_ptr);
    static IServerServer_ptr _unchecked_narrow(::CORBA::Object_ptr);

    static IServerServer_ptr _narrow(::CORBA::AbstractBase_ptr);
    static IServerServer_ptr _unchecked_narrow(::CORBA::AbstractBase_ptr);

    static const char** _OB_staticIds();

    //
    // IDL:IServerServer/Join:1.0
    //
    virtual ::AddressesList* Join(const ::DomainData::Address& serverAddress) = 0;

    //
    // IDL:IServerServer/Unjoin:1.0
    //
    virtual void Unjoin() = 0;

    //
    // IDL:IServerServer/AddServer:1.0
    //
    virtual void AddServer(const ::DomainData::Address& serverAddress) = 0;

    //
    // IDL:IServerServer/RemoveServer:1.0
    //
    virtual void RemoveServer(const ::DomainData::Address& serverAddress) = 0;

    //
    // IDL:IServerServer/PassMessage:1.0
    //
    virtual void PassMessage(const ::DomainData::Message& msg,
                             const ::DomainData::User& sender,
                             const ::DomainData::User& receiver) = 0;

    //
    // IDL:IServerServer/PassCreatePipeRequest:1.0
    //
    virtual void PassCreatePipeRequest(const ::DomainData::User& pipeHolder,
                                       const ::DomainData::User& sender,
                                       const ::DomainData::User& receiver) = 0;

    //
    // IDL:IServerServer/ClientStatusChanged:1.0
    //
    virtual void ClientStatusChanged(const ::DomainData::User& client,
                                     const ::DomainData::Address& clientAddress,
                                     const ::DomainData::Enability& en,
                                     const ::DomainData::Address& senderServerAddress) = 0;
};

//
// IDL:IServerServer:1.0
//
class OBProxy_IServerServer : virtual public ::IServerServer,
                              virtual public OBCORBA::Object
{
    OBProxy_IServerServer(const OBProxy_IServerServer&);
    void operator=(const OBProxy_IServerServer&);

protected:

    virtual OB::MarshalStubImpl_ptr _OB_createMarshalStubImpl();

public:

    OBProxy_IServerServer() { }
    virtual ~OBProxy_IServerServer() { }

    virtual const char** _OB_ids() const;

    //
    // IDL:IServerServer/Join:1.0
    //
    ::AddressesList* Join(const ::DomainData::Address& serverAddress);

    //
    // IDL:IServerServer/Unjoin:1.0
    //
    void Unjoin();

    //
    // IDL:IServerServer/AddServer:1.0
    //
    void AddServer(const ::DomainData::Address& serverAddress);

    //
    // IDL:IServerServer/RemoveServer:1.0
    //
    void RemoveServer(const ::DomainData::Address& serverAddress);

    //
    // IDL:IServerServer/PassMessage:1.0
    //
    void PassMessage(const ::DomainData::Message& msg,
                     const ::DomainData::User& sender,
                     const ::DomainData::User& receiver);

    //
    // IDL:IServerServer/PassCreatePipeRequest:1.0
    //
    void PassCreatePipeRequest(const ::DomainData::User& pipeHolder,
                               const ::DomainData::User& sender,
                               const ::DomainData::User& receiver);

    //
    // IDL:IServerServer/ClientStatusChanged:1.0
    //
    void ClientStatusChanged(const ::DomainData::User& client,
                             const ::DomainData::Address& clientAddress,
                             const ::DomainData::Enability& en,
                             const ::DomainData::Address& senderServerAddress);
};

//
// IDL:IServerServer:1.0
//
class OBStubImpl_IServerServer : virtual public OB::StubImplBase
{
    OBStubImpl_IServerServer(const OBStubImpl_IServerServer&);
    void operator=(const OBStubImpl_IServerServer&);

protected:

    OBStubImpl_IServerServer() { }

public:

    static inline OBStubImpl_IServerServer_ptr
    _duplicate(OBStubImpl_IServerServer_ptr p)
    {
        if(p)
            p -> _OB_incRef();
        return p;
    }

    static inline OBStubImpl_IServerServer_ptr
    _nil()
    {
        return 0;
    }

    //
    // IDL:IServerServer/Join:1.0
    //
    virtual ::AddressesList* Join(const ::DomainData::Address& serverAddress) = 0;

    //
    // IDL:IServerServer/Unjoin:1.0
    //
    virtual void Unjoin() = 0;

    //
    // IDL:IServerServer/AddServer:1.0
    //
    virtual void AddServer(const ::DomainData::Address& serverAddress) = 0;

    //
    // IDL:IServerServer/RemoveServer:1.0
    //
    virtual void RemoveServer(const ::DomainData::Address& serverAddress) = 0;

    //
    // IDL:IServerServer/PassMessage:1.0
    //
    virtual void PassMessage(const ::DomainData::Message& msg,
                             const ::DomainData::User& sender,
                             const ::DomainData::User& receiver) = 0;

    //
    // IDL:IServerServer/PassCreatePipeRequest:1.0
    //
    virtual void PassCreatePipeRequest(const ::DomainData::User& pipeHolder,
                                       const ::DomainData::User& sender,
                                       const ::DomainData::User& receiver) = 0;

    //
    // IDL:IServerServer/ClientStatusChanged:1.0
    //
    virtual void ClientStatusChanged(const ::DomainData::User& client,
                                     const ::DomainData::Address& clientAddress,
                                     const ::DomainData::Enability& en,
                                     const ::DomainData::Address& senderServerAddress) = 0;
};

//
// IDL:IServerServer:1.0
//
class OBMarshalStubImpl_IServerServer : 
    virtual public OBStubImpl_IServerServer,
    virtual public OB::MarshalStubImpl
{
    OBMarshalStubImpl_IServerServer(const OBMarshalStubImpl_IServerServer&);
    void operator=(const OBMarshalStubImpl_IServerServer&);

protected:

    OBMarshalStubImpl_IServerServer() { }
    friend class OBProxy_IServerServer;

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
                             const ::DomainData::User& sender,
                             const ::DomainData::User& receiver);

    //
    // IDL:IServerServer/PassCreatePipeRequest:1.0
    //
    virtual void PassCreatePipeRequest(const ::DomainData::User& pipeHolder,
                                       const ::DomainData::User& sender,
                                       const ::DomainData::User& receiver);

    //
    // IDL:IServerServer/ClientStatusChanged:1.0
    //
    virtual void ClientStatusChanged(const ::DomainData::User& client,
                                     const ::DomainData::Address& clientAddress,
                                     const ::DomainData::Enability& en,
                                     const ::DomainData::Address& senderServerAddress);
};

//
// IDL:AddressesList:1.0
//
void operator<<=(::CORBA::Any&, AddressesList*);
void operator<<=(::CORBA::Any&, const AddressesList&);
CORBA::Boolean operator>>=(const ::CORBA::Any&, const AddressesList*&);

inline void
operator<<=(::CORBA::Any_var& any, AddressesList* val)
{
    any.inout() <<= val;
}

inline void
operator<<=(::CORBA::Any_var& any, const AddressesList& val)
{
    any.inout() <<= val;
}

inline ::CORBA::Boolean
operator>>=(const ::CORBA::Any_var& any, const AddressesList*& val)
{
    return any.in() >>= val;
}

//
// IDL:IServerServer:1.0
//
namespace CORBA
{

inline void
release(::IServerServer_ptr p)
{
    if(p)
        p -> _remove_ref();
}

inline Boolean
is_nil(::IServerServer_ptr p)
{
    return p == 0;
}

inline void
release(OBStubImpl_IServerServer_ptr p)
{
    if(p)
        p -> _OB_decRef();
}

inline Boolean
is_nil(OBStubImpl_IServerServer_ptr p)
{
    return p == 0;
}

} // End of namespace CORBA

void operator<<=(::CORBA::Any&, IServerServer_ptr*);
void operator<<=(::CORBA::Any&, IServerServer_ptr);
CORBA::Boolean operator>>=(const ::CORBA::Any&, IServerServer_ptr&);

inline void
operator<<=(::CORBA::Any_var& any, IServerServer_ptr* val)
{
    any.inout() <<= val;
}

inline void
operator<<=(::CORBA::Any_var& any, IServerServer_ptr val)
{
    any.inout() <<= val;
}

inline CORBA::Boolean
operator>>=(const ::CORBA::Any_var& any, IServerServer_ptr& val)
{
    return any.in() >>= val;
}

#endif
