#include "ClientsDataBase.h"


///
/// Konstruktor bezparametrowy.
ClientsDataBase::ClientsDataBase() 
{

}

///
/// Konstruktor kopiujacy.
/// @param[in] arg Baza danych do skopiowania.
ClientsDataBase::ClientsDataBase(const ClientsDataBase & arg) 
{

}

///
/// Operator przypisania.
/// param[in] arg Baza danych ktora chcemy przypisac.
ClientsDataBase & ClientsDataBase::operator =(const ClientsDataBase & arg) 
{
	return const_cast<ClientsDataBase &>(arg);
}

///
/// Destruktor.
ClientsDataBase::~ClientsDataBase() 
{

}

///
/// Zamyka baze danych.
/// @return ???
int ClientsDataBase::Close()
{

	return 0;
}

///
/// Inicjalizuje baze danych.
/// @return ???
int ClientsDataBase::Initialize()
{

	return 0;
}

///
/// Znajdz rekord klienta.
/// @param[in] address Adres do wyszukania rekordu.
/// @return ID wyszukanego rekordu.
int ClientsDataBase::Find(DomainData::Address & address)
{
	return 0;
}