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
#include <ClientInterfaces.h>

#ifndef OB_INTEGER_VERSION
#   error No ORBacus version defined! Is <OB/CORBA.h> included?
#endif

#ifndef OB_NO_VERSION_CHECK
#   if (OB_INTEGER_VERSION != 4030300L)
#       error ORBacus version mismatch!
#   endif
#endif

namespace DomainData
{

::OB::TypeCodeConst _tc_Address(
"010101000f0000006400000001fb59001b00000049444c3a446f6d61696e446174612f4164647"
"26573733a312e30000008000000416464726573730002000000050000006e616d650000000012"
"000000000000000d0000006c6f63616c697a6174696f6e000001051200000000000000"
);

::OB::TypeCodeConst _tc_Message(
"010101000f0000004800000001fb59001b00000049444c3a446f6d61696e446174612f4d65737"
"36167653a312e300000080000004d657373616765000100000008000000636f6e74656e740012"
"00000000000000"
);

::OB::TypeCodeConst _tc_File(
"010101000f0000004400000001fb59001800000049444c3a446f6d61696e446174612f46696c6"
"53a312e30000500000046696c6500657373010000000500000070617468006f6e741200000000"
"000000"
);

::OB::TypeCodeConst _tc_Mode(
"01010100110000004700000001fb59001800000049444c3a446f6d61696e446174612f4d6f646"
"53a312e3000050000004d6f646500657373020000000700000070617373697600740700000061"
"637469766500"
);

::OB::TypeCodeConst _tc_Enability(
"010101000f000000a700000001fb59001d00000049444c3a446f6d61696e446174612f456e616"
"2696c6974793a312e30006f64650a000000456e6162696c697479007373020000000700000073"
"7461747573000008000000060000006d6f64655f006f6e1100000047000000010000001800000"
"049444c3a446f6d61696e446174612f4d6f64653a312e3000050000004d6f646500fb59000200"
"00000700000070617373697600000700000061637469766500"
);

::OB::TypeCodeConst _tc_User(
"010101000f0000005400000001fb59001800000049444c3a446f6d61696e446174612f5573657"
"23a312e300005000000557365720000000002000000050000006e616d65000000001200000000"
"000000070000006e756d626572000003000000"
);

} // End of namespace DomainData

namespace ClientInterfaces
{

::OB::TypeCodeConst _tc_IClientServer(
"010101000e0000004200000001fb59002700000049444c3a436c69656e74496e7465726661636"
"5732f49436c69656e745365727665723a312e3000000e00000049436c69656e74536572766572"
"00"
);

::OB::TypeCodeConst _tc_IClientClient(
"010101000e0000004200000001fb59002700000049444c3a436c69656e74496e7465726661636"
"5732f49436c69656e74436c69656e743a312e3000000e00000049436c69656e74436c69656e74"
"00"
);

} // End of namespace ClientInterfaces

//
// IDL:DomainData/Address:1.0
//
DomainData::Address::Address(const Address& _ob_a)
    : name(_ob_a.name),
      localization(_ob_a.localization)
{
}

DomainData::Address&
DomainData::Address::operator=(const Address& _ob_a)
{
    if(this != &_ob_a)
    {
        name = _ob_a.name;
        localization = _ob_a.localization;
    }
    return *this;
}

void
DomainData::Address::_OB_marshal(OB::OutputStreamImpl* _ob_out) const
{
    _ob_out -> write_string(name);
    _ob_out -> write_string(localization);
}

void
DomainData::Address::_OB_unmarshal(Address& _ob_v, OB::InputStreamImpl* _ob_in)
{
    _ob_v.name = _ob_in -> read_string();
    _ob_v.localization = _ob_in -> read_string();
}

void
operator<<=(::CORBA::Any& any, DomainData::Address* v)
{
    static const OB::Info< DomainData::Address > info;
    any.replace(DomainData::_tc_Address, v, true, &info);
}

void
operator<<=(::CORBA::Any& any, const DomainData::Address& v)
{
    any <<= new DomainData::Address(v);
}

::CORBA::Boolean
operator>>=(const ::CORBA::Any& any, const DomainData::Address*& v)
{
    if(any.check_type(DomainData::_tc_Address))
    {
        if(!any.info())
        {
            OB::InputStream_var _ob_in = any.create_input_stream();
            DomainData::Address* val = new DomainData::Address;
            DomainData::Address::_OB_unmarshal(*val, _ob_in);
            (::CORBA::Any&)any <<= val;
        }

        v = (DomainData::Address*)any.value();
        return true;
    }
    else
        return false;
}

//
// IDL:DomainData/Message:1.0
//
DomainData::Message::Message(const Message& _ob_a)
    : content(_ob_a.content)
{
}

DomainData::Message&
DomainData::Message::operator=(const Message& _ob_a)
{
    if(this != &_ob_a)
    {
        content = _ob_a.content;
    }
    return *this;
}

void
DomainData::Message::_OB_marshal(OB::OutputStreamImpl* _ob_out) const
{
    _ob_out -> write_string(content);
}

void
DomainData::Message::_OB_unmarshal(Message& _ob_v, OB::InputStreamImpl* _ob_in)
{
    _ob_v.content = _ob_in -> read_string();
}

void
operator<<=(::CORBA::Any& any, DomainData::Message* v)
{
    static const OB::Info< DomainData::Message > info;
    any.replace(DomainData::_tc_Message, v, true, &info);
}

void
operator<<=(::CORBA::Any& any, const DomainData::Message& v)
{
    any <<= new DomainData::Message(v);
}

::CORBA::Boolean
operator>>=(const ::CORBA::Any& any, const DomainData::Message*& v)
{
    if(any.check_type(DomainData::_tc_Message))
    {
        if(!any.info())
        {
            OB::InputStream_var _ob_in = any.create_input_stream();
            DomainData::Message* val = new DomainData::Message;
            DomainData::Message::_OB_unmarshal(*val, _ob_in);
            (::CORBA::Any&)any <<= val;
        }

        v = (DomainData::Message*)any.value();
        return true;
    }
    else
        return false;
}

//
// IDL:DomainData/File:1.0
//
DomainData::File::File(const File& _ob_a)
    : path(_ob_a.path)
{
}

DomainData::File&
DomainData::File::operator=(const File& _ob_a)
{
    if(this != &_ob_a)
    {
        path = _ob_a.path;
    }
    return *this;
}

void
DomainData::File::_OB_marshal(OB::OutputStreamImpl* _ob_out) const
{
    _ob_out -> write_string(path);
}

void
DomainData::File::_OB_unmarshal(File& _ob_v, OB::InputStreamImpl* _ob_in)
{
    _ob_v.path = _ob_in -> read_string();
}

void
operator<<=(::CORBA::Any& any, DomainData::File* v)
{
    static const OB::Info< DomainData::File > info;
    any.replace(DomainData::_tc_File, v, true, &info);
}

void
operator<<=(::CORBA::Any& any, const DomainData::File& v)
{
    any <<= new DomainData::File(v);
}

::CORBA::Boolean
operator>>=(const ::CORBA::Any& any, const DomainData::File*& v)
{
    if(any.check_type(DomainData::_tc_File))
    {
        if(!any.info())
        {
            OB::InputStream_var _ob_in = any.create_input_stream();
            DomainData::File* val = new DomainData::File;
            DomainData::File::_OB_unmarshal(*val, _ob_in);
            (::CORBA::Any&)any <<= val;
        }

        v = (DomainData::File*)any.value();
        return true;
    }
    else
        return false;
}

//
// IDL:DomainData/Mode:1.0
//
void
operator<<=(::CORBA::Any& any, DomainData::Mode v)
{
    any.replace(DomainData::_tc_Mode, new ::CORBA::ULong((::CORBA::ULong)v), true);
}

::CORBA::Boolean
operator>>=(const ::CORBA::Any& any, DomainData::Mode& v)
{
    if(any.check_type(DomainData::_tc_Mode))
    {
        v = (DomainData::Mode)(*(::CORBA::ULong*)any.value());
        return true;
    }
    else
        return false;
}

//
// IDL:DomainData/Enability:1.0
//
void
DomainData::Enability::_OB_marshal(OB::OutputStreamImpl* _ob_out) const
{
    _ob_out -> write_boolean(status);
    _ob_out -> write_ulong((::CORBA::ULong)mode_);
}

void
DomainData::Enability::_OB_unmarshal(Enability& _ob_v, OB::InputStreamImpl* _ob_in)
{
    _ob_v.status = _ob_in -> read_boolean();
    _ob_v.mode_ = (Mode)_ob_in -> read_ulong();
}

void
operator<<=(::CORBA::Any& any, DomainData::Enability* v)
{
    static const OB::Info< DomainData::Enability > info;
    any.replace(DomainData::_tc_Enability, v, true, &info);
}

void
operator<<=(::CORBA::Any& any, const DomainData::Enability& v)
{
    any <<= new DomainData::Enability(v);
}

::CORBA::Boolean
operator>>=(const ::CORBA::Any& any, const DomainData::Enability*& v)
{
    if(any.check_type(DomainData::_tc_Enability))
    {
        if(!any.info())
        {
            OB::InputStream_var _ob_in = any.create_input_stream();
            DomainData::Enability* val = new DomainData::Enability;
            DomainData::Enability::_OB_unmarshal(*val, _ob_in);
            (::CORBA::Any&)any <<= val;
        }

        v = (DomainData::Enability*)any.value();
        return true;
    }
    else
        return false;
}

//
// IDL:DomainData/User:1.0
//
#ifdef OB_CLEAR_MEM
DomainData::User::User()
{
    memset(&number, 0, sizeof(number));
}
#endif

DomainData::User::User(const User& _ob_a)
    : name(_ob_a.name),
      number(_ob_a.number)
{
}

DomainData::User&
DomainData::User::operator=(const User& _ob_a)
{
    if(this != &_ob_a)
    {
        name = _ob_a.name;
        number = _ob_a.number;
    }
    return *this;
}

void
DomainData::User::_OB_marshal(OB::OutputStreamImpl* _ob_out) const
{
    _ob_out -> write_string(name);
    _ob_out -> write_long(number);
}

void
DomainData::User::_OB_unmarshal(User& _ob_v, OB::InputStreamImpl* _ob_in)
{
    _ob_v.name = _ob_in -> read_string();
    _ob_v.number = _ob_in -> read_long();
}

void
operator<<=(::CORBA::Any& any, DomainData::User* v)
{
    static const OB::Info< DomainData::User > info;
    any.replace(DomainData::_tc_User, v, true, &info);
}

void
operator<<=(::CORBA::Any& any, const DomainData::User& v)
{
    any <<= new DomainData::User(v);
}

::CORBA::Boolean
operator>>=(const ::CORBA::Any& any, const DomainData::User*& v)
{
    if(any.check_type(DomainData::_tc_User))
    {
        if(!any.info())
        {
            OB::InputStream_var _ob_in = any.create_input_stream();
            DomainData::User* val = new DomainData::User;
            DomainData::User::_OB_unmarshal(*val, _ob_in);
            (::CORBA::Any&)any <<= val;
        }

        v = (DomainData::User*)any.value();
        return true;
    }
    else
        return false;
}

//
// IDL:ClientInterfaces/IClientServer:1.0
//
const char* ClientInterfaces::IClientServer::ids_[] =
{
    "IDL:ClientInterfaces/IClientServer:1.0",
    0
};

void
OBDuplicate(ClientInterfaces::IClientServer_ptr p)
{
    if(p)
        p -> _add_ref();
}

void
OBRelease(ClientInterfaces::IClientServer_ptr p)
{
    if(p)
        p -> _remove_ref();
}

ClientInterfaces::IClientServer_ptr
ClientInterfaces::IClientServer::_narrow(::CORBA::Object_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        IClientServer_ptr v = 
            dynamic_cast< IClientServer_ptr >(p);
        if(v)
            return _duplicate(v);

        if(p -> _is_a(ids_[0]))
        {
            OBProxy_ClientInterfaces::IClientServer* val = new OBProxy_ClientInterfaces::IClientServer;
            val -> _OB_copyFrom(p);
            return val;
        }
    }

    return _nil();
}

ClientInterfaces::IClientServer_ptr
ClientInterfaces::IClientServer::_narrow(::CORBA::AbstractBase_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        IClientServer_ptr v =
            dynamic_cast< IClientServer_ptr >(p);
        if(v)
            return _duplicate(v);

        ::CORBA::Object_var obj = p -> _to_object();
        return _narrow(obj);
    }
    return _nil();
}

ClientInterfaces::IClientServer_ptr
ClientInterfaces::IClientServer::_unchecked_narrow(::CORBA::Object_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        IClientServer_ptr v =
            dynamic_cast< IClientServer_ptr >(p);
        if(v)
            return _duplicate(v);

        OBProxy_ClientInterfaces::IClientServer* val = new OBProxy_ClientInterfaces::IClientServer;
        val -> _OB_copyFrom(p);
        return val;
    }

    return _nil();
}

ClientInterfaces::IClientServer_ptr
ClientInterfaces::IClientServer::_unchecked_narrow(::CORBA::AbstractBase_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        ::CORBA::Object_var obj = p -> _to_object();
        return _unchecked_narrow(obj);
    }
    return _nil();
}

const char**
ClientInterfaces::IClientServer::_OB_staticIds()
{
    return ids_;
}

void
OBMarshal(ClientInterfaces::IClientServer_ptr _ob_v, OB::OutputStreamImpl* _ob_out)
{
    _ob_out -> write_Object(_ob_v);
}

void
OBUnmarshal(ClientInterfaces::IClientServer_ptr& _ob_v, OB::InputStreamImpl* _ob_in)
{
    ClientInterfaces::IClientServer_var old = _ob_v;
    ::CORBA::Object_var p = _ob_in -> read_Object();

    if(!::CORBA::is_nil(p))
    {
        OBProxy_ClientInterfaces::IClientServer* _ob_obj = new OBProxy_ClientInterfaces::IClientServer;
        _ob_obj -> _OB_copyFrom(p);
        _ob_v = _ob_obj;
    }
    else
        _ob_v = ClientInterfaces::IClientServer::_nil();
}

void
operator<<=(::CORBA::Any& any, ClientInterfaces::IClientServer_ptr* v)
{
    any.replace(ClientInterfaces::_tc_IClientServer, (::CORBA::Object_ptr)*v, true);
}

void
operator<<=(::CORBA::Any& any, ClientInterfaces::IClientServer_ptr v)
{
    ClientInterfaces::IClientServer_ptr val = ClientInterfaces::IClientServer::_duplicate(v);
    any <<= &val;
}

::CORBA::Boolean
operator>>=(const ::CORBA::Any& any, ClientInterfaces::IClientServer_ptr& v)
{
    if(any.check_type(ClientInterfaces::_tc_IClientServer))
    {
        ::CORBA::Object_ptr val = (::CORBA::Object_ptr)any.value();

        if(!::CORBA::is_nil(val))
        {
            if(!(v = dynamic_cast< ClientInterfaces::IClientServer_ptr >(val)))
            {
                OBProxy_ClientInterfaces::IClientServer* obj = new OBProxy_ClientInterfaces::IClientServer;
                obj -> _OB_copyFrom(val);
                v = obj;
                (::CORBA::Any&)any <<= &v;
            }
        }
        else
            v = ClientInterfaces::IClientServer::_nil();

        return true;
    }
    else
        return false;
}

//
// IDL:ClientInterfaces/IClientClient:1.0
//
const char* ClientInterfaces::IClientClient::ids_[] =
{
    "IDL:ClientInterfaces/IClientClient:1.0",
    0
};

void
OBDuplicate(ClientInterfaces::IClientClient_ptr p)
{
    if(p)
        p -> _add_ref();
}

void
OBRelease(ClientInterfaces::IClientClient_ptr p)
{
    if(p)
        p -> _remove_ref();
}

ClientInterfaces::IClientClient_ptr
ClientInterfaces::IClientClient::_narrow(::CORBA::Object_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        IClientClient_ptr v = 
            dynamic_cast< IClientClient_ptr >(p);
        if(v)
            return _duplicate(v);

        if(p -> _is_a(ids_[0]))
        {
            OBProxy_ClientInterfaces::IClientClient* val = new OBProxy_ClientInterfaces::IClientClient;
            val -> _OB_copyFrom(p);
            return val;
        }
    }

    return _nil();
}

ClientInterfaces::IClientClient_ptr
ClientInterfaces::IClientClient::_narrow(::CORBA::AbstractBase_ptr p)
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

ClientInterfaces::IClientClient_ptr
ClientInterfaces::IClientClient::_unchecked_narrow(::CORBA::Object_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        IClientClient_ptr v =
            dynamic_cast< IClientClient_ptr >(p);
        if(v)
            return _duplicate(v);

        OBProxy_ClientInterfaces::IClientClient* val = new OBProxy_ClientInterfaces::IClientClient;
        val -> _OB_copyFrom(p);
        return val;
    }

    return _nil();
}

ClientInterfaces::IClientClient_ptr
ClientInterfaces::IClientClient::_unchecked_narrow(::CORBA::AbstractBase_ptr p)
{
    if(!::CORBA::is_nil(p))
    {
        ::CORBA::Object_var obj = p -> _to_object();
        return _unchecked_narrow(obj);
    }
    return _nil();
}

const char**
ClientInterfaces::IClientClient::_OB_staticIds()
{
    return ids_;
}

void
OBMarshal(ClientInterfaces::IClientClient_ptr _ob_v, OB::OutputStreamImpl* _ob_out)
{
    _ob_out -> write_Object(_ob_v);
}

void
OBUnmarshal(ClientInterfaces::IClientClient_ptr& _ob_v, OB::InputStreamImpl* _ob_in)
{
    ClientInterfaces::IClientClient_var old = _ob_v;
    ::CORBA::Object_var p = _ob_in -> read_Object();

    if(!::CORBA::is_nil(p))
    {
        OBProxy_ClientInterfaces::IClientClient* _ob_obj = new OBProxy_ClientInterfaces::IClientClient;
        _ob_obj -> _OB_copyFrom(p);
        _ob_v = _ob_obj;
    }
    else
        _ob_v = ClientInterfaces::IClientClient::_nil();
}

void
operator<<=(::CORBA::Any& any, ClientInterfaces::IClientClient_ptr* v)
{
    any.replace(ClientInterfaces::_tc_IClientClient, (::CORBA::Object_ptr)*v, true);
}

void
operator<<=(::CORBA::Any& any, ClientInterfaces::IClientClient_ptr v)
{
    ClientInterfaces::IClientClient_ptr val = ClientInterfaces::IClientClient::_duplicate(v);
    any <<= &val;
}

::CORBA::Boolean
operator>>=(const ::CORBA::Any& any, ClientInterfaces::IClientClient_ptr& v)
{
    if(any.check_type(ClientInterfaces::_tc_IClientClient))
    {
        ::CORBA::Object_ptr val = (::CORBA::Object_ptr)any.value();

        if(!::CORBA::is_nil(val))
        {
            if(!(v = dynamic_cast< ClientInterfaces::IClientClient_ptr >(val)))
            {
                OBProxy_ClientInterfaces::IClientClient* obj = new OBProxy_ClientInterfaces::IClientClient;
                obj -> _OB_copyFrom(val);
                v = obj;
                (::CORBA::Any&)any <<= &v;
            }
        }
        else
            v = ClientInterfaces::IClientClient::_nil();

        return true;
    }
    else
        return false;
}

//
// IDL:ClientInterfaces/IClientServer:1.0
//
OB::MarshalStubImpl_ptr
OBProxy_ClientInterfaces::IClientServer::_OB_createMarshalStubImpl()
{
    return new OBMarshalStubImpl_ClientInterfaces::IClientServer;
}

const char**
OBProxy_ClientInterfaces::IClientServer::_OB_ids() const
{
    return ::ClientInterfaces::IClientServer::ids_;
}

//
// IDL:ClientInterfaces/IClientServer/ReceiveMessage:1.0
//
void
OBProxy_ClientInterfaces::IClientServer::ReceiveMessage(const ::DomainData::Address& _ob_a0,
                                                        const ::DomainData::Message& _ob_a1)
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_ClientInterfaces::IClientServer_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_ClientInterfaces::IClientServer_ptr>(_ob_stubImplBase.in());
            _ob_stubImpl -> ReceiveMessage(_ob_a0, _ob_a1);
            return;
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:ClientInterfaces/IClientServer/ChangeServer:1.0
//
void
OBProxy_ClientInterfaces::IClientServer::ChangeServer(const ::DomainData::Address& _ob_a0)
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_ClientInterfaces::IClientServer_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_ClientInterfaces::IClientServer_ptr>(_ob_stubImplBase.in());
            _ob_stubImpl -> ChangeServer(_ob_a0);
            return;
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:ClientInterfaces/IClientServer/CreatePipeRequest:1.0
//
::CORBA::Boolean
OBProxy_ClientInterfaces::IClientServer::CreatePipeRequest(const ::DomainData::Address& _ob_a0,
                                                           const ::DomainData::Address& _ob_a1)
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_ClientInterfaces::IClientServer_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_ClientInterfaces::IClientServer_ptr>(_ob_stubImplBase.in());
            return _ob_stubImpl -> CreatePipeRequest(_ob_a0, _ob_a1);
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:ClientInterfaces/IClientClient:1.0
//
OB::MarshalStubImpl_ptr
OBProxy_ClientInterfaces::IClientClient::_OB_createMarshalStubImpl()
{
    return new OBMarshalStubImpl_ClientInterfaces::IClientClient;
}

const char**
OBProxy_ClientInterfaces::IClientClient::_OB_ids() const
{
    return ::ClientInterfaces::IClientClient::ids_;
}

//
// IDL:ClientInterfaces/IClientClient/SendFile:1.0
//
void
OBProxy_ClientInterfaces::IClientClient::SendFile(const ::DomainData::File& _ob_a0,
                                                  const ::DomainData::Address& _ob_a1)
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_ClientInterfaces::IClientClient_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_ClientInterfaces::IClientClient_ptr>(_ob_stubImplBase.in());
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
// IDL:ClientInterfaces/IClientClient/CreatePipe:1.0
//
void
OBProxy_ClientInterfaces::IClientClient::CreatePipe()
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_ClientInterfaces::IClientClient_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_ClientInterfaces::IClientClient_ptr>(_ob_stubImplBase.in());
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
// IDL:ClientInterfaces/IClientClient/GetFile:1.0
//
::DomainData::File*
OBProxy_ClientInterfaces::IClientClient::GetFile(const ::DomainData::Address& _ob_a0)
{
    ::CORBA::ULong _ob_retry = 0, _ob_hop = 0;
    while(true)
    {
        try
        {
            OB::StubImplBase_var _ob_stubImplBase = _OB_getStubImpl();
            OBStubImpl_ClientInterfaces::IClientClient_ptr _ob_stubImpl = 
                dynamic_cast< OBStubImpl_ClientInterfaces::IClientClient_ptr>(_ob_stubImplBase.in());
            return _ob_stubImpl -> GetFile(_ob_a0);
        }
        catch(const OB::ExceptionBase& _ob_ex)
        {
            _OB_handleException(_ob_ex, _ob_retry, _ob_hop);
        }
    }
}

//
// IDL:ClientInterfaces/IClientServer:1.0
//
void
OBDuplicate(OBStubImpl_ClientInterfaces::IClientServer_ptr p)
{
    if(p)
        p -> _OB_incRef();
}

void
OBRelease(OBStubImpl_ClientInterfaces::IClientServer_ptr p)
{
    if(p)
        p -> _OB_decRef();
}

//
// IDL:ClientInterfaces/IClientClient:1.0
//
void
OBDuplicate(OBStubImpl_ClientInterfaces::IClientClient_ptr p)
{
    if(p)
        p -> _OB_incRef();
}

void
OBRelease(OBStubImpl_ClientInterfaces::IClientClient_ptr p)
{
    if(p)
        p -> _OB_decRef();
}

//
// IDL:ClientInterfaces/IClientServer/ReceiveMessage:1.0
//
void
OBMarshalStubImpl_ClientInterfaces::IClientServer::ReceiveMessage(const ::DomainData::Address& _ob_a0,
                                                                  const ::DomainData::Message& _ob_a1)
{
    while(true)
    {
        OB::Downcall_var _ob_down = _OB_createDowncall("ReceiveMessage", true);
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
// IDL:ClientInterfaces/IClientServer/ChangeServer:1.0
//
void
OBMarshalStubImpl_ClientInterfaces::IClientServer::ChangeServer(const ::DomainData::Address& _ob_a0)
{
    while(true)
    {
        OB::Downcall_var _ob_down = _OB_createDowncall("ChangeServer", true);
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
// IDL:ClientInterfaces/IClientServer/CreatePipeRequest:1.0
//
::CORBA::Boolean
OBMarshalStubImpl_ClientInterfaces::IClientServer::CreatePipeRequest(const ::DomainData::Address& _ob_a0,
                                                                     const ::DomainData::Address& _ob_a1)
{
    while(true)
    {
        OB::Downcall_var _ob_down = _OB_createDowncall("CreatePipeRequest", true);
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
            bool _ob_uex;
            OB::InputStreamImpl* _ob_in = _OB_preUnmarshal(_ob_down, _ob_uex);
            if(_ob_uex)
            {
                _OB_postUnmarshal(_ob_down);
            }
            else
            {
                ::CORBA::Boolean _ob_r;
                try
                {
                    _ob_r = _ob_in -> read_boolean();
                }
                catch(const ::CORBA::SystemException& _ob_ex)
                {
                    _OB_unmarshalEx(_ob_down, _ob_ex);
                }
                _OB_postUnmarshal(_ob_down);
                return _ob_r;
            }
        }
        catch(const OB::FailureException& _ob_ex)
        {
            _OB_handleFailureException(_ob_down, _ob_ex);
        }
    }
}

//
// IDL:ClientInterfaces/IClientClient/SendFile:1.0
//
void
OBMarshalStubImpl_ClientInterfaces::IClientClient::SendFile(const ::DomainData::File& _ob_a0,
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
// IDL:ClientInterfaces/IClientClient/CreatePipe:1.0
//
void
OBMarshalStubImpl_ClientInterfaces::IClientClient::CreatePipe()
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
// IDL:ClientInterfaces/IClientClient/GetFile:1.0
//
::DomainData::File*
OBMarshalStubImpl_ClientInterfaces::IClientClient::GetFile(const ::DomainData::Address& _ob_a0)
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