#ifndef IMODEL_H
#define IMODEL_H


#include "DataObserver.h"
#include "FilePackage.h"
#include "IRemoteObserver.h"
#include "DomainData.h"

class IModel
{

    public:

        IModel();

        virtual ~IModel();

		virtual void SetServerAddress(const char * addr)=0;
		virtual const DomainData::Address & GetServerAddress() const=0;
		virtual void SetPortNumber(const int & p)=0;
		virtual int GetPortNumber()const=0;

        virtual int AddStatusObserver(DataObserver & observer) = 0;

        virtual int SendPackage(FilePackage package) = 0;

        virtual int DeleteContact() = 0;

        virtual int SendMessage(DomainData::Address recAddr, DomainData::Message msg)= 0;

        virtual int AddContact() = 0;

        virtual int Disconnect() = 0;

        virtual bool ConnectToServer() = 0;

        virtual int AddFileObserver(IRemoteObserver & observer) = 0;

        virtual int AddMessageObserver(IRemoteObserver & observer) = 0;

        virtual  int GetContactsList() = 0; // TODO: zmienic typ zwracany

};  //end class IModel

#endif
