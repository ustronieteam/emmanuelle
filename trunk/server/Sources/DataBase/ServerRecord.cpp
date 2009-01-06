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
IServerServer * ServerRecord::GetServerRemoteInstance() const
{
	return this->_serverRemoteInstance;
}

///
/// Ustawia namiastke servera.
/// @param[in] serverRemoteInstance Namiastka servera.
void ServerRecord::SetServerRemoteInstance(IServerServer * serverRemoteInstance)
{
	this->_serverRemoteInstance = serverRemoteInstance;
}
