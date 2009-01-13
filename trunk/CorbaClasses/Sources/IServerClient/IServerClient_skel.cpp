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

#include <OB/CORBAServer.h>
#include <IServerClient_skel.h>

#ifndef OB_INTEGER_VERSION
#   error No ORBacus version defined! Is <OB/CORBA.h> included?
#endif

#ifndef OB_NO_VERSION_CHECK
#   if (OB_INTEGER_VERSION != 4030300L)
#       error ORBacus version mismatch!
#   endif
#endif

//
// IDL:IServerClient/Connect:1.0
//
void
POA_IServerClient::_OB_op_Connect(OB::Upcall_ptr _ob_up)
{
    ::DomainData::Address _ob_a0;
    ::DomainData::Mode _ob_a1;
    ::DomainData::User _ob_a2;
    OB::InputStreamImpl* _ob_in = _OB_preUnmarshal(_ob_up);
    ::DomainData::Address::_OB_unmarshal(_ob_a0, _ob_in);
    _ob_a1 = (::DomainData::Mode)_ob_in -> read_ulong();
    ::DomainData::User::_OB_unmarshal(_ob_a2, _ob_in);
    _OB_postUnmarshal(_ob_up);
    ::DomainData::Address_var _ob_r = Connect(_ob_a0, _ob_a1, _ob_a2);
    _OB_postinvoke(_ob_up);
    OB::OutputStreamImpl* _ob_out = _OB_preMarshal(_ob_up);
    _ob_r.in()._OB_marshal(_ob_out);
    _OB_postMarshal(_ob_up);
}

//
// IDL:IServerClient/Disconnect:1.0
//
void
POA_IServerClient::_OB_op_Disconnect(OB::Upcall_ptr _ob_up)
{
    ::DomainData::User _ob_a0;
    OB::InputStreamImpl* _ob_in = _OB_preUnmarshal(_ob_up);
    ::DomainData::User::_OB_unmarshal(_ob_a0, _ob_in);
    _OB_postUnmarshal(_ob_up);
    Disconnect(_ob_a0);
    _OB_postinvoke(_ob_up);
    _OB_preMarshal(_ob_up);
    _OB_postMarshal(_ob_up);
}

//
// IDL:IServerClient/Register:1.0
//
void
POA_IServerClient::_OB_op_Register(OB::Upcall_ptr _ob_up)
{
    ::DomainData::User _ob_a0;
    OB::InputStreamImpl* _ob_in = _OB_preUnmarshal(_ob_up);
    ::DomainData::User::_OB_unmarshal(_ob_a0, _ob_in);
    _OB_postUnmarshal(_ob_up);
    ::DomainData::User_var _ob_r = Register(_ob_a0);
    _OB_postinvoke(_ob_up);
    OB::OutputStreamImpl* _ob_out = _OB_preMarshal(_ob_up);
    _ob_r.in()._OB_marshal(_ob_out);
    _OB_postMarshal(_ob_up);
}

//
// IDL:IServerClient/SendMessage:1.0
//
void
POA_IServerClient::_OB_op_SendMessage(OB::Upcall_ptr _ob_up)
{
    ::DomainData::User _ob_a0;
    ::DomainData::User _ob_a1;
    ::DomainData::Message _ob_a2;
    OB::InputStreamImpl* _ob_in = _OB_preUnmarshal(_ob_up);
    ::DomainData::User::_OB_unmarshal(_ob_a0, _ob_in);
    ::DomainData::User::_OB_unmarshal(_ob_a1, _ob_in);
    ::DomainData::Message::_OB_unmarshal(_ob_a2, _ob_in);
    _OB_postUnmarshal(_ob_up);
    SendMessage(_ob_a0, _ob_a1, _ob_a2);
    _OB_postinvoke(_ob_up);
    _OB_preMarshal(_ob_up);
    _OB_postMarshal(_ob_up);
}

//
// IDL:IServerClient/CheckClientStatus:1.0
//
void
POA_IServerClient::_OB_op_CheckClientStatus(OB::Upcall_ptr _ob_up)
{
    ::DomainData::User _ob_a0;
    OB::InputStreamImpl* _ob_in = _OB_preUnmarshal(_ob_up);
    ::DomainData::User::_OB_unmarshal(_ob_a0, _ob_in);
    _OB_postUnmarshal(_ob_up);
    ::DomainData::Enability _ob_r = CheckClientStatus(_ob_a0);
    _OB_postinvoke(_ob_up);
    OB::OutputStreamImpl* _ob_out = _OB_preMarshal(_ob_up);
    _ob_r._OB_marshal(_ob_out);
    _OB_postMarshal(_ob_up);
}

//
// IDL:IServerClient/GetPipeHolder:1.0
//
void
POA_IServerClient::_OB_op_GetPipeHolder(OB::Upcall_ptr _ob_up)
{
    ::DomainData::User _ob_a0;
    OB::InputStreamImpl* _ob_in = _OB_preUnmarshal(_ob_up);
    ::DomainData::User::_OB_unmarshal(_ob_a0, _ob_in);
    _OB_postUnmarshal(_ob_up);
    ::DomainData::User_var _ob_r = GetPipeHolder(_ob_a0);
    _OB_postinvoke(_ob_up);
    OB::OutputStreamImpl* _ob_out = _OB_preMarshal(_ob_up);
    _ob_r.in()._OB_marshal(_ob_out);
    _OB_postMarshal(_ob_up);
}

//
// IDL:IServerClient/GetUserAddressByName:1.0
//
void
POA_IServerClient::_OB_op_GetUserAddressByName(OB::Upcall_ptr _ob_up)
{
    ::DomainData::User _ob_a0;
    OB::InputStreamImpl* _ob_in = _OB_preUnmarshal(_ob_up);
    ::DomainData::User::_OB_unmarshal(_ob_a0, _ob_in);
    _OB_postUnmarshal(_ob_up);
    ::DomainData::Address_var _ob_r = GetUserAddressByName(_ob_a0);
    _OB_postinvoke(_ob_up);
    OB::OutputStreamImpl* _ob_out = _OB_preMarshal(_ob_up);
    _ob_r.in()._OB_marshal(_ob_out);
    _OB_postMarshal(_ob_up);
}

//
// IDL:IServerClient:1.0
//
::CORBA::Boolean
POA_IServerClient::_is_a(const char* type)
    throw(::CORBA::SystemException)
{
    const char** _ob_ids = IServerClient::_OB_staticIds();
    for(::CORBA::ULong _ob_i = 0; _ob_ids[_ob_i] != 0; ++_ob_i)
        if(strcmp(type, _ob_ids[_ob_i]) == 0)
            return true;

    return false;
}

::CORBA::RepositoryId
POA_IServerClient::_primary_interface(const PortableServer::ObjectId&,
                                      PortableServer::POA_ptr)
{
    return ::CORBA::string_dup(IServerClient::_OB_staticIds()[0]);
}

IServerClient_ptr
POA_IServerClient::_this()
{
    ::CORBA::Object_var obj = _OB_createReference();
    IServerClient_var result = IServerClient::_narrow(obj);
    return result._retn();
}

OB::DirectStubImpl_ptr
POA_IServerClient::_OB_createDirectStubImpl(PortableServer::POA_ptr poa,
                                            const PortableServer::ObjectId& oid)
{
    return new OBDirectStubImpl_IServerClient(poa, oid, this);
}

void
POA_IServerClient::_OB_dispatch(OB::Upcall_ptr _ob_up)
{
    static const char* _ob_names[] =
    {
        "CheckClientStatus",
        "Connect",
        "Disconnect",
        "GetPipeHolder",
        "GetUserAddressByName",
        "Register",
        "SendMessage"
    };
    static const ::CORBA::ULong _ob_numNames = 7;

    switch(_OB_findOperation(_ob_up, _ob_names, _ob_numNames))
    {
    case 0: // CheckClientStatus
        _OB_op_CheckClientStatus(_ob_up);
        return;

    case 1: // Connect
        _OB_op_Connect(_ob_up);
        return;

    case 2: // Disconnect
        _OB_op_Disconnect(_ob_up);
        return;

    case 3: // GetPipeHolder
        _OB_op_GetPipeHolder(_ob_up);
        return;

    case 4: // GetUserAddressByName
        _OB_op_GetUserAddressByName(_ob_up);
        return;

    case 5: // Register
        _OB_op_Register(_ob_up);
        return;

    case 6: // SendMessage
        _OB_op_SendMessage(_ob_up);
        return;
    }

    _OB_dispatchBase(_ob_up);
}

//
// IDL:IServerClient:1.0
//
OBDirectStubImpl_IServerClient::OBDirectStubImpl_IServerClient(
    PortableServer::POA_ptr poa,
    const PortableServer::ObjectId& oid,
    PortableServer::ServantBase* servant)
#ifdef HAVE_VCPLUSPLUS_BUGS
{
    _ob_initialize(poa, oid, servant);
}
#else
    : OB::DirectStubImpl(poa, oid, servant)
{
}
#endif

//
// IDL:IServerClient/Connect:1.0
//
::DomainData::Address*
OBDirectStubImpl_IServerClient::Connect(const ::DomainData::Address& _ob_a0,
                                        ::DomainData::Mode _ob_a1,
                                        const ::DomainData::User& _ob_a2)
{
    OB::InvocationHandler _ob_handler(this, "Connect");
    return dynamic_cast<POA_IServerClient*>(_ob_servant_) -> Connect(_ob_a0, _ob_a1, _ob_a2);
}

//
// IDL:IServerClient/Disconnect:1.0
//
void
OBDirectStubImpl_IServerClient::Disconnect(const ::DomainData::User& _ob_a0)
{
    OB::InvocationHandler _ob_handler(this, "Disconnect");
    dynamic_cast<POA_IServerClient*>(_ob_servant_) -> Disconnect(_ob_a0);
}

//
// IDL:IServerClient/Register:1.0
//
::DomainData::User*
OBDirectStubImpl_IServerClient::Register(const ::DomainData::User& _ob_a0)
{
    OB::InvocationHandler _ob_handler(this, "Register");
    return dynamic_cast<POA_IServerClient*>(_ob_servant_) -> Register(_ob_a0);
}

//
// IDL:IServerClient/SendMessage:1.0
//
void
OBDirectStubImpl_IServerClient::SendMessage(const ::DomainData::User& _ob_a0,
                                            const ::DomainData::User& _ob_a1,
                                            const ::DomainData::Message& _ob_a2)
{
    OB::InvocationHandler _ob_handler(this, "SendMessage");
    dynamic_cast<POA_IServerClient*>(_ob_servant_) -> SendMessage(_ob_a0, _ob_a1, _ob_a2);
}

//
// IDL:IServerClient/CheckClientStatus:1.0
//
::DomainData::Enability
OBDirectStubImpl_IServerClient::CheckClientStatus(const ::DomainData::User& _ob_a0)
{
    OB::InvocationHandler _ob_handler(this, "CheckClientStatus");
    return dynamic_cast<POA_IServerClient*>(_ob_servant_) -> CheckClientStatus(_ob_a0);
}

//
// IDL:IServerClient/GetPipeHolder:1.0
//
::DomainData::User*
OBDirectStubImpl_IServerClient::GetPipeHolder(const ::DomainData::User& _ob_a0)
{
    OB::InvocationHandler _ob_handler(this, "GetPipeHolder");
    return dynamic_cast<POA_IServerClient*>(_ob_servant_) -> GetPipeHolder(_ob_a0);
}

//
// IDL:IServerClient/GetUserAddressByName:1.0
//
::DomainData::Address*
OBDirectStubImpl_IServerClient::GetUserAddressByName(const ::DomainData::User& _ob_a0)
{
    OB::InvocationHandler _ob_handler(this, "GetUserAddressByName");
    return dynamic_cast<POA_IServerClient*>(_ob_servant_) -> GetUserAddressByName(_ob_a0);
}
