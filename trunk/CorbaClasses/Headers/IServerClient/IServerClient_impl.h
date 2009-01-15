#ifndef ___IServerClient_impl_h__
#define ___IServerClient_impl_h__

#include <IServerClient_skel.h>
#include "IRemoteObjects.h"

#include <log4cxx/logger.h>
#include <log4cxx/level.h>

///
/// @author	Mateusz Ko³odziejczyk
/// @date	06.01.2009
///
/// @brief	Klasa wygenerowana z pliku IDL IServerClient.idl
///
/// Ciala metod zaimplementowane przez programiste
///

class IServerClient_impl : virtual public POA_IServerClient,
                           virtual public PortableServer::RefCountServantBase,
						   virtual public IRemoteObjects
{
    IServerClient_impl(const IServerClient_impl&);
    void operator=(const IServerClient_impl&);

    PortableServer::POA_var poa_;

	// logger
	log4cxx::LoggerPtr logger;

public:

    IServerClient_impl(PortableServer::POA_ptr);
    ~IServerClient_impl();

    virtual PortableServer::POA_ptr _default_POA();

    ///
	/// @param [in] server	adres serwera, do ktorego laczy sie klient (ta dana potrzebna jest serwerowi)
	/// @param [in] m		tryb (czy mozliwe s¹ po³¹czenia przychodz¹ce do klienta)
	/// @param [in] usr		dane uzytkownika, ktory chce sie polaczyc z serwerem
	/// @return				Adres innego serwera z którym powinien próbowac pod³¹czyæ siê klient
	///						lub w³asny adres serwera je¿eli uda³o siê pod³¹czyæ
	///
	/// Metoda umo¿liwia pod³¹czenie siê klienta do serwera. JE¿eli dany serwer odmawia po³¹czenia,
	/// np. za du¿o klientów ju¿ obs³uguje, to metoda zwraca adres innego serwera z którym powinien
	/// próbowac pod³¹czyæ siê dany klient.
	///
    virtual ::DomainData::Address* Connect(const ::DomainData::Address& server,
                                           ::DomainData::Mode m,
                                           const ::DomainData::User& usr)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] usr		dane uzytkownika, ktory sie chce rozlaczyc
	///
	/// Metoda roz³¹cza danego klienta z systemem
	///
    virtual void Disconnect(const ::DomainData::User& usr)
        throw(::CORBA::SystemException);

    ///
	/// @param [in]	usr		dane uzytkownika, ktory chce sie zarejestrowac
	/// @return				uzupelnione dane uzytkownika (zarejetrowanie numeru)
	///
	/// Rejestracja uzytkownika w systemie 
	///
    virtual ::DomainData::User* Register(const ::DomainData::User& usr)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] ssender		nadawca wiadomoœci
	/// @param [in] receiver	odbiorca wiadomosci
	/// @param [in] msg			przesy³ana wiadomoœæ
	///
	/// Metoda wysy³a wiadomoœc Message do klienta ReceiverAddress
	///
    virtual void SendMessage(const ::DomainData::User& ssender,
                             const ::DomainData::User& receiver,
                             const ::DomainData::Message& msg)
        throw(::CORBA::SystemException);

    
	///
	/// @param [in] usr		sprawdzany klienta
	/// @return				struktura z informacjami o statusie klienta usr
	/// 
	/// Metoda umozliwia sprawdzenie czy dany klient jest dostêpny. Oraz czy mo¿na mu wys³aæ plik
	/// (czy jest passywny czy aktywny)
	///
    virtual ::DomainData::Enability CheckClientStatus(const ::DomainData::User& usr)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] receiver	klient któremu chcemy wys³aæ plik
	///							ale nie mo¿emy to zrobiæ bezpoœrednio
	/// @return					klient poœredni
	///
	/// Metoda tworzy kana³ w przesy³aniu plików pomiedzy klientami
	/// za pomoc¹ poœrednika (PipeHolder)
	///
    virtual ::DomainData::User* GetPipeHolder(const ::DomainData::User& receiver)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] usr		szukany uzytkownik
	/// @return				adres szukanego uzytkownika
	///
	/// szuka adresu danego uzytkownika w bazie na serwerze
	///
    virtual ::DomainData::Address* GetUserAddressByName(const ::DomainData::User& usr)
        throw(::CORBA::SystemException);
};

#endif
