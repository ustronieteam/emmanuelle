#include "ClientRecord.h"

ClientRecord::ClientRecord() 
{

}

ClientRecord::ClientRecord(const ClientRecord & arg) 
{
	this->_recordId				= arg._recordId;
	this->_address				= arg._address;
	this->_broker				= arg._broker;

	this->_clientServerId		= arg._clientServerId;
	this->_clientRemoteInstance = arg._clientRemoteInstance;
	this->_enability			= arg._enability;
	this->_user					= arg._user;
}

ClientRecord & ClientRecord::operator =(const ClientRecord & arg) 
{
	/// Jesli sa to rozne obiekty.
    if (this != &arg)
    {
		this->_recordId				= arg._recordId;
		this->_address				= arg._address;
		this->_broker				= arg._broker;

		this->_clientServerId		= arg._clientServerId;
		this->_clientRemoteInstance = arg._clientRemoteInstance;
		this->_enability			= arg._enability;
		this->_user					= arg._user;
    }

	return *this;
}

ClientRecord::~ClientRecord() 
{

}

const int & ClientRecord::GetClientServerId() const
{
	return this->_clientServerId;
}

void ClientRecord::SetClientServerId(const int & clientServerId)
{
	this->_clientServerId = clientServerId;
}

const IClientServer_var & ClientRecord::GetClientRemoteInstance() const
{
	return this->_clientRemoteInstance;
}

void ClientRecord::SetClientRemoteInstance(const IClientServer_var & clientRemoteInstance)
{
	this->_clientRemoteInstance = clientRemoteInstance;
}

const struct DomainData::Enability & ClientRecord::GetEnability() const
{
	return this->_enability;
}

void ClientRecord::SetEnability(const struct DomainData::Enability & enability)
{
	this->_enability = enability;
}

const struct DomainData::User & ClientRecord::GetUser() const
{
	return this->_user;
}

void ClientRecord::SetUser(const struct DomainData::User & user)
{
	this->_user = user;
}