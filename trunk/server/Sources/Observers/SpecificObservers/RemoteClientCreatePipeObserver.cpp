#include "Observers/RemoteClientCreatePipeObserver.h"
//Begin section for file RemoteClientCreatePipeObserver.cpp
//TODO: Add definitions that you want preserved
//End section for file RemoteClientCreatePipeObserver.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
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
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientCreatePipeObserver::RemoteClientCreatePipeObserver(RemoteClientCreatePipeObserver & arg) 
{
    //TODO Auto-generated method stub
    this->clientsDataBase = arg.clientsDataBase;
    this->serverDataBase = arg.serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteClientCreatePipeObserver & RemoteClientCreatePipeObserver::operator =(const RemoteClientCreatePipeObserver & arg) 
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
RemoteClientCreatePipeObserver::~RemoteClientCreatePipeObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
boost::shared_ptr<ClientsDataBase> & RemoteClientCreatePipeObserver::get_clientsDataBase() 
{
    //TODO Auto-generated method stub
    return clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteClientCreatePipeObserver::set_clientsDataBase(boost::shared_ptr<ClientsDataBase> & clientsDataBase) 
{
    this->clientsDataBase = clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
boost::shared_ptr<ServerDataBase> & RemoteClientCreatePipeObserver::get_serverDataBase() 
{
    //TODO Auto-generated method stub
    return serverDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteClientCreatePipeObserver::set_serverDataBase(boost::shared_ptr<ServerDataBase> & serverDataBase) 
{
    this->serverDataBase = serverDataBase;
}
//@author Marian Szczykulski
//@date 30-12-2008
//@note Obserwator rzadania utworzenia pipe-u
//@brief Glowna funkcja obserwatora, odpowiedzialna za logike przetwarzania.
//@param[in] Dane obserwatora potrzebne do podejmowania decyzji podczas przetwarzania
//@return ??
int RemoteClientCreatePipeObserver::Refresh(RemoteObserverData observerData)
{
	//Utworz logike watku
	RemoteClientCreatePipeObserverLogicRunnable threadLogic(serverDataBase ,clientsDataBase, observerData);
	//Utworz i uruchom watki
	boost::thread threadClCreatePipe(threadLogic);
	return 0;
}
//@author Marian Szczykulski
//@date 30-12-2008
//@note Logika watku
//@brief Zawiera logike przetwarzania ktora moze byc uruchomiona w odzielnym watku
int RemoteClientCreatePipeObserverLogicRunnable::operator()()
{
	LOG4CXX_INFO(logger, "Przetwarzanie logiki RemoteClientCreatePipeObserver");

	//    1) Znajdz w bazie o klientach, takiego który nie blokuje po³¹czeñ przychodz¹cych i jest pod³¹czony
	//    z aktualnym serwerem i przekaz mu odpowiedni komunikat o tworzeniu pipe'u
	int localServId;// = serverDataBase->getLocalServerId();
	struct DomainData::Address clientAddr = observerData.getClientAddress();
	int clientId = clientsDataBase->Find(clientAddr); //Byc moze trzeba wywolac inna funkcjie
	if(clientId>0)
	{
		Record clRec;
		try
		{
			clRec = clientsDataBase->GetRecord(clientId);
		}
		catch(std::exception &exc)
		{
			LOG4CXX_ERROR(logger, "Nie udalo sie pobrac rekordu z klienta z bazy");
			return -1;
		}
		ClientRecord clSpecRec = *(dynamic_cast<ClientRecord *>(&clRec));
		struct DomainData::Address pipeHolderAddr = clSpecRec.GetAddress();
		IClientServer_var remoteInstance = clSpecRec.GetClientRemoteInstance();

		try
		{
			struct DomainData::Address senderAddr = observerData.getSenderClientAddress();
			remoteInstance->CreatePipeRequest(pipeHolderAddr, senderAddr);
			LOG4CXX_INFO(logger, "Przekazano komunikat o utworzeniu pipe-u");
		}
		catch(std::exception &exc)
		{
			LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas przekazywania do klienta komunikatu o tworzeniu pipe-u");
			return -2;
		}
	}
	else
	{	//    2) Je¿eli takiego nie ma to znajdŸ takiego który jest pod³¹czony do innego serwera i przeka¿ temu serwerowi
		//    odpowiedni komunikat (PassCreatePipe?)

		//Wyszukaj dowolnego nie blokujacego
		int clientId2 = clientsDataBase->Find(clientAddr/*nie blokujacy*/); //Byc moze trzeba wywolac inna funkcjie
		if(clientId2<=0)
		{
			LOG4CXX_INFO(logger, "Nie odnaleziono zadnego pasujacego rekordu");
			return -4;//To nie jest do konca blad. Taki pryzpadek jest moyliwz
		}
		Record clRec2;
		try
		{
			clRec2 = clientsDataBase->GetRecord(clientId2);
		}
		catch(std::exception &exc)
		{
			LOG4CXX_ERROR(logger, "Blad podczas pobierania rekordu z bazy klientow");
			return -5;
		}
		ClientRecord clSpecRec2 = *(dynamic_cast<ClientRecord *>(&clRec2));
		int conServId = clSpecRec2.GetClientServerId();
		if(conServId <=0)
		{
			LOG4CXX_ERROR(logger, "Blad podczas identyfikacji klienta z serverem");
			return -6;
		}
		Record servRec = serverDataBase->GetRecord(conServId);
		ServerRecord servSpecRec = *(dynamic_cast<ServerRecord *>(&servRec));
		IServerServer_var remInstance = servSpecRec.GetServerRemoteInstance();
		try
		{
			struct DomainData::Address pipeHolder = observerData.getPipeHolderAddress();  
			struct DomainData::Address senderAddr = observerData.getSenderClientAddress();
			struct DomainData::Address recAddr = observerData.getClientAddress();
			remInstance->PassCreatePipeRequest(pipeHolder,senderAddr,recAddr);
		}
		catch(std::exception &exc)
		{
			LOG4CXX_ERROR(logger, "Blad podczas przekazywania wiadomosci o tworzeniu pipe-u do zdalnego serwera");
			return -7;
		}

	}

	LOG4CXX_INFO(logger, "Koniec przetwarzania logiki RemoteClientCreatePipeObserver");
	return 1;
}
