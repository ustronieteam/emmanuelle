#ifndef IMODEL_H
#define IMODEL_H

#include "DataObserver.h"
#include "IRemoteObserver.h"
#include "DomainData.h"
#include "ContactRecord.h"
#include "IServerClient.h"
#include <vector>

class IModel
{

    public:
		
		IModel() 
		{}

        virtual ~IModel()
		{}

		virtual std::string GetOwnName() = 0;
		virtual const long GetOwnNumber() = 0;
		virtual bool GetMyAvailability() = 0;
		
		virtual void SetOwnName(const char * c) = 0;
		virtual void SetOwnNumber(long l) = 0;
		virtual void SetMyAvailability(bool b) = 0;

		virtual void SetServerAddress(const char * addr)=0;
		virtual const DomainData::Address & GetServerAddress() const=0;
		virtual void SetPortNumber(const int & p)=0;
		virtual int GetPortNumber()const=0;

		virtual int RegisterObserver(IRemoteObserver * observ, ObserverType type) = 0 ;
		virtual int UnregisterObserver() = 0;

        virtual int AddStatusObserver(DataObserver * observer) = 0;

        virtual int SendPackage(DomainData::User & usr,DomainData::File & f) = 0;

		virtual int DeleteContact(const DomainData::User & usr) = 0;

		virtual int SendMessageToClient(DomainData::User sender, DomainData::User receiver, DomainData::Message msg)= 0;

        virtual int AddContact(const DomainData::User &usr) = 0;

        virtual int Disconnect() = 0;

        virtual bool ConnectToServer() = 0;

        virtual int AddFileObserver(IRemoteObserver & observer) = 0;

        virtual int AddMessageObserver(IRemoteObserver & observer) = 0;

        virtual  std::vector<ContactRecord> GetContactsList() = 0; 
		virtual bool runStatusChecker() = 0;
		virtual void activateListning() = 0;

		virtual IServerClient_var GetServerInstance() = 0;

		 virtual void TestClient(std::string addrClient) = 0;
		 virtual void setOwnMode(DomainData::Mode m)=0;
		virtual DomainData::Mode getOwnMode()=0;

};  //end class IModel

#endif
