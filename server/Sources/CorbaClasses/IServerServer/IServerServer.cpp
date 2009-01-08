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

#include <OB/CORBAClient.h>
#include <IServerServer.h>

#ifndef OB_INTEGER_VERSION
#   error No ORBacus version defined! Is <OB/CORBA.h> included?
#endif

#ifndef OB_NO_VERSION_CHECK
#   if (OB_INTEGER_VERSION != 4030300L)
#       error ORBacus version mismatch!
#   endif
#endif

::OB::TypeCodeConst _tc_AddressesList(
"019e630015000000b00000000102917c1600000049444c3a4164647265737365734c6973743a3"
"12e300063000e0000004164647265737365734c697374004c001300000074000000010000000f"
"0000006400000001e612001b00000049444c3a446f6d61696e446174612f416464726573733a3"
"12e30000008000000416464726573730002000000050000006e616d650001917c120000000000"
"00000d0000006c6f63616c697a6174696f6e00e61200120000000000000000000000"
);

::OB::TypeCodeConst _tc_IServerServer(
"019e63000e000000320000000102917c1600000049444c3a495365727665725365727665723a3"
"12e300063000e0000004953657276657253657276657200"
);

//
// IDL:AddressesList:1.0
//
void
OBInfo_AddressesList::marshal(const void* _ob_v, OB::OutputStreamImpl* _ob_out) const
{
    const ::AddressesList& _ob_seq = *(const ::AddressesList*)_ob_v;
    ::CORBA::ULong _ob_len0 = _ob_seq.length();
    _ob_out -> write_ulong(_ob_len0);
    ::DomainData::Address const * _ob_buf0 = _ob_seq.get_buffer();
    for(::CORBA::ULong _ob_i0 = 0 ; _ob_i0 < _ob_len0 ; _ob_i0++)
    {
        _ob_buf0[_ob_i0]._OB_marshal(_ob_out);
    }
}

void
OBInfo_AddressesList::unmarshal(void* _ob_v, OB::InputStreamImpl* _ob_in) const
{
    ::AddressesList& _ob_seq = *(::AddressesList*)_ob_v;
    ::CORBA::ULong _ob_len0 = _ob_in -> read_ulong();
    _ob_seq.length(_ob_len0);
    ::DomainData::Address * _ob_buf0 = _ob_seq.get_buffer();
    for(::CORBA::ULong _ob_i0 = 0 ; _ob_i0 < _ob_len0 ; _ob_i0++)
    {
        ::DomainData::Address::_OB_unmarshal(_ob_buf0[_ob_i0], _ob_in);
    }
}

void
operator<<=(::CORBA::Any& any, AddressesList* v)
{
    static const OBInfo_AddressesList info;
    any.replace(_tc_AddressesList, v, true, &info);
}

void
operator<<=(::CORBA::Any& any, const AddressesList& v)
{
    any <<= new AddressesList(v);
}

::CORBA::Boolean
operator>>=(const ::CORBA::Any& any, const AddressesList*& v)
{
    if(any.check_type(_tc_AddressesList))
    {
        if(!any.info())
        {
            OB::InputStream_var _ob_in = any.create_input_stream();
            AddressesList* val = new AddressesList;
            ::CORBA::ULong _ob_len0 = _ob_in -> read_ulong();
            (*val).length(_ob_len0);
            ::DomainData::Address * _ob_buf0 = (*val).get_buffer();
            for(::CORBA::ULong _ob_i0 = 0 ; _ob_i0 < _ob_len0 ; _ob_i0++)
            {
                ::DomainData::Address::_OB_unmarshal(_ob_buf0[_ob_i0], _ob_in);
            }
            (::CORBA::Any&)any <<= val;
        }

        v = (AddressesList*)any.value();
        return true;
    }
    else
        return false;
}

//
// IDL:IServerServer:1.0
//
const char* IServerServer::ids_[] =
{
    "IDL:IServerServer:1.0",
    0
};

void
OBDuplicate(IServerServer_ptr p)
{
    if(p)
        p -> _add_ref();
}

void
OBRelease(IServerServer_ptr p)
{
    if(p)
        p -> _remove_ref();
}

IServerServer_ptr
IServerServer::_narrow(::CORBA::Object_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        IServerServer_ptr v = 
            dynamic_cast< IServerServer_ptr >(p);
        if(v)
            return _duplicate(v);

        if(p -> _is_a(ids_[0]))
        {
            OBProxy_IServerServer* val = new OBProxy_IServerServer;
            val -> _OB_copyFrom(p);
            return val;
        }
    }

    return _nil();
}

IServerServer_ptr
IServerServer::_narrow(::CORBA::AbstractBase_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        IServerServer_ptr v =
            dynamic_cast< IServerServer_ptr >(p);
        if(v)
            return _duplicate(v);

        ::CORBA::Object_var obj = p -> _to_object();
        return _narrow(obj);
    }
    return _nil();
}

IServerServer_ptr
IServerServer::_unchecked_narrow(::CORBA::Object_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        IServerServer_ptr v =
            dynamic_cast< IServerServer_ptr >(p);
        if(v)
            return _duplicate(v);

        OBProxy_IServerServer* val = new OBProxy_IServerServer;
        val -> _OB_copyFrom(p);
        return val;
    }

    return _nil();
}

IServerServer_ptr
IServerServer::_unchecked_narrow(::CORBA::AbstractBase_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        ::CORBA::Object_var obj = p -> _to_object();
        return _unchecked_narrow(obj);
    }
    return _nil();
}

const char**
IServerServer::_OB_staticIds()
{
    return ids_;
}

void
OBMarshal(IServerServer_ptr _ob_v, OB::OutputStreamImpl* _ob_out)
{
    _ob_out -> write_Object(_ob_v);
}

void
OBUnmarshal(IServerServer_ptr& _ob_v, OB::InputStreamImpl* _ob_in)
{
    IServerServer_var old = _ob_v;
    ::CORBA::Object_var p = _ob_in -> read_Object();

    if(!::CORBA::is_nil(p))
    {
        OBProxy_IServerServer* _ob_obj = new OBProxy_IServerServer;
        _ob_obj -> _OB_copyFrom(p);
        _ob_v = _ob_obj;
    }
    else
        _ob_v = IServerServer::_nil();
}

void
operator<<=(::CORBA::Any& any, IServerServer_ptr* v)
{
    any.replace(_tc_IServerServer, (::CORBA::Object_ptr)*v, true);
}

void
operator<<=(::CORBA::Any& any, IServerServer_ptr v)
{
    IServerServer_ptr val = IServerServer::_duplicate(v);
    any <<= &val;
}

::CORBA::Boolean
operator>>=(const ::CORBA::Any& any, IServerServer_ptr& v)
{
    if(any.check_type(_tc_IServerServer))
    {
        ::CORBA::Object_ptr val = (::CORBA::Object_ptr)any.value();

        if(!::CORBA::is_nil(val))
        {
            if(!(v = dynamic_cast< IServerServer_ptr >(val)))
            {
                OBProxy_IServerServer* obj = new OBProxy_IServerServer;
                obj -> _OB_copyFrom(val);
                v = obj;
                (::CORBA::Any&)any <<= &v;
            }
        }
        else
            v = IServerServer::_nil();

        return true;
    }
    else
        return false;
}

//
// IDL:IServerServer:1.0
//
OB::MarshalStubImpl_ptr
OBProxy_IServerServer::_OB_createMarshalStubImpl()
{
    return new OBMarshalStubImpl_IServerServer;
}

const char**
OBProxy_IServerServer::_OB_ids() const
{
    return ::IServerServer::ids_;
}

//
// IDL:IServerServer/Join:1.0
//
::AddressesList*
OBProxy_IServerServer::Join(const ::DomainData::Address& _ob_a0)
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_IServerServer_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_IServerServer_ptr>(_ob_stubImplBase.in());
            return _ob_stubImpl -> Join(_ob_a0);
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:IServerServer/Unjoin:1.0
//
void
OBProxy_IServerServer::Unjoin()
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_IServerServer_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_IServerServer_ptr>(_ob_stubImplBase.in());
            _ob_stubImpl -> Unjoin();
            return;
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:IServerServer/AddServer:1.0
//
void
OBProxy_IServerServer::AddServer(const ::DomainData::Address& _ob_a0)
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_IServerServer_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_IServerServer_ptr>(_ob_stubImplBase.in());
            _ob_stubImpl -> AddServer(_ob_a0);
            return;
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:IServerServer/RemoveServer:1.0
//
void
OBProxy_IServerServer::RemoveServer(const ::DomainData::Address& _ob_a0)
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_IServerServer_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_IServerServer_ptr>(_ob_stubImplBase.in());
            _ob_stubImpl -> RemoveServer(_ob_a0);
            return;
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:IServerServer/PassMessage:1.0
//
void
OBProxy_IServerServer::PassMessage(const ::DomainData::Message& _ob_a0,
                                   const ::DomainData::Address& _ob_a1,
                                   const ::DomainData::Address& _ob_a2)
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_IServerServer_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_IServerServer_ptr>(_ob_stubImplBase.in());
            _ob_stubImpl -> PassMessage(_ob_a0, _ob_a1, _ob_a2);
            return;
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:IServerServer/PassCreatePipeRequest:1.0
//
void
OBProxy_IServerServer::PassCreatePipeRequest(const ::DomainData::Address& _ob_a0,
                                             const ::DomainData::Address& _ob_a1,
                                             const ::DomainData::Address& _ob_a2)
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_IServerServer_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_IServerServer_ptr>(_ob_stubImplBase.in());
            _ob_stubImpl -> PassCreatePipeRequest(_ob_a0, _ob_a1, _ob_a2);
            return;
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:IServerServer/ClientStatusChanged:1.0
//
void
OBProxy_IServerServer::ClientStatusChanged(const ::DomainData::Address& _ob_a0,
                                           const ::DomainData::Enability& _ob_a1)
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_IServerServer_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_IServerServer_ptr>(_ob_stubImplBase.in());
            _ob_stubImpl -> ClientStatusChanged(_ob_a0, _ob_a1);
            return;
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:IServerServer:1.0
//
void
OBDuplicate(OBStubImpl_IServerServer_ptr p)
{
    if(p)
        p -> _OB_incRef();
}

void
OBRelease(OBStubImpl_IServerServer_ptr p)
{
    if(p)
        p -> _OB_decRef();
}

//
// IDL:IServerServer/Join:1.0
//
::AddressesList*
OBMarshalStubImpl_IServerServer::Join(const ::DomainData::Address& _ob_a0)
{
    while(true)
    {
        OB::Downcall_var _ob_down = _OB_createDowncall("Join", true);
        try
        {
            OB::OutputStreamImpl* _ob_out = _OB_preMarshal(_ob_down);
            try
            {
                _ob_a0._OB_marshal(_ob_out);
            }
            catch(const ::CORBA::SystemException& _ob_ex)
            {
                _OB_marshalEx(_ob_down, _ob_ex);
            }
            _OB_postMarshal(_ob_down);
            _OB_request(_ob_down);
            bool _ob_uex;
            OB::InputStreamImpl* _ob_in = _OB_preUnmarshal(_ob_down, _ob_uex);
            if(_ob_uex)
            {
                _OB_postUnmarshal(_ob_down);
            }
            else
            {
                ::AddressesList_var _ob_r;
                try
                {
                    _ob_r = new ::AddressesList;
                    ::CORBA::ULong _ob_len0 = _ob_in -> read_ulong();
                    _ob_r -> length(_ob_len0);
                    ::DomainData::Address * _ob_buf0 = _ob_r -> get_buffer();
                    for(::CORBA::ULong _ob_i0 = 0 ; _ob_i0 < _ob_len0 ; _ob_i0++)
                    {
                        ::DomainData::Address::_OB_unmarshal(_ob_buf0[_ob_i0], _ob_in);
                    }
                }
                catch(const ::CORBA::SystemException& _ob_ex)
                {
                    _OB_unmarshalEx(_ob_down, _ob_ex);
                }
                _OB_postUnmarshal(_ob_down);
                return _ob_r._retn();
            }
        }
        catch(const OB::FailureException& _ob_ex)
        {
            _OB_handleFailureException(_ob_down, _ob_ex);
        }
    }
}

//
// IDL:IServerServer/Unjoin:1.0
//
void
OBMarshalStubImpl_IServerServer::Unjoin()
{
    while(true)
    {
        OB::Downcall_var _ob_down = _OB_createDowncall("Unjoin", true);
        try
        {
            _OB_preMarshal(_ob_down);
            _OB_postMarshal(_ob_down);
            _OB_request(_ob_down);
            _OB_preUnmarshal(_ob_down);
            _OB_postUnmarshal(_ob_down);
            return;
        }
        catch(const OB::FailureException& _ob_ex)
        {
            _OB_handleFailureException(_ob_down, _ob_ex);
        }
    }
}

//
// IDL:IServerServer/AddServer:1.0
//
void
OBMarshalStubImpl_IServerServer::AddServer(const ::DomainData::Address& _ob_a0)
{
    while(true)
    {
        OB::Downcall_var _ob_down = _OB_createDowncall("AddServer", true);
        try
        {
            OB::OutputStreamImpl* _ob_out = _OB_preMarshal(_ob_down);
            try
            {
                _ob_a0._OB_marshal(_ob_out);
            }
            catch(const ::CORBA::SystemException& _ob_ex)
            {
                _OB_marshalEx(_ob_down, _ob_ex);
            }
            _OB_postMarshal(_ob_down);
            _OB_request(_ob_down);
            _OB_preUnmarshal(_ob_down);
            _OB_postUnmarshal(_ob_down);
            return;
        }
        catch(const OB::FailureException& _ob_ex)
        {
            _OB_handleFailureException(_ob_down, _ob_ex);
        }
    }
}

//
// IDL:IServerServer/RemoveServer:1.0
//
void
OBMarshalStubImpl_IServerServer::RemoveServer(const ::DomainData::Address& _ob_a0)
{
    while(true)
    {
        OB::Downcall_var _ob_down = _OB_createDowncall("RemoveServer", true);
        try
        {
            OB::OutputStreamImpl* _ob_out = _OB_preMarshal(_ob_down);
            try
            {
                _ob_a0._OB_marshal(_ob_out);
            }
            catch(const ::CORBA::SystemException& _ob_ex)
            {
                _OB_marshalEx(_ob_down, _ob_ex);
            }
            _OB_postMarshal(_ob_down);
            _OB_request(_ob_down);
            _OB_preUnmarshal(_ob_down);
            _OB_postUnmarshal(_ob_down);
            return;
        }
        catch(const OB::FailureException& _ob_ex)
        {
            _OB_handleFailureException(_ob_down, _ob_ex);
        }
    }
}

//
// IDL:IServerServer/PassMessage:1.0
//
void
OBMarshalStubImpl_IServerServer::PassMessage(const ::DomainData::Message& _ob_a0,
                                             const ::DomainData::Address& _ob_a1,
                                             const ::DomainData::Address& _ob_a2)
{
    while(true)
    {
        OB::Downcall_var _ob_down = _OB_createDowncall("PassMessage", true);
        try
        {
            OB::OutputStreamImpl* _ob_out = _OB_preMarshal(_ob_down);
            try
            {
                _ob_a0._OB_marshal(_ob_out);
                _ob_a1._OB_marshal(_ob_out);
                _ob_a2._OB_marshal(_ob_out);
            }
            catch(const ::CORBA::SystemException& _ob_ex)
            {
                _OB_marshalEx(_ob_down, _ob_ex);
            }
            _OB_postMarshal(_ob_down);
            _OB_request(_ob_down);
            _OB_preUnmarshal(_ob_down);
            _OB_postUnmarshal(_ob_down);
            return;
        }
        catch(const OB::FailureException& _ob_ex)
        {
            _OB_handleFailureException(_ob_down, _ob_ex);
        }
    }
}

//
// IDL:IServerServer/PassCreatePipeRequest:1.0
//
void
OBMarshalStubImpl_IServerServer::PassCreatePipeRequest(const ::DomainData::Address& _ob_a0,
                                                       const ::DomainData::Address& _ob_a1,
                                                       const ::DomainData::Address& _ob_a2)
{
    while(true)
    {
        OB::Downcall_var _ob_down = _OB_createDowncall("PassCreatePipeRequest", true);
        try
        {
            OB::OutputStreamImpl* _ob_out = _OB_preMarshal(_ob_down);
            try
            {
                _ob_a0._OB_marshal(_ob_out);
                _ob_a1._OB_marshal(_ob_out);
                _ob_a2._OB_marshal(_ob_out);
            }
            catch(const ::CORBA::SystemException& _ob_ex)
            {
                _OB_marshalEx(_ob_down, _ob_ex);
            }
            _OB_postMarshal(_ob_down);
            _OB_request(_ob_down);
            _OB_preUnmarshal(_ob_down);
            _OB_postUnmarshal(_ob_down);
            return;
        }
        catch(const OB::FailureException& _ob_ex)
        {
            _OB_handleFailureException(_ob_down, _ob_ex);
        }
    }
}

//
// IDL:IServerServer/ClientStatusChanged:1.0
//
void
OBMarshalStubImpl_IServerServer::ClientStatusChanged(const ::DomainData::Address& _ob_a0,
                                                     const ::DomainData::Enability& _ob_a1)
{
    while(true)
    {
        OB::Downcall_var _ob_down = _OB_createDowncall("ClientStatusChanged", true);
        try
        {
            OB::OutputStreamImpl* _ob_out = _OB_preMarshal(_ob_down);
            try
            {
                _ob_a0._OB_marshal(_ob_out);
                _ob_a1._OB_marshal(_ob_out);
            }
            catch(const ::CORBA::SystemException& _ob_ex)
            {
                _OB_marshalEx(_ob_down, _ob_ex);
            }
            _OB_postMarshal(_ob_down);
            _OB_request(_ob_down);
            _OB_preUnmarshal(_ob_down);
            _OB_postUnmarshal(_ob_down);
            return;
        }
        catch(const OB::FailureException& _ob_ex)
        {
            _OB_handleFailureException(_ob_down, _ob_ex);
        }
    }
}
