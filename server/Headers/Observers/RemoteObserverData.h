#ifndef REMOTEOBSERVERDATA_H
#define REMOTEOBSERVERDATA_H


#include "EventType.h"
#include "DomainData.h"

///
///@author Marian Szczykulski
///@date 2009-01-09
///@brief Klasa danych obserwatora
///
class RemoteObserverData
{
    private:
        EventType eventType;
		DomainData::Address _serverAddress;
		DomainData::User _clientData;
		DomainData::User _senderClientData;

		DomainData::Message _clientMessage;
		DomainData::Enability _clientEnability;
		DomainData::User _pipeHolderData;

		DomainData::User	_clientUserData;

    public:

   
        RemoteObserverData();
        virtual ~RemoteObserverData();
        EventType & get_eventType();
        void set_eventType(EventType eventType);
		
		DomainData::Address & getServerAddress(){return _serverAddress;}
		void setServerAddress(const DomainData::Address & serverAddress){_serverAddress = serverAddress;}

		DomainData::User & getDestinationUser(){return _clientData;}
		void setDestination(const DomainData::User & clientDt){_clientData = clientDt;}

		DomainData::Message & getClientMessage(){return _clientMessage;}
		void setClientMessage(const DomainData::Message & clientMessage){_clientMessage = clientMessage;}

		DomainData::User & getSenderClientData(){return _senderClientData;}
		void setSenderClientData(const DomainData::User & senderClientD){_senderClientData = senderClientD;}

		DomainData::Enability & getClientEnability(){return _clientEnability;}
		void setClientEnability(const DomainData::Enability & clientEnability){_clientEnability = clientEnability;}

		DomainData::User & getPipeHolderData(){return _pipeHolderData;}
		void setPipeHolderData(const DomainData::User & pipeHolderData){_pipeHolderData = pipeHolderData;}

		DomainData::User & getClientUserData(){return _clientUserData;}
		void setClientUserData( const DomainData::User & clientUserData){_clientUserData = clientUserData;}




};  //end class RemoteObserverData

#endif
