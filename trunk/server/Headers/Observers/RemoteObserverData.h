#ifndef REMOTEOBSERVERDATA_H
#define REMOTEOBSERVERDATA_H
//Begin section for file RemoteObserverData.h
//TODO: Add definitions that you want preserved
//End section for file RemoteObserverData.h

#include "EventType.h"
#include "DomainData.h"


//Dane przekazywane przez zdalny obiekt obserwowany do odpowiedniego obserwatora. Dzieki temu bedzie wiedzial co sie
//zmienilo.
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class RemoteObserverData
{

    //Begin section for RemoteObserverData
    //TODO: Add attributes that you want preserved
    //End section for RemoteObserverData

    private:
        EventType eventType;
		DomainData::Address _serverAddress;
		DomainData::Address _clientAddress;
		DomainData::Address _senderClientAddress;
		DomainData::Message _clientMessage;
		DomainData::Enability _clientEnability;
		DomainData::Address _pipeHolderAddress;

    public:

   
        RemoteObserverData();
        RemoteObserverData(RemoteObserverData & arg);
        RemoteObserverData & operator =(const RemoteObserverData & arg);
        virtual ~RemoteObserverData();
        EventType & get_eventType();
        void set_eventType(EventType & eventType);
		
		DomainData::Address & getServerAddress(){return _serverAddress;}
		void setServerAddress(DomainData::Address & serverAddress){_serverAddress = serverAddress;}

		DomainData::Address & getClientAddress(){return _clientAddress;}
		void setClientAddress(DomainData::Address & clientAddress){_clientAddress = clientAddress;}

		DomainData::Message & getClientMessage(){return _clientMessage;}
		void setClientMessage(DomainData::Message & clientMessage){_clientMessage = clientMessage;}

		DomainData::Address & getSenderClientAddress(){return _senderClientAddress;}
		void setSenderClientAddress(DomainData::Address & senderClientAddress){_senderClientAddress = senderClientAddress;}

		DomainData::Enability & getClientEnability(){return _clientEnability;}
		void setClientEnability(DomainData::Enability & clientEnability){_clientEnability = clientEnability;}

		DomainData::Address & getPipeHolderAddress(){return _pipeHolderAddress;}
		void setPipeHolderAddress(DomainData::Address & pipeHolderAddress){_pipeHolderAddress = pipeHolderAddress;}



};  //end class RemoteObserverData

#endif
