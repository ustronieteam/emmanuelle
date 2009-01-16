#include "Observers/ServerCreatePipeObserver.h"

ServerCreatePipeObserver::ServerCreatePipeObserver() 
{
	this->clientsDataBase = boost::shared_ptr<ClientsDataBase>();
}


ServerCreatePipeObserver::ServerCreatePipeObserver(ServerCreatePipeObserver & arg) 
{
    this->clientsDataBase = arg.clientsDataBase;
}

ServerCreatePipeObserver::ServerCreatePipeObserver(boost::shared_ptr<ClientsDataBase> & clntDB) 
{
	 this->clientsDataBase = clntDB;
}


ServerCreatePipeObserver & ServerCreatePipeObserver::operator =(const ServerCreatePipeObserver & arg) 
{
    
    if (this != &arg)
    {
        this->clientsDataBase = arg.clientsDataBase;
    }
	return *this;
}


ServerCreatePipeObserver::~ServerCreatePipeObserver() 
{
    
}


boost::shared_ptr<ClientsDataBase> & ServerCreatePipeObserver::get_clientsDataBase() 
{
    
    return clientsDataBase;
}


void ServerCreatePipeObserver::set_clientsDataBase(boost::shared_ptr<ClientsDataBase> & clientsDataBase) 
{
	this->clientsDataBase = clientsDataBase;
}

///
///@author Marian Szczykulski
///@date 02-01-2009
///@note Obserwator zlecenie od innego servera do utworzenia pipe na jakims kliencie(ktory jest do nas podlaczony)
///@brief Glowna funkcja obserwatora, odpowiedzialna za logike przetwarzania.
///@param[in] Dane obserwatora potrzebne do podejmowania decyzji podczas przetwarzania
///
int ServerCreatePipeObserver::Refresh(RemoteObserverData observerData)
{
	if(observerData.get_eventType()!=SERVER_CREATE_PIPE_REQUEST)
		return 0;
	//Utworz logike watku
	ServerCreatePipeObserverLogicRunnable threadLogic(clientsDataBase, observerData);
	//Utworz i uruchom watki
	boost::thread threadServCreatePipe(threadLogic);
	return 0;
}

///
///@author Marian Szczykulski
///@date 02-01-2009
///@note Logika watku
///@brief Zawiera logike przetwarzania ktora moze byc uruchomiona w odzielnym watku
///
int ServerCreatePipeObserverLogicRunnable::operator()()
{
	LOG4CXX_INFO(logger, "Przetwarzanie logiki ServerCreatePipeObserverLogicRunnable");

	//    1)Klientowi który ma tworzyæ pipe przeka¿ odpowiedni¹ wiadomoœæ.
	//Klient ten musi byæ z nami pod³¹czony, je¿eli nie to b³ad integralnoœci danych w bazie.
	struct DomainData::User clientData = observerData.getClientUserData();
	int clientId = clientsDataBase->Find(clientData);
	if(clientId<=0)
	{
		LOG4CXX_ERROR(logger, "Blad podczas odnaidywania id klienta w bazie");
		return -1;
	}
	ClientRecord clientSpecRec;
	try
	{
		clientSpecRec = clientsDataBase->GetRecord(clientId);
	}
	catch(std::exception &exc)
	{
		LOG4CXX_ERROR(logger, "Blad podczas pobierania rekordu z bazy. Klient Id: "<<clientId<< ".Powod: "<< exc.what());
		return -2;
	}
	try
	{
		struct DomainData::User pipeHolder = observerData.getPipeHolderData();
		struct DomainData::User senderData = observerData.getSenderClientData();
		IClientServer_var remoteInstance = clientSpecRec.GetClientRemoteInstance();
		remoteInstance->CreatePipeRequest(pipeHolder, senderData);
	}
	catch(std::exception &exc)
	{
		LOG4CXX_ERROR(logger, "Nie udalo sie wyslac zadania o utworzenie pipe-u do klienta"<< ".Powod: "<< exc.what());
		return -3;
	}
	LOG4CXX_INFO(logger, "Koniec przetwarzania logiki ServerCreatePipeObserverLogicRunnable");
	return 1;
}
