#include "Observers/PassMessageObserver.h"
//Begin section for file PassMessageObserver.cpp
//TODO: Add definitions that you want preserved
//End section for file PassMessageObserver.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
PassMessageObserver::PassMessageObserver() 
{
	this->clientsDataBase = boost::shared_ptr<ClientsDataBase>();
}
PassMessageObserver::PassMessageObserver(boost::shared_ptr<ClientsDataBase> & clientsDB)
{
	this->clientsDataBase = clientsDataBase;
}
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
PassMessageObserver::PassMessageObserver(PassMessageObserver & arg) 
{
    this->clientsDataBase = arg.clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
PassMessageObserver & PassMessageObserver::operator =(const PassMessageObserver & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->clientsDataBase = arg.clientsDataBase;
    }
	return *this;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
PassMessageObserver::~PassMessageObserver() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
boost::shared_ptr<ClientsDataBase> & PassMessageObserver::get_clientsDataBase() 
{
    //TODO Auto-generated method stub
    return clientsDataBase;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void PassMessageObserver::set_clientsDataBase(boost::shared_ptr<ClientsDataBase> & clientsDataBase) 
{
	this->clientsDataBase = clientsDataBase;
}
//@author Marian Szczykulski
//@date 30-12-2008
//@note Obserwator rzadania utworzenia pipe-u od klienta
//@brief Glowna funkcja obserwatora, odpowiedzialna za logike przetwarzania.
//@param[in] Dane obserwatora potrzebne do podejmowania decyzji podczas przetwarzania
//@return ??
int PassMessageObserver::Refresh(RemoteObserverData observerData)
{
	//Utworz logike watku
	PassMessageObserverLogicRunnable threadLogic(clientsDataBase, observerData);
	//Utworz i uruchom watki
	boost::thread threadPassMessage(threadLogic);
	return 0;
}
//@author Marian Szczykulski
//@date 30-12-2008
//@note Logika watku
//@brief Zawiera logike przetwarzania ktora moze byc uruchomiona w odzielnym watku
int PassMessageObserverLogicRunnable::operator()()
{
	LOG4CXX_INFO(logger, "Przetwarzanie logiki PassMessageObserver");

	//    1)Znajdz klienta docelowego(adresata) - musi byc do nas pod³¹czony (Je¿eli nie to b³¹d.)
	struct DomainData::Address clientAddr = observerData.getClientAddress();
	int clientId = clientsDataBase->Find(clientAddr);
	if(clientId <=0)
	{
		LOG4CXX_ERROR(logger, "Nie znaleziono klienta w bazie!!!");
		return -1;
	}
	Record clientRec;
	try
	{
		clientRec = clientsDataBase->GetRecord(clientId);
	}
	catch(std::exception &exc)
	{
		LOG4CXX_ERROR(logger, "Nie mozna pobrac rekordu z bazy danych klientow. Client ID: " << clientId);
		return -2;
	}
	ClientRecord clientSpecRec = *(dynamic_cast<ClientRecord*>(&clientRec));
	IClientServer_var remoteInstance = clientSpecRec.GetClientRemoteInstance();
	try	//    2)Przekaz mu wiadomoœæ
	{
		struct DomainData::Message msg = observerData.getClientMessage();
		struct DomainData::Address senderAddr = observerData.getSenderClientAddress();
		remoteInstance->ReceiveMessage(senderAddr, msg);
	}
	catch(std::exception &exc)
	{
		LOG4CXX_ERROR(logger, "Blad podczas przekazywania wiadomosci do klienta");
		return -3;
	}
	

	LOG4CXX_INFO(logger, "Koniec przetwarzania logiki PassMessageObserver");
	return 1;
}
