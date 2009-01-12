#ifndef REMOTEOBSERVERDATA_H
#define REMOTEOBSERVERDATA_H

#include "DomainData.h"
#include "ObserverType.h"

//Wszystkie dane jakie mog¹ p³yn¹æ z objektu obserwowanego. Te dane bêd¹ wykorzystywane przez widok w celu prezentacji.
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class RemoteObserverData
{
	
	private:

		ObserverType eventType;

		DomainData::Message message;

		DomainData::Address senderAddress;


    public:

        RemoteObserverData();

        virtual ~RemoteObserverData();

		const ObserverType & GetObserverType() const
		{
			return eventType;
		}

		void SetObserverType(const ObserverType & type)
		{
			eventType = type;
		}

		const DomainData::Message & GetSenderMessage() const
		{
			return message;
		}

		void SetSenderMessage(const DomainData::Message & msg)
		{
			message = msg;
		}

		const DomainData::Address & GetSenderAddress() const
		{
			return senderAddress;
		}

		void SetSenderAddress(const DomainData::Address & addr)
		{
			senderAddress = addr;
		}

};  //end class RemoteObserverData

#endif
