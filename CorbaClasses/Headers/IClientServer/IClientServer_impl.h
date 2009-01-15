#ifndef ___IClientServer_impl_h__
#define ___IClientServer_impl_h__

#include <IClientServer_skel.h>
#include "IRemoteObserverObject.h"

///
/// @author	Mateusz Ko³odziejczyk
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
	/// @param [in] sender	uzytkownik, który wys³a³ wiadomoœæ
	/// @param [in] msg		wiadomoœæ
	/// 
	/// Metoda wyo³ywana, gdy na serwerze znajduje sie wiadomoœæ wys³ana do danego klienta
	/// a ten klient jest dostepny. Powoduje ona dostarczenie wiadomoœci do adresata
	///
    virtual void ReceiveMessage(const ::DomainData::User& sender,
                                const ::DomainData::Message& msg)
        throw(::CORBA::SystemException);


	///
	/// @param [in] serverAddress	adres alternatywnego serwera
	///
	/// metoda wywo³ywana na kliencie aby po³¹czyæ go z innym serwerem poniewa¿ ten, z którym 
	/// jest aktulanie polaczony z ro¿nych powodów musi siê roz³¹czyc z klientem
	///
    virtual void ChangeServer(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] pipeHolder	klient, do którego ma zostaæ ztworzona rurka
	/// @param [in] sender		klient chc¹cy po³¹czyæ sie z PipeHolderAddress 
	/// @return					powodzenie TRUE, niepowodzeni FALSE
	///
	/// Metoda wywo³ywana przez serwer na kliencie poœrednim (wybranym przez serwer) wtedy 
	/// gdy nie ma bezposredniego pol¹czenia miêdzy dwoma klientami (podczas przesy³ania pliku). 
	/// Jest to rz¹danie utworzenia rurki miêdzy clientem o identyfikatorze SenderAddress
	/// i klientem PipeHolderAddress 
	///
    virtual ::CORBA::Boolean CreatePipeRequest(const ::DomainData::User& sender,
                                               const ::DomainData::User& pipeHolder)
        throw(::CORBA::SystemException);
};

#endif
