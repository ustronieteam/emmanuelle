#include "ClientRecord.h"

///
/// Konstruktor bezparametrowy.
ClientRecord::ClientRecord() 
{

}

///
/// Konstruktor kopiujacy.
/// @param[in] arg Record do skopiowania.
ClientRecord::ClientRecord(const ClientRecord & arg) 
{
	this->_clientServerId		= arg._clientServerId;
	this->_clientRemoteInstance = arg._clientRemoteInstance;
	this->_enability			= arg._enability;
}

///
/// Operator przypisania.
/// param[in] arg Record ktory chcemy przypisac.
ClientRecord & ClientRecord::operator =(const ClientRecord & arg) 
{
	/// Jesli sa to rozne obiekty.
    if (this != &arg)
    {
		this->_clientServerId		= arg._clientServerId;
		this->_clientRemoteInstance = arg._clientRemoteInstance;
		this->_enability			= arg._enability;
    }

	return const_cast<ClientRecord &>(arg);
}

///
/// Destruktor.
ClientRecord::~ClientRecord() 
{

}

///
/// Zwraca ID serwera do ktorego podlaczony jest klient.
/// @return Id serwera do ktorego podlaczony jest klient.
int ClientRecord::GetClientServerId() const
{
	return this->_clientServerId;
}

///
/// Ustawia ID serwera do ktorego podlaczony jest klient.
/// @param[in] clientServerId Id serwera do ktorego podlaczony jest klient.
void ClientRecord::SetClientServerId(int & clientServerId)
{
	this->_clientServerId = clientServerId;
}

///
/// Pobiera namiastke klienta.
/// @return Namiastka klienta.
IClientServer_var ClientRecord::GetClientRemoteInstance() const
{
	return this->_clientRemoteInstance;
}

///
/// Ustawia namiastke klienta.
/// @param[in] clientRemoteInstance Namiastka klienta.
void ClientRecord::SetClientRemoteInstance(IClientServer_var clientRemoteInstance)
{
	this->_clientRemoteInstance = clientRemoteInstance;
}

///
/// Pobiera dostepnosc klienta.
/// @return Dostepnosc klienta.
struct DomainData::Enability ClientRecord::GetEnability() const
{
	return this->_enability;
}

///
/// Ustawia dostepnosc klienta.
/// param[in] enability Dostepnosc klienta.
void ClientRecord::SetEnability(struct DomainData::Enability & enability)
{
	this->_enability = enability;
}
