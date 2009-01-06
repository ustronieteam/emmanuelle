#include "ServerDataBase.h"


///
/// Konstruktor bezparametrowy.
ServerDataBase::ServerDataBase() 
{

}

///
/// Konstruktor kopiujacy.
/// @param[in] arg Baza danych do skopiowania.
ServerDataBase::ServerDataBase(const ServerDataBase & arg) 
{

}

///
/// Operator przypisania.
/// param[in] arg Baza danych ktora chcemy przypisac.
ServerDataBase & ServerDataBase::operator =(const ServerDataBase & arg) 
{
	return const_cast<ServerDataBase &>(arg);
}

///
/// Destruktor.
ServerDataBase::~ServerDataBase() 
{

}

///
/// Zamyka baze danych.
/// @return ???
int ServerDataBase::Close()
{

	return 0;
}

///
/// Inicjalizuje baze danych.
/// @return ???
int ServerDataBase::Initialize()
{

	return 0;
}

///
/// Znajdz rekord servera.
/// @param[in] address Adres do wyszukania rekordu.
/// @return ID wyszukanego rekordu.
int ServerDataBase::Find(DomainData::Address & address)
{
	return 0;
}
