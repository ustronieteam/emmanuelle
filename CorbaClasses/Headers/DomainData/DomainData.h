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
/// @brief	Klasa wygenerowana z pliku IDL DomainData.idl
///

#ifndef ___DomainData_h__
#define ___DomainData_h__

#include <OB/CORBA.h>

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

} // End of namespace DomainData

namespace DomainData
{

} // End of namespace DomainData

namespace OBStubImpl_DomainData
{

} // End of namespace OBStubImpl_DomainData

namespace OBStubImpl_DomainData
{

} // End of namespace OBStubImpl_DomainData

//
// IDL:DomainData:1.0
//
namespace DomainData
{

//
// IDL:DomainData/User:1.0
//
struct User;
typedef OB::VarVar< User > User_var;
typedef OB::VarOut< User > User_out;

struct User
{
#ifdef OB_CLEAR_MEM
    User();
#else
    User() { }
#endif
    User(const User&);
    User& operator=(const User&);

    typedef User_var _var_type;

    OB::StrForStruct name;
    ::CORBA::Long number;

    void _OB_marshal(OB::OutputStreamImpl*) const;
    static void _OB_unmarshal(User&, OB::InputStreamImpl*);
};

extern OB::TypeCodeConst _tc_User;

//
// IDL:DomainData/Address:1.0
//
struct Address;
typedef OB::VarVar< Address > Address_var;
typedef OB::VarOut< Address > Address_out;

struct Address
{
    Address() { }
    Address(const Address&);
    Address& operator=(const Address&);

    typedef Address_var _var_type;

    OB::StrForStruct name;
    OB::StrForStruct localization;

    void _OB_marshal(OB::OutputStreamImpl*) const;
    static void _OB_unmarshal(Address&, OB::InputStreamImpl*);
};

extern OB::TypeCodeConst _tc_Address;

//
// IDL:DomainData/Message:1.0
//
struct Message;
typedef OB::VarVar< Message > Message_var;
typedef OB::VarOut< Message > Message_out;

struct Message
{
    Message() { }
    Message(const Message&);
    Message& operator=(const Message&);

    typedef Message_var _var_type;

    OB::StrForStruct content;

    void _OB_marshal(OB::OutputStreamImpl*) const;
    static void _OB_unmarshal(Message&, OB::InputStreamImpl*);
};

extern OB::TypeCodeConst _tc_Message;

//
// IDL:DomainData/Content:1.0
//
class OBUnique_Content { };

typedef OB::FixSeq< ::CORBA::Char, OBUnique_Content > Content;
typedef OB::SeqVar< OB::FixSeq< ::CORBA::Char, OBUnique_Content > > Content_var;
typedef OB::SeqOut< OB::FixSeq< ::CORBA::Char, OBUnique_Content > > Content_out;
extern OB::TypeCodeConst _tc_Content;

struct OBInfo_Content : public OB::ConstructedInfo
{
    OBInfo_Content() { }

    virtual void free(void* p) const
    {
        delete (Content*)p;
    }

    virtual void* dup(const void* p) const
    {
        return new Content(*(const Content*)p);
    }

    virtual void marshal(const void*, OB::OutputStreamImpl*) const;
    virtual void unmarshal(void*, OB::InputStreamImpl*) const;
};

//
// IDL:DomainData/File:1.0
//
struct File;
typedef OB::VarVar< File > File_var;
typedef OB::VarOut< File > File_out;

struct File
{
#ifdef OB_CLEAR_MEM
    File();
#else
    File() { }
#endif
    File(const File&);
    File& operator=(const File&);

    typedef File_var _var_type;

    OB::StrForStruct name;
    ::CORBA::ULong size;
    Content body;

    void _OB_marshal(OB::OutputStreamImpl*) const;
    static void _OB_unmarshal(File&, OB::InputStreamImpl*);
};

extern OB::TypeCodeConst _tc_File;

//
// IDL:DomainData/Mode:1.0
//
enum Mode
{
    passiv,
    active
};

typedef Mode& Mode_out;

extern OB::TypeCodeConst _tc_Mode;

//
// IDL:DomainData/Enability:1.0
//
struct Enability;
typedef OB::FixVar< Enability > Enability_var;
typedef Enability& Enability_out;

struct Enability
{
    typedef Enability_var _var_type;

    ::CORBA::Boolean status;
    Mode mode_;

    void _OB_marshal(OB::OutputStreamImpl*) const;
    static void _OB_unmarshal(Enability&, OB::InputStreamImpl*);
};

extern OB::TypeCodeConst _tc_Enability;

} // End of namespace DomainData

//
// IDL:DomainData:1.0
//
namespace OBProxy_DomainData
{

} // End of namespace OBProxy_DomainData

//
// IDL:DomainData:1.0
//
namespace OBStubImpl_DomainData
{

} // End of namespace OBStubImpl_DomainData

//
// IDL:DomainData:1.0
//
namespace OBMarshalStubImpl_DomainData
{

} // End of namespace OBMarshalStubImpl_DomainData

//
// IDL:DomainData:1.0
//
namespace OBV_DomainData
{

} // End of namespace OBV_DomainData

//
// IDL:DomainData/User:1.0
//
void operator<<=(::CORBA::Any&, DomainData::User*);
void operator<<=(::CORBA::Any&, const DomainData::User&);
CORBA::Boolean operator>>=(const ::CORBA::Any&, const DomainData::User*&);

inline void
operator<<=(::CORBA::Any_var& any, DomainData::User* val)
{
    any.inout() <<= val;
}

inline void
operator<<=(::CORBA::Any_var& any, const DomainData::User& val)
{
    any.inout() <<= val;
}

inline ::CORBA::Boolean
operator>>=(const ::CORBA::Any_var& any, const DomainData::User*& val)
{
    return any.in() >>= val;
}

//
// IDL:DomainData/Address:1.0
//
void operator<<=(::CORBA::Any&, DomainData::Address*);
void operator<<=(::CORBA::Any&, const DomainData::Address&);
CORBA::Boolean operator>>=(const ::CORBA::Any&, const DomainData::Address*&);

inline void
operator<<=(::CORBA::Any_var& any, DomainData::Address* val)
{
    any.inout() <<= val;
}

inline void
operator<<=(::CORBA::Any_var& any, const DomainData::Address& val)
{
    any.inout() <<= val;
}

inline ::CORBA::Boolean
operator>>=(const ::CORBA::Any_var& any, const DomainData::Address*& val)
{
    return any.in() >>= val;
}

//
// IDL:DomainData/Message:1.0
//
void operator<<=(::CORBA::Any&, DomainData::Message*);
void operator<<=(::CORBA::Any&, const DomainData::Message&);
CORBA::Boolean operator>>=(const ::CORBA::Any&, const DomainData::Message*&);

inline void
operator<<=(::CORBA::Any_var& any, DomainData::Message* val)
{
    any.inout() <<= val;
}

inline void
operator<<=(::CORBA::Any_var& any, const DomainData::Message& val)
{
    any.inout() <<= val;
}

inline ::CORBA::Boolean
operator>>=(const ::CORBA::Any_var& any, const DomainData::Message*& val)
{
    return any.in() >>= val;
}

//
// IDL:DomainData/Content:1.0
//
void operator<<=(::CORBA::Any&, DomainData::Content*);
void operator<<=(::CORBA::Any&, const DomainData::Content&);
CORBA::Boolean operator>>=(const ::CORBA::Any&, const DomainData::Content*&);

inline void
operator<<=(::CORBA::Any_var& any, DomainData::Content* val)
{
    any.inout() <<= val;
}

inline void
operator<<=(::CORBA::Any_var& any, const DomainData::Content& val)
{
    any.inout() <<= val;
}

inline ::CORBA::Boolean
operator>>=(const ::CORBA::Any_var& any, const DomainData::Content*& val)
{
    return any.in() >>= val;
}

//
// IDL:DomainData/File:1.0
//
void operator<<=(::CORBA::Any&, DomainData::File*);
void operator<<=(::CORBA::Any&, const DomainData::File&);
CORBA::Boolean operator>>=(const ::CORBA::Any&, const DomainData::File*&);

inline void
operator<<=(::CORBA::Any_var& any, DomainData::File* val)
{
    any.inout() <<= val;
}

inline void
operator<<=(::CORBA::Any_var& any, const DomainData::File& val)
{
    any.inout() <<= val;
}

inline ::CORBA::Boolean
operator>>=(const ::CORBA::Any_var& any, const DomainData::File*& val)
{
    return any.in() >>= val;
}

//
// IDL:DomainData/Mode:1.0
//
void operator<<=(::CORBA::Any&, DomainData::Mode);
CORBA::Boolean operator>>=(const ::CORBA::Any&, DomainData::Mode&);

inline void
operator<<=(::CORBA::Any_var& any, DomainData::Mode val)
{
    any.inout() <<= val;
}

inline ::CORBA::Boolean
operator>>=(const ::CORBA::Any_var& any, DomainData::Mode& val)
{
    return any.in() >>= val;
}

//
// IDL:DomainData/Enability:1.0
//
void operator<<=(::CORBA::Any&, DomainData::Enability*);
void operator<<=(::CORBA::Any&, const DomainData::Enability&);
CORBA::Boolean operator>>=(const ::CORBA::Any&, const DomainData::Enability*&);

inline void
operator<<=(::CORBA::Any_var& any, DomainData::Enability* val)
{
    any.inout() <<= val;
}

inline void
operator<<=(::CORBA::Any_var& any, const DomainData::Enability& val)
{
    any.inout() <<= val;
}

inline ::CORBA::Boolean
operator>>=(const ::CORBA::Any_var& any, const DomainData::Enability*& val)
{
    return any.in() >>= val;
}

#endif
