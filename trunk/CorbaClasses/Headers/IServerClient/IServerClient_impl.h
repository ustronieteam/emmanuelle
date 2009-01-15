#ifndef ___IServerClient_impl_h__
#define ___IServerClient_impl_h__

#include <IServerClient_skel.h>
#include "IRemoteObjects.h"

#include <log4cxx/logger.h>
#include <log4cxx/level.h>

///
/// @author	Mateusz Ko�odziejczyk
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
	/// @param [in] m		tryb (czy mozliwe s� po��czenia przychodz�ce do klienta)
	/// @param [in] usr		dane uzytkownika, ktory chce sie polaczyc z serwerem
	/// @return				Adres innego serwera z kt�rym powinien pr�bowac pod��czy� si� klient
	///						lub w�asny adres serwera je�eli uda�o si� pod��czy�
	///
	/// Metoda umo�liwia pod��czenie si� klienta do serwera. JE�eli dany serwer odmawia po��czenia,
	/// np. za du�o klient�w ju� obs�uguje, to metoda zwraca adres innego serwera z kt�rym powinien
	/// pr�bowac pod��czy� si� dany klient.
	///
    virtual ::DomainData::Address* Connect(const ::DomainData::Address& server,
                                           ::DomainData::Mode m,
                                           const ::DomainData::User& usr)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] usr		dane uzytkownika, ktory sie chce rozlaczyc
	///
	/// Metoda roz��cza danego klienta z systemem
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
	/// @param [in] ssender		nadawca wiadomo�ci
	/// @param [in] receiver	odbiorca wiadomosci
	/// @param [in] msg			przesy�ana wiadomo��
	///
	/// Metoda wysy�a wiadomo�c Message do klienta ReceiverAddress
	///
    virtual void SendMessage(const ::DomainData::User& ssender,
                             const ::DomainData::User& receiver,
                             const ::DomainData::Message& msg)
        throw(::CORBA::SystemException);

    
	///
	/// @param [in] usr		sprawdzany klienta
	/// @return				struktura z informacjami o statusie klienta usr
	/// 
	/// Metoda umozliwia sprawdzenie czy dany klient jest dost�pny. Oraz czy mo�na mu wys�a� plik
	/// (czy jest passywny czy aktywny)
	///
    virtual ::DomainData::Enability CheckClientStatus(const ::DomainData::User& usr)
        throw(::CORBA::SystemException);

    ///
	/// @param [in] receiver	klient kt�remu chcemy wys�a� plik
	///							ale nie mo�emy to zrobi� bezpo�rednio
	/// @return					klient po�redni
	///
	/// Metoda tworzy kana� w przesy�aniu plik�w pomiedzy klientami
	/// za pomoc� po�rednika (PipeHolder)
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
