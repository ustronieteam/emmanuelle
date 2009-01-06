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
int ServerDataBase::Find(struct DomainData::Address & address)
{
	ServerRecord * r;

	if ( _records.size() != 0 )
		for(map<int, Record>::iterator i = this->_records.begin(); i != this->_records.end(); i++)
		{
			r = static_cast<ServerRecord *>(&(i->second));

			if ( r->GetAddress().name == address.name && r->GetAddress().localization == address.localization )
				return r->GetRecordId();
		}

	return -1;
}
