#include "Observers/RemoteClientSendMessageObserver.h"
//Begin section for file RemoteClientSendMessageObserver.cpp
//TODO: Add definitions that you want preserved
//End section for file RemoteClientSendMessageObserver.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientSendMessageObserver::RemoteClientSendMessageObserver() 
{
    this->clientsDataBase  = boost::shared_ptr<ClientsDataBase>();
    this->serverDataBase  = boost::shared_ptr<ServerDataBase>();
}
RemoteClientSendMessageObserver::RemoteClientSendMessageObserver(boost::shared_ptr<ServerDataBase> & servDB, boost::shared_ptr<ClientsDataBase> & clientsDB)
{
	this->clientsDataBase = clientsDataBase;
    this->serverDataBase  = serverDataBase;
}
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientSendMessageObserver::RemoteClientSendMessageObserver(RemoteClientSendMessageObserver & arg) 
{
    //TODO Auto-generated method stub
    this->clientsDataBase = arg.clientsDataBase;
    this->serverDataBase = arg.serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientSendMessageObserver & RemoteClientSendMessageObserver::operator =(const RemoteClientSendMessageObserver & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->clientsDataBase = arg.clientsDataBase;
        this->serverDataBase = arg.serverDataBase;
    }
	return *this;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientSendMessageObserver::~RemoteClientSendMessageObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
boost::shared_ptr<ClientsDataBase> & RemoteClientSendMessageObserver::get_clientsDataBase() 
{
    //TODO Auto-generated method stub
    return clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteClientSendMessageObserver::set_clientsDataBase(boost::shared_ptr<ClientsDataBase> & clientsDataBase) 
{
	this->clientsDataBase = clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
boost::shared_ptr<ServerDataBase> & RemoteClientSendMessageObserver::get_serverDataBase() 
{
    //TODO Auto-generated method stub
    return serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteClientSendMessageObserver::set_serverDataBase(boost::shared_ptr<ServerDataBase> & serverDataBase) 
{
	this->serverDataBase = serverDataBase;
}
//@author Marian Szczykulski
//@date 02-01-2009
//@note Obserwator wysy�ania wiadomosci przez klienta
//@brief Glowna funkcja obserwatora, odpowiedzialna za logike przetwarzania.
//@param[in] Dane obserwatora potrzebne do podejmowania decyzji podczas przetwarzania
//@return ??
int RemoteClientSendMessageObserver::Refresh(RemoteObserverData observerData)
{
	//Utworz logike watku
	RemoteClientSendMessageObserverLogicRunnable threadLogic(serverDataBase, clientsDataBase, observerData);
	//Utworz i uruchom watki
	boost::thread threadSendMessage(threadLogic);
	return 0;
}
//@author Marian Szczykulski
//@date 02-01-2009
//@note Logika watku
//@brief Zawiera logike przetwarzania ktora moze byc uruchomiona w odzielnym watku
int RemoteClientSendMessageObserverLogicRunnable::operator()()
{
	LOG4CXX_INFO(logger, "Przetwarzanie logiki RemoteClientSendMessageObserver");

	//    1) Znajdz odpowiedniego klienta (adresata)
	struct DomainData::Address clientAddr = observerData.getClientAddress();
	int clientId = clientsDataBase->Find(clientAddr/*Dane z observerData*/);
	if(clientId<0)
	{
		LOG4CXX_ERROR(logger, "Blad w odnajdowaniu klienta- nie ma go w bazie");
		return -1;
	}
	ClientRecord clRec;
	try
	{
		clRec = clientsDataBase->GetRecord(clientId);
	}
	catch(std::exception &exc)
	{
		LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas odszukiwania rekordu klienta. ClientId: "<<clientId<< ".Powod: "<< exc.what());
		return -2;
	}
	//Znajdz serwer do kt�rego jest on podlaczony (trzeba rzutowa�)
	int servId = clRec.GetClientServerId();
	
	// Wyznacz nasz serverId
	int localServerId ;//= serverDataBase->getLocalServerId();

	
	if(servId == localServerId)
	{//    2) Jezeli jest do nas pod��czony przekaz mu wiadomo��
		IClientServer_var remoteClientInterface= clRec.GetClientRemoteInstance();
		try
		{
			struct DomainData::Address senderAddr = observerData.getSenderClientAddress();
			struct DomainData::Message msg = observerData.getClientMessage();
			remoteClientInterface->ReceiveMessage(senderAddr, msg);
			LOG4CXX_INFO(logger, "Wiadomosc przekazana pomyslnie");
		}
		catch(std::exception &exc)
		{
			LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas przekazywania wiadomosci do klienta"<< ".Powod: "<< exc.what());
			return -3;
		}
	}
	else
	{//    3) Je�eli nie jest to wykonaj PassMessage na serwerze do kt�rego jest pod��czony
		ServerRecord remoteServRecord;
		try
		{
			remoteServRecord = serverDataBase->GetRecord(servId);
		}
		catch(std::exception &exc)
		{
			LOG4CXX_ERROR(logger, "Blad podczas pobierania rekordu z bazy serwerow"<< ".Powod: "<< exc.what());
			return -5;
		}
		IServerServer_var remoteInstance = remoteServRecord.GetServerRemoteInstance();
		try
		{
			struct DomainData::Address senderAddr = observerData.getSenderClientAddress();
			struct DomainData::Message msg = observerData.getClientMessage();
			struct DomainData::Address recAddr = observerData.getClientAddress();
			remoteInstance->PassMessage(msg, senderAddr, recAddr);
			LOG4CXX_INFO(logger, "Wiadomosc przekazana pomyslnie na inny server");
		}
		catch(std::exception &exc)
		{
			LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas przekazywania wiadomosci na inny serwer"<< ".Powod: "<< exc.what());
			return -4;
		}
	}

	LOG4CXX_INFO(logger, "Koniec przetwarzania logiki RemoteClientSendMessageObserver");
	return 1;
}
