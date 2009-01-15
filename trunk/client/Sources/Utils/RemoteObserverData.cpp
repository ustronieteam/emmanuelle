#include "RemoteObserverData.h"

RemoteObserverData::RemoteObserverData() 
{
    
}

RemoteObserverData::~RemoteObserverData() 
{

}

const ObserverType & RemoteObserverData::GetObserverType() const
{
	return _eventType;
}

void RemoteObserverData::SetObserverType(const ObserverType & type)
{
	_eventType = type;
}

const DomainData::Message & RemoteObserverData::GetSenderMessage() const
{
	return _message;
}

void RemoteObserverData::SetSenderMessage(const DomainData::Message & msg)
{
	_message = msg;
}

const DomainData::User & RemoteObserverData::GetUser() const
{
	return _user;
}

void RemoteObserverData::SetUser(const DomainData::User & user)
{
	_user = user;
}

const std::string & RemoteObserverData::GetFileName() const
{
	return _fileName;
}

void RemoteObserverData::SetFileName(const std::string & file)
{
	_fileName = file;
}
