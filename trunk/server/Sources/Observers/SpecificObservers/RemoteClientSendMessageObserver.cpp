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
//@note Obserwator wysy³ania wiadomosci przez klienta
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
	int clientId = clientsDataBase->Find(/*Dane z observerData*/);
	if(clientId<0)
	{
		LOG4CXX_ERROR(logger, "Blad w odnajdowaniu klienta- nie ma go w bazie");
		return -1;
	}
	Record clientRec;
	try
	{
		clientRec = clientsDataBase->GetRecord(clientId);
	}
	catch(std::exception &exc)
	{
		LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas odszukiwania rekordu klienta. ClientId: "<<clientId);
		return -2;
	}
	//Znajdz serwer do którego jest on podlaczony (trzeba rzutowaæ)
	ClientRecord clRec = *(dynamic_cast<ClientRecord *>(&clientRec));//Pomyslec o przechwytywaniu tu wyjatku bad_cast??
	int servId = clRec.getConnectedServerId();
	
	// Wyznacz nasz serverId
	int localServerId = serverDataBase->getLocalServerId();

	
	if(servId == localServerId)
	{//    2) Jezeli jest do nas pod³¹czony przekaz mu wiadomoœæ
		IClientServer remoteClientInterface= clRec.getRemoteInstance();
		try
		{
			remoteClientInterface.ReceiveMessage(/*wiadomosc z observerData*/);
			LOG4CXX_INFO(logger, "Wiadomosc przekazana pomyslnie");
		}
		catch(std::exception &exc)
		{
			LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas przekazywania wiadomosci do klienta");
			return -3;
		}
	}
	else
	{//    3) Je¿eli nie jest to wykonaj PassMessage na serwerze do którego jest pod³¹czony
		Record remoteRecord;
		try
		{
			remoteRecord = serverDataBase->GetRecord(servId);
		}
		catch(std::exception &exc)
		{
			LOG4CXX_ERROR(logger, "Blad podczas pobierania rekordu z bazy serwerow");
			return -5;
		}
		ServerRecord remoteServRecord = *(dynamic_cast<ServerRecord *>(&remoteRecord));
		IServerServer remoteInstance = remoteServRecord.getRemoteInstance();
		try
		{
			remoteInstance.PassMessage(/*Wiadomosc z observerData*/);
			LOG4CXX_INFO(logger, "Wiadomosc przekazana pomyslnie na inny server");
		}
		catch(std::exception &exc)
		{
			LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas przekazywania wiadomosci na inny serwer");
			return -4;
		}
	}

	LOG4CXX_INFO(logger, "Koniec przetwarzania logiki RemoteClientSendMessageObserver");
	return 1;
}
