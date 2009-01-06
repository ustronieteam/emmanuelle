#include "ServerRecord.h"

///
/// Konstruktor bezparametrowy.
ServerRecord::ServerRecord() 
{

}

///
/// Konstruktor kopiujacy.
/// @param[in] arg Record do skopiowania.
ServerRecord::ServerRecord(const ServerRecord & arg) 
{
	this->_serverRemoteInstance = arg._serverRemoteInstance;
}

///
/// Operator przypisania.
/// param[in] arg Record ktory chcemy przypisac.
ServerRecord & ServerRecord::operator =(const ServerRecord & arg) 
{
	/// Jesli sa to rozne obiekty.
    if (this != &arg)
    {
		this->_serverRemoteInstance = arg._serverRemoteInstance;
	}

	return const_cast<ServerRecord &>(arg);
}


///
/// Destruktor.
ServerRecord::~ServerRecord() 
{

}

///
/// Pobiera namiastke serwera.
/// @return Namiastka servera.
IServerServer_var ServerRecord::GetServerRemoteInstance() const
{
	return this->_serverRemoteInstance;
}

///
/// Ustawia namiastke servera.
/// @param[in] serverRemoteInstance Namiastka servera.
void ServerRecord::SetServerRemoteInstance(IServerServer_var serverRemoteInstance)
{
	this->_serverRemoteInstance = serverRemoteInstance;
}

///
/// Pobiera adresu serwera.
/// @return Adres serwera.
struct DomainData::Address ServerRecord::GetAddress() const
{
	return this->_address;
}

///
/// Ustawia adres serwera.
/// param[in] address Adres serwera.
void ServerRecord::SetAddress(struct DomainData::Address & address)
{
	this->_address = address;
}
