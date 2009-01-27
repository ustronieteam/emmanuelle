#ifndef ___IClientClient_impl_h__
#define ___IClientClient_impl_h__

#include <IClientClient_skel.h>
#include "IRemoteObserverObject.h"

///
/// @author	Mateusz Ko³odziejczyk
/// @date	06.01.2009
///
/// @brief	Klasa wygenerowana z pliku IDL IClientClient.idl
///
/// Ciala metod zaimplementowane przez programiste
///

class IClientClient_impl : virtual public POA_IClientClient,
                           virtual public PortableServer::RefCountServantBase,
						   virtual public IRemoteObserverObject
{
    IClientClient_impl(const IClientClient_impl&);
    void operator=(const IClientClient_impl&);

    PortableServer::POA_var poa_;

	//logger
	log4cxx::LoggerPtr logger;

	int isPipeOpen;
	DomainData::User senderCC;
	DomainData::User receiverCC;
	DomainData::File file;

public:

    IClientClient_impl(PortableServer::POA_ptr);
    ~IClientClient_impl();

    virtual PortableServer::POA_ptr _default_POA();

    ///
	/// @param [in] f			plik
	/// @param [in] receiver	odbiorca
	/// 
	/// Wysy³anie pliku.
	///
    virtual void SendFile(const ::DomainData::File& f,
                          const ::DomainData::User& receiver)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] receiver	odbiorca
	///
	/// Utworzenie rurki
	///
    virtual void CreatePipe(const ::DomainData::User& receiver)
        throw(::CORBA::SystemException);

	///
	/// @param [in] sender		klient od którego oczekujemy pliku w rurce.
	/// @return					plik
	/// 
	/// Pobranie pliku z rurki
	///
    virtual ::DomainData::File* GetFile(const ::DomainData::User& sender)
        throw(::CORBA::SystemException);
};

#endif
