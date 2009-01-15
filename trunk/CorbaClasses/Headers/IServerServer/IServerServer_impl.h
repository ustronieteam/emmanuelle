#ifndef ___IServerServer_impl_h__
#define ___IServerServer_impl_h__

#include <IServerServer_skel.h>
#include "IRemoteObjects.h"

#include <log4cxx/logger.h>
#include <log4cxx/level.h>

///
/// @author	Mateusz Ko�odziejczyk
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
	/// @return						struktura z adresami wszystkich serwer�w oraz 
	///								danymi o klientach
	/// 
	/// Metoda umo�liwia po��czenie si� serwera do systemu. Kroki jakie zachodz� 
	/// podczas takiego zdarzenia opisane s� w dokumentacji architektury systemu
	///
    virtual ::AddressesList* Join(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException);

    ///
	/// Metoda od��czenie si� od systemu.
	///
    virtual void Unjoin()
        throw(::CORBA::SystemException);

    ///
	/// @param [in] serverAddress	adres dodawanego serwera
	/// 
	/// Metoda powoduj�ca dodanie nowego adresu serwera do listy dost�pnych serwer�w.
	/// Jest �ci�le powi�zana z metod� Join i algorytmem do��cznia si� nowego serwera.
	///
    virtual void AddServer(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] serverAddress	adres usuwanego serwera
	///
	/// Metoda powoduj�ca usuniecie adresu serwera z listy dost�pnych serwer�w
	/// Patrz metoda Unjoin
	///
    virtual void RemoveServer(const ::DomainData::Address& serverAddress)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] msg			Wiadomo�� wys�ana przez SenderAddres
	/// @param [in] sender		Nadawca wiadomo�ci
	/// @param [in] receiver    Adresat
	///  
	/// Metoda przekazuje wiadomo�� do serwera do kt�rego pod��czony jest Adresat(ReceiverAddress)
	///
    virtual void PassMessage(const ::DomainData::Message& msg,
                             const ::DomainData::User& sender,
                             const ::DomainData::User& receiver)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] pipeHolder		Adres po�rednika w przesy�aniu plik�w
	/// @param [in] sender			Wysy�aj�cy plik (zrod�o)
	/// @param [in] receiver	   	Adresat (odbiorca pliku)
	///
	/// Metoda przekazuj�ca serwerowi do kt�rego pod��czony jest ReceiverAddress (adresat)
	/// informacje o tym �e zak�adane jest po��czenie posrednie przez PipeHolderAddress
	/// w celu wys�ania pliku do ReceiverAddress.
	///
    virtual void PassCreatePipeRequest(const ::DomainData::User& pipeHolder,
                                       const ::DomainData::User& sender,
                                       const ::DomainData::User& receiver)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] client				klient, ktory zmienia status
	/// @param [in] clientAddress		adres klienta
	/// @param [in] en					struktura opisuj�ca stan klienta
	/// @param [in] senderServerAddress adres serwera ktory wywoluje metode
	///
	/// Metoda umo�liwia przes�anie informacji o statusie klienta(a w�a�ciwie jego zmianie)
	///
    virtual void ClientStatusChanged(const ::DomainData::User& client,
                                     const ::DomainData::Address& clientAddress,
                                     const ::DomainData::Enability& en,
                                     const ::DomainData::Address& senderServerAddress)
        throw(::CORBA::SystemException);
};

#endif
