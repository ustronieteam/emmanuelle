#ifndef ___IServerServer_impl_h__
#define ___IServerServer_impl_h__

#include <IServerServer_skel.h>
#include "IRemoteObjects.h"

#include <log4cxx/logger.h>
#include <log4cxx/level.h>

///
/// @author	Mateusz Ko³odziejczyk
/// @date	06.01.2009
///
/// @brief	Klasa wygenerowana z pliku IDL IServerServer.idl
///
/// Ciala metod zaimplemetowane przez programiste
///
class IServerServer_impl : virtual public POA_IServerServer,
                           virtual public PortableServer::RefCountServantBase,
						   virtual public IRemoteObjects
{
    IServerServer_impl(const IServerServer_impl&);
    void operator=(const IServerServer_impl&);

    PortableServer::POA_var poa_;

	// logger
	log4cxx::LoggerPtr logger;

public:

    IServerServer_impl(PortableServer::POA_ptr);
    ~IServerServer_impl();

    virtual PortableServer::POA_ptr _default_POA();

    ///
	/// @param [in] serverAddress	adres servera, do ktorego sie podlaczamy
	/// @return						struktura z adresami wszystkich serwerów oraz 
	///								danymi o klientach
	/// 
	/// Metoda umo¿liwia po³¹czenie siê serwera do systemu. Kroki jakie zachodz¹ 
	/// podczas takiego zdarzenia opisane s¹ w dokumentacji architektury systemu
	///
    virtual ::AddressesList* Join(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException);

    ///
	/// Metoda od³¹czenie siê od systemu.
	///
    virtual void Unjoin()
        throw(::CORBA::SystemException);

    ///
	/// @param [in] serverAddress	adres dodawanego serwera
	/// 
	/// Metoda powoduj¹ca dodanie nowego adresu serwera do listy dostêpnych serwerów.
	/// Jest œciœle powi¹zana z metod¹ Join i algorytmem do³¹cznia siê nowego serwera.
	///
    virtual void AddServer(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] serverAddress	adres usuwanego serwera
	///
	/// Metoda powoduj¹ca usuniecie adresu serwera z listy dostêpnych serwerów
	/// Patrz metoda Unjoin
	///
    virtual void RemoveServer(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] msg			Wiadomoœæ wys³ana przez SenderAddres
	/// @param [in] sender		Nadawca wiadomoœci
	/// @param [in] receiver    Adresat
	///  
	/// Metoda przekazuje wiadomoœæ do serwera do którego pod³¹czony jest Adresat(ReceiverAddress)
	///
    virtual void PassMessage(const ::DomainData::Message& msg,
                             const ::DomainData::User& sender,
                             const ::DomainData::User& receiver)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] pipeHolder		Adres poœrednika w przesy³aniu plików
	/// @param [in] sender			Wysy³aj¹cy plik (zrod³o)
	/// @param [in] receiver	   	Adresat (odbiorca pliku)
	///
	/// Metoda przekazuj¹ca serwerowi do którego pod³¹czony jest ReceiverAddress (adresat)
	/// informacje o tym ¿e zak³adane jest po³¹czenie posrednie przez PipeHolderAddress
	/// w celu wys³ania pliku do ReceiverAddress.
	///
    virtual void PassCreatePipeRequest(const ::DomainData::User& pipeHolder,
                                       const ::DomainData::User& sender,
                                       const ::DomainData::User& receiver)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] client				klient, ktory zmienia status
	/// @param [in] clientAddress		adres klienta
	/// @param [in] en					struktura opisuj¹ca stan klienta
	/// @param [in] senderServerAddress adres serwera ktory wywoluje metode
	///
	/// Metoda umo¿liwia przes³anie informacji o statusie klienta(a w³aœciwie jego zmianie)
	///
    virtual void ClientStatusChanged(const ::DomainData::User& client,
                                     const ::DomainData::Address& clientAddress,
                                     const ::DomainData::Enability& en,
                                     const ::DomainData::Address& senderServerAddress)
        throw(::CORBA::SystemException);
};

#endif
