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
#include <DomainData.h>

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

::OB::TypeCodeConst _tc_User(
"01302e330f0000005400000001fb59001800000049444c3a446f6d61696e446174612f5573657"
"23a312e300005000000557365720044656602000000050000006e616d6500fb59001200000000"
"000000070000006e756d626572000003000000"
);

::OB::TypeCodeConst _tc_Address(
"01302e330f0000006400000001fb59001b00000049444c3a446f6d61696e446174612f4164647"
"26573733a312e30000008000000416464726573730002000000050000006e616d650000000012"
"000000000000000d0000006c6f63616c697a6174696f6e000001051200000000000000"
);

::OB::TypeCodeConst _tc_Message(
"01302e330f0000004800000001fb59001b00000049444c3a446f6d61696e446174612f4d65737"
"36167653a312e300000080000004d657373616765000100000008000000636f6e74656e740012"
"00000000000000"
);

::OB::TypeCodeConst _tc_File(
"01302e330f0000004400000001fb59001800000049444c3a446f6d61696e446174612f46696c6"
"53a312e30000500000046696c6500657373010000000500000070617468006f6e741200000000"
"000000"
);

::OB::TypeCodeConst _tc_Mode(
"01302e33110000004700000001fb59001800000049444c3a446f6d61696e446174612f4d6f646"
"53a312e3000050000004d6f646500657373020000000700000070617373697600740700000061"
"637469766500"
);

::OB::TypeCodeConst _tc_Enability(
"01302e330f000000a700000001fb59001d00000049444c3a446f6d61696e446174612f456e616"
"2696c6974793a312e30006f64650a000000456e6162696c697479007373020000000700000073"
"7461747573000008000000060000006d6f64655f006f6e1100000047000000010000001800000"
"049444c3a446f6d61696e446174612f4d6f64653a312e3000050000004d6f646500fb59000200"
"00000700000070617373697600000700000061637469766500"
);

} // End of namespace DomainData

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
