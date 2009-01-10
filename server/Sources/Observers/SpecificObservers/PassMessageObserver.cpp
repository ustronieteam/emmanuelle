#include "Observers/PassMessageObserver.h"

PassMessageObserver::PassMessageObserver() 
{
	this->clientsDataBase = boost::shared_ptr<ClientsDataBase>();
}
PassMessageObserver::PassMessageObserver(boost::shared_ptr<ClientsDataBase> & clientsDB)
{
	this->clientsDataBase = clientsDataBase;
}
PassMessageObserver::PassMessageObserver(PassMessageObserver & arg) 
{
    this->clientsDataBase = arg.clientsDataBase;
}
PassMessageObserver & PassMessageObserver::operator =(const PassMessageObserver & arg) 
{
    if (this != &arg)
    {
        this->clientsDataBase = arg.clientsDataBase;
    }
	return *this;
}
PassMessageObserver::~PassMessageObserver() 
{
}

boost::shared_ptr<ClientsDataBase> & PassMessageObserver::get_clientsDataBase() 
{
    return clientsDataBase;
}

void PassMessageObserver::set_clientsDataBase(boost::shared_ptr<ClientsDataBase> & clientsDataBase) 
{
	this->clientsDataBase = clientsDataBase;
}
///@author Marian Szczykulski
///@date 30-12-2008
///@note Obserwator rzadania utworzenia pipe-u od klienta
///@brief Glowna funkcja obserwatora, odpowiedzialna za logike przetwarzania.
///@param[in] Dane obserwatora potrzebne do podejmowania decyzji podczas przetwarzania
///@return ??
int PassMessageObserver::Refresh(RemoteObserverData observerData)
{
	if(observerData.get_eventType()!=SERVER_PASS_MESSAGE)
		return 0; //Odfiltrowanie niechcianych zdarzen
	//Utworz logike watku
	PassMessageObserverLogicRunnable threadLogic(clientsDataBase, observerData);
	//Utworz i uruchom watki
	boost::thread threadPassMessage(threadLogic);
	return 0;
}
///@author Marian Szczykulski
///@date 30-12-2008
///@note Logika watku
///@brief Zawiera logike przetwarzania ktora moze byc uruchomiona w odzielnym watku
///@brief Wiadomosc jest dostarczana do klienta
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
	ClientRecord clientSpecRec;
	try
	{
		clientSpecRec = clientsDataBase->GetRecord(clientId);
	}
	catch(std::exception &exc)
	{
		LOG4CXX_ERROR(logger, "Nie mozna pobrac rekordu z bazy danych klientow. Client ID: " << clientId << ".Powod: "<< exc.what());
		return -2;
	}
	IClientServer_var remoteInstance = clientSpecRec.GetClientRemoteInstance();
	if(CORBA::is_nil(remoteInstance))
	{
		LOG4CXX_DEBUG(logger, "Pozyskiwanie zdalnej instancji servera");
		CORBA::ORB_var orb;
		try
		{
			if(Server::connectToClientServer(clientSpecRec.GetAddress().localization.in(),orb, remoteInstance)==false)
			{
				LOG4CXX_ERROR(logger, "Nie mozna pozyskac zdalnej instancji klienta");
				return -3; //Nie mozna wywolac zdalnej metody
			}
			else
			{
				LOG4CXX_DEBUG(logger, "Pozyskano zdalna instancje klienta");
				clientSpecRec.SetClientRemoteInstance(remoteInstance);
				clientSpecRec.SetBroker(orb);
			}
		}
		catch(CORBA::SystemException & e)
		{
			//TODO Klient rozlaczony (wyslac wiadomosc o disconnect?)
			LOG4CXX_ERROR(logger, "Zlapano wyjatek podczas pozyskiwania zdalnej instancji: "<<e._name());
			return -4;
		}
	}
	try	//    2)Przekaz mu wiadomoœæ
	{
		struct DomainData::Message msg = observerData.getClientMessage();
		struct DomainData::Address senderAddr = observerData.getSenderClientAddress();
		remoteInstance->ReceiveMessage(senderAddr, msg);
	}
	catch(std::exception &exc)
	{
		LOG4CXX_ERROR(logger, "Blad podczas przekazywania wiadomosci do klienta"<< ".Powod: "<< exc.what());
		return -5;
	}
	

	LOG4CXX_INFO(logger, "Koniec przetwarzania logiki PassMessageObserver");
	return 1;
}
