#include "RemoteObserverData.h"

///
/// Konstruktor.
///
RemoteObserverData::RemoteObserverData() 
{
    
}

///
/// Destruktor.
///
RemoteObserverData::~RemoteObserverData() 
{

}

///
/// Pobiera typ zdarzenia.
/// @return Typ zdarzenia.
///
const ObserverType & RemoteObserverData::GetObserverType() const
{
	return _eventType;
}

///
/// Ustawia typ zdarzenia.
/// @param[in] type Typ zdarzenia.
///
void RemoteObserverData::SetObserverType(const ObserverType & type)
{
	_eventType = type;
}

///
/// Pobiera wiadomosc.
/// @return Wiadomosc.
///
const DomainData::Message & RemoteObserverData::GetSenderMessage() const
{
	return _message;
}

///
/// Ustawia wiadomosc.
/// @param[in] msg Wiadomosc
///
void RemoteObserverData::SetSenderMessage(const DomainData::Message & msg)
{
	_message = msg;
}

///
/// Pobiera nadawce.
/// @return Nadawca
///
const DomainData::User & RemoteObserverData::GetUser() const
{
	return _user;
}

///
/// Ustawia nadawce.
/// @parm[in] user Nadawca
///
void RemoteObserverData::SetUser(const DomainData::User & user)
{
	_user = user;
}

///
/// Pobiera plik.
/// @return Plik
///
const DomainData::File & RemoteObserverData::GetFile() const
{
	return _file;
}

///
/// Ustawia plik.
/// @parm[in] file Plik
///
void RemoteObserverData::SetFile(const DomainData::File & file)
{
	_file = file;
}
