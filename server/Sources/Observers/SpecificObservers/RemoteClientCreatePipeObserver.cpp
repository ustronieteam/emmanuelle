#include "Observers/RemoteClientCreatePipeObserver.h"

RemoteClientCreatePipeObserver::RemoteClientCreatePipeObserver() 
{
    this->clientsDataBase  = boost::shared_ptr<ClientsDataBase>();
    this->serverDataBase  = boost::shared_ptr<ServerDataBase>();
}
RemoteClientCreatePipeObserver::RemoteClientCreatePipeObserver(boost::shared_ptr<ServerDataBase> & servDB, boost::shared_ptr<ClientsDataBase> & clientsDB)
{
	this->clientsDataBase = clientsDataBase;
    this->serverDataBase  = serverDataBase;
}

RemoteClientCreatePipeObserver::RemoteClientCreatePipeObserver(RemoteClientCreatePipeObserver & arg) 
{
    
    this->clientsDataBase = arg.clientsDataBase;
    this->serverDataBase = arg.serverDataBase;
}


RemoteClientCreatePipeObserver & RemoteClientCreatePipeObserver::operator =(const RemoteClientCreatePipeObserver & arg) 
{
    
    if (this != &arg)
    {
        this->clientsDataBase = arg.clientsDataBase;
        this->serverDataBase = arg.serverDataBase;
    }
	return *this;
}


RemoteClientCreatePipeObserver::~RemoteClientCreatePipeObserver() 
{
    
}


boost::shared_ptr<ClientsDataBase> & RemoteClientCreatePipeObserver::get_clientsDataBase() 
{
    
    return clientsDataBase;
}


void RemoteClientCreatePipeObserver::set_clientsDataBase(boost::shared_ptr<ClientsDataBase> & clientsDataBase) 
{
    this->clientsDataBase = clientsDataBase;
}


boost::shared_ptr<ServerDataBase> & RemoteClientCreatePipeObserver::get_serverDataBase() 
{
    
    return serverDataBase;
}


void RemoteClientCreatePipeObserver::set_serverDataBase(boost::shared_ptr<ServerDataBase> & serverDataBase) 
{
    this->serverDataBase = serverDataBase;
}

///
///@author Marian Szczykulski
///@date 30-12-2008
///@note Obserwator rzadania utworzenia pipe-u
///@brief Glowna funkcja obserwatora, odpowiedzialna za logike przetwarzania.
///@param[in] Dane obserwatora potrzebne do podejmowania decyzji podczas przetwarzania
///
int RemoteClientCreatePipeObserver::Refresh(RemoteObserverData observerData)
{
	if(observerData.get_eventType()!=CLIENT_CREATE_PIPE_REQUEST)
		return 0; 
	//Utworz logike watku
	RemoteClientCreatePipeObserverLogicRunnable threadLogic(serverDataBase ,clientsDataBase, observerData);
	//Utworz i uruchom watki
	boost::thread threadClCreatePipe(threadLogic);
	return 0;
}
///
///@author Marian Szczykulski
///@date 30-12-2008
///@note Logika watku
///@brief Zawiera logike przetwarzania ktora moze byc uruchomiona w odzielnym watku
///
int RemoteClientCreatePipeObserverLogicRunnable::operator()()
{
	LOG4CXX_INFO(logger, "Przetwarzanie logiki RemoteClientCreatePipeObserver");

	//    1) Znajdz w bazie o klientach, takiego który nie blokuje po³¹czeñ przychodz¹cych i jest pod³¹czony
	//    z aktualnym serwerem i przekaz mu odpowiedni komunikat o tworzeniu pipe'u
	int localServId = 0;// = serverDataBase->getLocalServerId();
	// TODO: cos zrobic
	struct DomainData::User clientData = observerData.getClientUserData();
	int clientId = clientsDataBase->FindActiveClientOnServer(localServId);
	if(clientId>0)
	{
		ClientRecord clSpecRec;
		try
		{
			clSpecRec = clientsDataBase->GetRecord(clientId);
		}
		catch(std::exception &exc)
		{
			LOG4CXX_ERROR(logger, "Nie udalo sie pobrac rekordu z klienta z bazy"<< ".Powod: "<< exc.what());
			return -1;
		}
		struct DomainData::User pipeHolderData= clSpecRec.GetUser();
		IClientServer_var remoteInstance = clSpecRec.GetClientRemoteInstance();

		try
		{
			struct DomainData::User senderData = observerData.getSenderClientData();
			remoteInstance->CreatePipeRequest(pipeHolderData, senderData);
			LOG4CXX_INFO(logger, "Przekazano komunikat o utworzeniu pipe-u");
		}
		catch(std::exception &exc)
		{
			LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas przekazywania do klienta komunikatu o tworzeniu pipe-u"<< ".Powod: "<< exc.what());
			return -2;
		}
	}
	else
	{	//    2) Je¿eli takiego nie ma to znajdŸ takiego który jest pod³¹czony do innego serwera i przeka¿ temu serwerowi
		//    odpowiedni komunikat (PassCreatePipe?)

		//Wyszukaj dowolnego nie blokujacego
		int clientId2 = 0;//clientsDataBase->FindActiveClient();
		if(clientId2<=0)
		{
			LOG4CXX_INFO(logger, "Nie odnaleziono zadnego pasujacego rekordu");
			return -4;//To nie jest do konca blad. Taki pryzpadek jest moyliwz
		}
		ClientRecord clSpecRec2 ;
		try
		{
			clSpecRec2 = clientsDataBase->GetRecord(clientId2);
		}
		catch(std::exception &exc)
		{
			LOG4CXX_ERROR(logger, "Blad podczas pobierania rekordu z bazy klientow"<< ".Powod: "<< exc.what());
			return -5;
		}
		int conServId = clSpecRec2.GetClientServerId();
		if(conServId <=0)
		{
			LOG4CXX_ERROR(logger, "Blad podczas identyfikacji klienta z serverem");
			return -6;
		}
		ServerRecord servSpecRec = serverDataBase->GetRecord(conServId);
		IServerServer_var remInstance = servSpecRec.GetServerRemoteInstance();
		try
		{
			struct DomainData::User pipeHolder = observerData.getPipeHolderData();  
			struct DomainData::User senderAddr = observerData.getSenderClientData();
			struct DomainData::User recAddr = observerData.getDestinationUser();
			remInstance->PassCreatePipeRequest(pipeHolder,senderAddr,recAddr);
		}
		catch(std::exception &exc)
		{
			LOG4CXX_ERROR(logger, "Blad podczas przekazywania wiadomosci o tworzeniu pipe-u do zdalnego serwera"<< ".Powod: "<< exc.what());
			return -7;
		}

	}

	LOG4CXX_INFO(logger, "Koniec przetwarzania logiki RemoteClientCreatePipeObserver");
	return 1;
}
