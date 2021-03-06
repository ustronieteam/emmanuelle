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

///
/// @author	Mateusz Kołodziejczyk
/// @date	06.01.2009
///
/// @brief	Klasa wygenerowana z pliku IDL IClientClient.idl
///

#ifndef ___IClientClient_h__
#define ___IClientClient_h__

#include <DomainData.h>

#ifndef OB_INTEGER_VERSION
#   error No ORBacus version defined! Is <OB/CORBA.h> included?
#endif

#ifndef OB_NO_VERSION_CHECK
#   if (OB_INTEGER_VERSION != 4030300L)
#       error ORBacus version mismatch!
#   endif
#endif

class IClientClient;
typedef IClientClient* IClientClient_ptr;
typedef IClientClient* IClientClientRef;

extern OB::TypeCodeConst _tc_IClientClient;

void OBDuplicate(IClientClient_ptr);
void OBRelease(IClientClient_ptr);

void OBMarshal(IClientClient_ptr, OB::OutputStreamImpl*);
void OBUnmarshal(IClientClient_ptr&, OB::InputStreamImpl*);

typedef OB::ObjVar< IClientClient > IClientClient_var;
typedef OB::ObjOut< IClientClient > IClientClient_out;

class OBStubImpl_IClientClient;
typedef OBStubImpl_IClientClient* OBStubImpl_IClientClient_ptr;

void OBDuplicate(OBStubImpl_IClientClient_ptr);
void OBRelease(OBStubImpl_IClientClient_ptr);

typedef OB::ObjVar< OBStubImpl_IClientClient > OBStubImpl_IClientClient_var;

//
// IDL:IClientClient:1.0
//
class IClientClient : virtual public ::CORBA::Object
{
    IClientClient(const IClientClient&);
    void operator=(const IClientClient&);

protected:

    static const char* ids_[];

public:

    IClientClient() { }
    virtual ~IClientClient() { }

    typedef IClientClient_ptr _ptr_type;
    typedef IClientClient_var _var_type;

    static inline IClientClient_ptr
    _duplicate(IClientClient_ptr p)
    {
        if(p)
            p -> _add_ref();
        return p;
    }

    static inline IClientClient_ptr
    _nil()
    {
        return 0;
    }

    static IClientClient_ptr _narrow(::CORBA::Object_ptr);
    static IClientClient_ptr _unchecked_narrow(::CORBA::Object_ptr);

    static IClientClient_ptr _narrow(::CORBA::AbstractBase_ptr);
    static IClientClient_ptr _unchecked_narrow(::CORBA::AbstractBase_ptr);

    static const char** _OB_staticIds();

    //
    // IDL:IClientClient/SendFile:1.0
    //
    virtual void SendFile(const ::DomainData::File& f,
                          const ::DomainData::User& receiver) = 0;

    //
    // IDL:IClientClient/CreatePipe:1.0
    //
    virtual void CreatePipe(const ::DomainData::User& receiver) = 0;

    //
    // IDL:IClientClient/GetFile:1.0
    //
    virtual ::DomainData::File* GetFile(const ::DomainData::User& sender) = 0;
};

//
// IDL:IClientClient:1.0
//
class OBProxy_IClientClient : virtual public ::IClientClient,
                              virtual public OBCORBA::Object
{
    OBProxy_IClientClient(const OBProxy_IClientClient&);
    void operator=(const OBProxy_IClientClient&);

protected:

    virtual OB::MarshalStubImpl_ptr _OB_createMarshalStubImpl();

public:

    OBProxy_IClientClient() { }
    virtual ~OBProxy_IClientClient() { }

    virtual const char** _OB_ids() const;

    //
    // IDL:IClientClient/SendFile:1.0
    //
    void SendFile(const ::DomainData::File& f,
                  const ::DomainData::User& receiver);

    //
    // IDL:IClientClient/CreatePipe:1.0
    //
    void CreatePipe(const ::DomainData::User& receiver);

    //
    // IDL:IClientClient/GetFile:1.0
    //
    ::DomainData::File* GetFile(const ::DomainData::User& sender);
};

//
// IDL:IClientClient:1.0
//
class OBStubImpl_IClientClient : virtual public OB::StubImplBase
{
    OBStubImpl_IClientClient(const OBStubImpl_IClientClient&);
    void operator=(const OBStubImpl_IClientClient&);

protected:

    OBStubImpl_IClientClient() { }

public:

    static inline OBStubImpl_IClientClient_ptr
    _duplicate(OBStubImpl_IClientClient_ptr p)
    {
        if(p)
            p -> _OB_incRef();
        return p;
    }

    static inline OBStubImpl_IClientClient_ptr
    _nil()
    {
        return 0;
    }

    //
    // IDL:IClientClient/SendFile:1.0
    //
    virtual void SendFile(const ::DomainData::File& f,
                          const ::DomainData::User& receiver) = 0;

    //
    // IDL:IClientClient/CreatePipe:1.0
    //
    virtual void CreatePipe(const ::DomainData::User& receiver) = 0;

    //
    // IDL:IClientClient/GetFile:1.0
    //
    virtual ::DomainData::File* GetFile(const ::DomainData::User& sender) = 0;
};

//
// IDL:IClientClient:1.0
//
class OBMarshalStubImpl_IClientClient : 
    virtual public OBStubImpl_IClientClient,
    virtual public OB::MarshalStubImpl
{
    OBMarshalStubImpl_IClientClient(const OBMarshalStubImpl_IClientClient&);
    void operator=(const OBMarshalStubImpl_IClientClient&);

protected:

    OBMarshalStubImpl_IClientClient() { }
    friend class OBProxy_IClientClient;

public:

    //
    // IDL:IClientClient/SendFile:1.0
    //
    virtual void SendFile(const ::DomainData::File& f,
                          const ::DomainData::User& receiver);

    //
    // IDL:IClientClient/CreatePipe:1.0
    //
    virtual void CreatePipe(const ::DomainData::User& receiver);

    //
    // IDL:IClientClient/GetFile:1.0
    //
    virtual ::DomainData::File* GetFile(const ::DomainData::User& sender);
};

//
// IDL:IClientClient:1.0
//
namespace CORBA
{

inline void
release(::IClientClient_ptr p)
{
    if(p)
        p -> _remove_ref();
}

inline Boolean
is_nil(::IClientClient_ptr p)
{
    return p == 0;
}

inline void
release(OBStubImpl_IClientClient_ptr p)
{
    if(p)
        p -> _OB_decRef();
}

inline Boolean
is_nil(OBStubImpl_IClientClient_ptr p)
{
    return p == 0;
}

} // End of namespace CORBA

void operator<<=(::CORBA::Any&, IClientClient_ptr*);
void operator<<=(::CORBA::Any&, IClientClient_ptr);
CORBA::Boolean operator>>=(const ::CORBA::Any&, IClientClient_ptr&);

inline void
operator<<=(::CORBA::Any_var& any, IClientClient_ptr* val)
{
    any.inout() <<= val;
}

inline void
operator<<=(::CORBA::Any_var& any, IClientClient_ptr val)
{
    any.inout() <<= val;
}

inline CORBA::Boolean
operator>>=(const ::CORBA::Any_var& any, IClientClient_ptr& val)
{
    return any.in() >>= val;
}

#endif
