#ifndef ___IClientServer_impl_h__
#define ___IClientServer_impl_h__

#include <IClientServer_skel.h>
#include "IRemoteObserverObject.h"

///
/// @author	Mateusz Ko�odziejczyk
/// @date	06.01.2009
///
/// @brief	Klasa wygenerowana z pliku IDL IClientServer.idl
///
/// Ciala metod uzupelnione przez programiste
///

class IClientServer_impl : virtual public POA_IClientServer,
                           virtual public PortableServer::RefCountServantBase,
						   virtual public IRemoteObserverObject
{
    IClientServer_impl(const IClientServer_impl&);
    void operator=(const IClientServer_impl&);

    PortableServer::POA_var poa_;

	//logger
	log4cxx::LoggerPtr logger;

public:

    IClientServer_impl(PortableServer::POA_ptr);
    ~IClientServer_impl();

    virtual PortableServer::POA_ptr _default_POA();

    ///
	/// @param [in] sender	uzytkownik, kt�ry wys�a� wiadomo��
	/// @param [in] msg		wiadomo��
	/// 
	/// Metoda wyo�ywana, gdy na serwerze znajduje sie wiadomo�� wys�ana do danego klienta
	/// a ten klient jest dostepny. Powoduje ona dostarczenie wiadomo�ci do adresata
	///
    virtual void ReceiveMessage(const ::DomainData::User& sender,
                                const ::DomainData::Message& msg)
        throw(::CORBA::SystemException);


	///
	/// @param [in] serverAddress	adres alternatywnego serwera
	///
	/// metoda wywo�ywana na kliencie aby po��czy� go z innym serwerem poniewa� ten, z kt�rym 
	/// jest aktulanie polaczony z ro�nych powod�w musi si� roz��czyc z klientem
	///
    virtual void ChangeServer(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] pipeHolder	klient, do kt�rego ma zosta� ztworzona rurka
	/// @param [in] sender		klient chc�cy po��czy� sie z PipeHolderAddress 
	/// @return					powodzenie TRUE, niepowodzeni FALSE
	///
	/// Metoda wywo�ywana przez serwer na kliencie po�rednim (wybranym przez serwer) wtedy 
	/// gdy nie ma bezposredniego pol�czenia mi�dzy dwoma klientami (podczas przesy�ania pliku). 
	/// Jest to rz�danie utworzenia rurki mi�dzy clientem o identyfikatorze SenderAddress
	/// i klientem PipeHolderAddress 
	///
    virtual ::CORBA::Boolean CreatePipeRequest(const ::DomainData::User& sender,
                                               const ::DomainData::User& pipeHolder)
        throw(::CORBA::SystemException);
};

#endif
