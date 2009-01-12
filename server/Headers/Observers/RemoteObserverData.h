#ifndef REMOTEOBSERVERDATA_H
#define REMOTEOBSERVERDATA_H


#include "EventType.h"
#include "DomainData.h"

///@author Marian Szczykulski
///@date 2009-01-09
///@brief Klasa danych obserwatora
class RemoteObserverData
{
    private:
        EventType eventType;
		DomainData::Address _serverAddress;
		DomainData::Address _clientAddress;
		DomainData::Address _senderClientAddress;

		DomainData::Message _clientMessage;
		DomainData::Enability _clientEnability;
		DomainData::Address _pipeHolderAddress;

		DomainData::User	_clientUserData;

    public:

   
        RemoteObserverData();
        virtual ~RemoteObserverData();
        EventType & get_eventType();
        void set_eventType(EventType eventType);
		
		DomainData::Address & getServerAddress(){return _serverAddress;}
		void setServerAddress(const DomainData::Address & serverAddress){_serverAddress = serverAddress;}

		DomainData::Address & getClientAddress(){return _clientAddress;}
		void setClientAddress(const DomainData::Address & clientAddress){_clientAddress = clientAddress;}

		DomainData::Message & getClientMessage(){return _clientMessage;}
		void setClientMessage(const DomainData::Message & clientMessage){_clientMessage = clientMessage;}

		DomainData::Address & getSenderClientAddress(){return _senderClientAddress;}
		void setSenderClientAddress(const DomainData::Address & senderClientAddress){_senderClientAddress = senderClientAddress;}

		DomainData::Enability & getClientEnability(){return _clientEnability;}
		void setClientEnability(const DomainData::Enability & clientEnability){_clientEnability = clientEnability;}

		DomainData::Address & getPipeHolderAddress(){return _pipeHolderAddress;}
		void setPipeHolderAddress(const DomainData::Address & pipeHolderAddress){_pipeHolderAddress = pipeHolderAddress;}

		DomainData::User & getClientUserData(){return _clientUserData;}
		void setClientUserData( const DomainData::User & clientUserData){_clientUserData = clientUserData;}




};  //end class RemoteObserverData

#endif
