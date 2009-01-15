#include "ServerRecord.h"

ServerRecord::ServerRecord() 
{

}

ServerRecord::ServerRecord(const ServerRecord & arg) 
{
	this->_recordId				= arg._recordId;
	this->_address				= arg._address;
	this->_broker				= arg._broker;

	this->_serverRemoteInstance = arg._serverRemoteInstance;
}

ServerRecord & ServerRecord::operator =(const ServerRecord & arg) 
{
	/// Jesli sa to rozne obiekty.
    if (this != &arg)
    {
		this->_recordId				= arg._recordId;
		this->_address				= arg._address;
		this->_broker				= arg._broker;

		this->_serverRemoteInstance = arg._serverRemoteInstance;
	}

	return *this;
}

ServerRecord::~ServerRecord() 
{

}

const IServerServer_var & ServerRecord::GetServerRemoteInstance() const
{
	return this->_serverRemoteInstance;
}

void ServerRecord::SetServerRemoteInstance(const IServerServer_var & serverRemoteInstance)
{
	this->_serverRemoteInstance = serverRemoteInstance;
}
