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
	this->clientsDataBase = clientsDB;
    this->serverDataBase  = servDB;
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
///@author Marian Szczykulski
///@date 02-01-2009
///@note Obserwator wysy³ania wiadomosci przez klienta
///@brief Glowna funkcja obserwatora, odpowiedzialna za logike przetwarzania.
///@param[in] Dane obserwatora potrzebne do podejmowania decyzji podczas przetwarzania
///@return ??
int RemoteClientSendMessageObserver::Refresh(RemoteObserverData observerData)
{
	if(observerData.get_eventType()!=CLIENT_SEND_MESSAGE)
		return 0;
	//Utworz logike watku
	RemoteClientSendMessageObserverLogicRunnable threadLogic(serverDataBase, clientsDataBase, observerData);
	//Utworz i uruchom watki
	boost::thread threadSendMessage(threadLogic);
	return 0;
}
///@author Marian Szczykulski
///@date 02-01-2009
///@note Logika watku
///@brief Zawiera logike przetwarzania ktora moze byc uruchomiona w odzielnym watku
int RemoteClientSendMessageObserverLogicRunnable::operator()()
{
	LOG4CXX_INFO(logger, "Przetwarzanie logiki RemoteClientSendMessageObserver");

	//    1) Znajdz odpowiedniego klienta (adresata)
	struct DomainData::Address clientAddr = observerData.getClientAddress();
	struct DomainData::User usr = observerData.getClientUserData();
	int clientId = clientsDataBase->Find(usr);
	if(clientId<0)
	{
		LOG4CXX_ERROR(logger, "Blad w odnajdowaniu klienta- nie ma go w bazie");
		return -1;
	}
	ClientRecord clRec; //Rekord adresata
	try
	{
		clRec = clientsDataBase->GetRecord(clientId);
		clientAddr = clRec.GetAddress();
	}
	catch(std::exception &exc)
	{
		LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas odszukiwania rekordu klienta. ClientId: "<<clientId<< ".Powod: "<< exc.what());
		return -2;
	}
	//Znajdz serwer do którego jest on podlaczony
	int servId = clRec.GetClientServerId();
	
	// Wyznacz nasz serverId
	struct DomainData::Address localServAddr = Server::GetMyIP();
	int localServerId = serverDataBase->Find(localServAddr);

	LOG4CXX_DEBUG(logger, "LocalId: "<<localServerId<<"ServerId: "<<servId << "Local Addr: "<<localServAddr.localization.in() );
	if(servId == localServerId)
	{//    2) Jezeli jest do nas pod³¹czony przekaz mu wiadomoœæ
		IClientServer_var remoteClientInterface= clRec.GetClientRemoteInstance();
		if(CORBA::is_nil(remoteClientInterface))
		{
			LOG4CXX_DEBUG(logger, "Pozyskiwanie zdalnej instancji klienta: "<<clientAddr.localization.in() );
			CORBA::ORB_var orb;
			try
			{
				IClientServer_var remInstance;
				if(Server::connectToClientServer(clientAddr.localization.in(),orb, remInstance)==false)
				{
						LOG4CXX_ERROR(logger, "Nie mozna pozyskac zdalnej instancji klienta");
						return -3; //Nie mozna wywolac zdalnej metody
				}
				else
				{
						LOG4CXX_DEBUG(logger, "Pozyskano zdalna instancje klienta");
						clRec.SetClientRemoteInstance(remoteClientInterface);
						clRec.SetBroker(orb);
						remoteClientInterface = remInstance;
				}
			}
			catch(CORBA::SystemException & e)
			{
				LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas pozyskiwania zdalnej instancji klienta: "<<e._name() << ": " << e._to_string());
				return -4;
			}
		}//Zdalna instancje klienta pobrano
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
	{//    3) Je¿eli nie jest to wykonaj PassMessage na serwerze do którego jest pod³¹czony
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
		if(CORBA::is_nil(remoteInstance))//Pozyskiwanie zdalnej instancji
		{
			LOG4CXX_DEBUG(logger, "Pozyskiwanie zdalnej instancji serwera");
			CORBA::ORB_var orb;
			try
			{
				if(Server::connectToServerServer(remoteServRecord.GetAddress().localization.in(), orb, remoteInstance)==false)
				{
					LOG4CXX_ERROR(logger, "Nie mozna pozyskac zdalnej instancji servera");
					return -4; //Nie mozna wywolac zdalnej metody
				}
				else
				{
					LOG4CXX_DEBUG(logger, "Pozyskano zdalna instancje servera");
					remoteServRecord.SetServerRemoteInstance(remoteInstance);
					remoteServRecord.SetBroker(orb);
				}
			}
			catch(CORBA::SystemException & e)
			{
				LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas pozyskiwania zdalnej instancji klienta: "<<e._name());
				return -5;
			}

		}//Zdalna instancja jest pozyskana
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
