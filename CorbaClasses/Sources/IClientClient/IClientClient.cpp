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
#include <IClientClient.h>

#ifndef OB_INTEGER_VERSION
#   error No ORBacus version defined! Is <OB/CORBA.h> included?
#endif

#ifndef OB_NO_VERSION_CHECK
#   if (OB_INTEGER_VERSION != 4030300L)
#       error ORBacus version mismatch!
#   endif
#endif

::OB::TypeCodeConst _tc_IClientClient(
"017970650e000000320000000102917c1600000049444c3a49436c69656e74436c69656e743a3"
"12e300063000e00000049436c69656e74436c69656e7400"
);

//
// IDL:IClientClient:1.0
//
const char* IClientClient::ids_[] =
{
    "IDL:IClientClient:1.0",
    0
};

void
OBDuplicate(IClientClient_ptr p)
{
    if(p)
        p -> _add_ref();
}

void
OBRelease(IClientClient_ptr p)
{
    if(p)
        p -> _remove_ref();
}

IClientClient_ptr
IClientClient::_narrow(::CORBA::Object_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        IClientClient_ptr v = 
            dynamic_cast< IClientClient_ptr >(p);
        if(v)
            return _duplicate(v);

        if(p -> _is_a(ids_[0]))
        {
            OBProxy_IClientClient* val = new OBProxy_IClientClient;
            val -> _OB_copyFrom(p);
            return val;
        }
    }

    return _nil();
}

IClientClient_ptr
IClientClient::_narrow(::CORBA::AbstractBase_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        IClientClient_ptr v =
            dynamic_cast< IClientClient_ptr >(p);
        if(v)
            return _duplicate(v);

        ::CORBA::Object_var obj = p -> _to_object();
        return _narrow(obj);
    }
    return _nil();
}

IClientClient_ptr
IClientClient::_unchecked_narrow(::CORBA::Object_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        IClientClient_ptr v =
            dynamic_cast< IClientClient_ptr >(p);
        if(v)
            return _duplicate(v);

        OBProxy_IClientClient* val = new OBProxy_IClientClient;
        val -> _OB_copyFrom(p);
        return val;
    }

    return _nil();
}

IClientClient_ptr
IClientClient::_unchecked_narrow(::CORBA::AbstractBase_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        ::CORBA::Object_var obj = p -> _to_object();
        return _unchecked_narrow(obj);
    }
    return _nil();
}

const char**
IClientClient::_OB_staticIds()
{
    return ids_;
}

void
OBMarshal(IClientClient_ptr _ob_v, OB::OutputStreamImpl* _ob_out)
{
    _ob_out -> write_Object(_ob_v);
}

void
OBUnmarshal(IClientClient_ptr& _ob_v, OB::InputStreamImpl* _ob_in)
{
    IClientClient_var old = _ob_v;
    ::CORBA::Object_var p = _ob_in -> read_Object();

    if(!::CORBA::is_nil(p))
    {
        OBProxy_IClientClient* _ob_obj = new OBProxy_IClientClient;
        _ob_obj -> _OB_copyFrom(p);
        _ob_v = _ob_obj;
    }
    else
        _ob_v = IClientClient::_nil();
}

void
operator<<=(::CORBA::Any& any, IClientClient_ptr* v)
{
    any.replace(_tc_IClientClient, (::CORBA::Object_ptr)*v, true);
}

void
operator<<=(::CORBA::Any& any, IClientClient_ptr v)
{
    IClientClient_ptr val = IClientClient::_duplicate(v);
    any <<= &val;
}

::CORBA::Boolean
operator>>=(const ::CORBA::Any& any, IClientClient_ptr& v)
{
    if(any.check_type(_tc_IClientClient))
    {
        ::CORBA::Object_ptr val = (::CORBA::Object_ptr)any.value();

        if(!::CORBA::is_nil(val))
        {
            if(!(v = dynamic_cast< IClientClient_ptr >(val)))
            {
                OBProxy_IClientClient* obj = new OBProxy_IClientClient;
                obj -> _OB_copyFrom(val);
                v = obj;
                (::CORBA::Any&)any <<= &v;
            }
        }
        else
            v = IClientClient::_nil();

        return true;
    }
    else
        return false;
}

//
// IDL:IClientClient:1.0
//
OB::MarshalStubImpl_ptr
OBProxy_IClientClient::_OB_createMarshalStubImpl()
{
    return new OBMarshalStubImpl_IClientClient;
}

const char**
OBProxy_IClientClient::_OB_ids() const
{
    return ::IClientClient::ids_;
}

//
// IDL:IClientClient/SendFile:1.0
//
void
OBProxy_IClientClient::SendFile(const ::DomainData::File& _ob_a0,
                                const ::DomainData::Address& _ob_a1)
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_IClientClient_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_IClientClient_ptr>(_ob_stubImplBase.in());
            _ob_stubImpl -> SendFile(_ob_a0, _ob_a1);
            return;
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:IClientClient/CreatePipe:1.0
//
void
OBProxy_IClientClient::CreatePipe()
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_IClientClient_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_IClientClient_ptr>(_ob_stubImplBase.in());
            _ob_stubImpl -> CreatePipe();
            return;
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:IClientClient/GetFile:1.0
//
::DomainData::File*
OBProxy_IClientClient::GetFile(const ::DomainData::Address& _ob_a0)
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_IClientClient_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_IClientClient_ptr>(_ob_stubImplBase.in());
            return _ob_stubImpl -> GetFile(_ob_a0);
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:IClientClient:1.0
//
void
OBDuplicate(OBStubImpl_IClientClient_ptr p)
{
    if(p)
        p -> _OB_incRef();
}

void
OBRelease(OBStubImpl_IClientClient_ptr p)
{
    if(p)
        p -> _OB_decRef();
}

//
// IDL:IClientClient/SendFile:1.0
//
void
OBMarshalStubImpl_IClientClient::SendFile(const ::DomainData::File& _ob_a0,
                                          const ::DomainData::Address& _ob_a1)
{
    while(true)
    {
        OB::Downcall_var _ob_down = _OB_createDowncall("SendFile", true);
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

//
// IDL:IClientClient/CreatePipe:1.0
//
void
OBMarshalStubImpl_IClientClient::CreatePipe()
{
    while(true)
    {
        OB::Downcall_var _ob_down = _OB_createDowncall("CreatePipe", true);
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
// IDL:IClientClient/GetFile:1.0
//
::DomainData::File*
OBMarshalStubImpl_IClientClient::GetFile(const ::DomainData::Address& _ob_a0)
{
    while(true)
    {
        OB::Downcall_var _ob_down = _OB_createDowncall("GetFile", true);
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
                ::DomainData::File_var _ob_r;
                try
                {
                    _ob_r = new ::DomainData::File;
                    ::DomainData::File::_OB_unmarshal(_ob_r.inout(), _ob_in);
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