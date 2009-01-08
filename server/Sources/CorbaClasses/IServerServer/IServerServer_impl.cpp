#include <IServerServer_impl.h>
#include <Server.h>

//
// IDL:IServerServer:1.0
//
IServerServer_impl::IServerServer_impl(PortableServer::POA_ptr poa)
    : poa_(PortableServer::POA::_duplicate(poa))
{
}

IServerServer_impl::~IServerServer_impl()
{
}

PortableServer::POA_ptr
IServerServer_impl::_default_POA()
{
    return PortableServer::POA::_duplicate(poa_);
}

//
// IDL:IServerServer/Join:1.0
//
::AddressesList*
IServerServer_impl::Join(const ::DomainData::Address& serverAddress)
    throw(::CORBA::SystemException)
{
	std::cout << "WYWOLANIE JOIN z adresu: " << Server::GetRemotedAddress() << std::endl;

	//pobranie instancji bazy danych
	ServerDataBase * serverDB = ServerDataBase::GetInstance();

	// dodanie nowego serwera do bazy danych
	DomainData::Address addr;
	addr.localization = CORBA::string_dup( Server::GetRemotedAddress() );
	this->AddServer(addr);
	/*
	ServerRecord * record = new ServerRecord();
	// TODO: dodac dane
	serverDB->InsertRecord(*record);
   */

	//pobranie wszystkich rekordow z bazy danych serwera
	std::vector<ServerRecord> & serversList = serverDB->GetAllRecords();

	if(serversList.size() == 1)
	{
		// w bazie nei bylo jeszcze adresu serwera mecierzystego a wiec trzeba go dodac
		this->AddServer(serverAddress);
		/*
		ServerRecord * mRecord = new ServerRecord();
		// TODO: dodac dane
		serverDB->InsertRecord(*mRecord);
		*/

		// dolozenie do kolekcji serwerow tego ktory przed chwila zostal dodany
		serversList = serverDB->GetAllRecords();
		// serversList.push_back(*mRecord);
	}

	// stworzenie obiektu z danymi dla obserwatora
	RemoteObserverData observData;
	observData.set_eventType(SERVER_CONNECTED);
	
	DomainData::Address adres;
	adres.localization = Server::GetRemotedAddress();
	
	observData.setServerAddress(adres);

	// wywolanie notify() na obserwatorach (jesli dany obserwator w kolekcji obserwatorow
	// bedzie zobowiazany do zareagowania na zdarzenie to to zrobi)
	this->Notify(observData);

	// utworzenie listy typu AddressList i przepisanie danych uzyskanych z bazy
	AddressesList * _r =  new  AddressesList();
	_r->length(serversList.size());
	
	for(unsigned int i = 0; i < serversList.size(); ++i)
		(*_r)[i] = serversList[i].GetAddress();

    return _r;
}

//
// IDL:IServerServer/Unjoin:1.0
//
void
IServerServer_impl::Unjoin()
    throw(::CORBA::SystemException)
{
    // adres serwera do usuniecia
	DomainData::Address addr;
	addr.localization = CORBA::string_dup(Server::GetRemotedAddress());

	this->RemoveServer(addr);

	/*
	// wydobycie z bazy rekordu dla tego serwera
	int recordId;
	if((recordId = ServerDataBase::GetInstance()->Find(addr)) < 0)
		return;

	ServerDataBase::GetInstance()->DeleteRecord(recordId);
	*/

	// stworzenie obiektu z danymi dla obserwatora
	RemoteObserverData observData;
	observData.set_eventType(SERVER_DISCONNECTED);
	observData.setServerAddress(addr); // ??? czy napewno??

	this->Notify(observData);
}

//
// IDL:IServerServer/AddServer:1.0
//
void
IServerServer_impl::AddServer(const ::DomainData::Address& serverAddress)
    throw(::CORBA::SystemException)
{
	ServerRecord record;
	record.SetAddress(serverAddress);

	try
	{
		ServerDataBase::GetInstance()->InsertRecord(record);
	}
	catch(std::exception &)
	{}
}

//
// IDL:IServerServer/RemoveServer:1.0
//
void
IServerServer_impl::RemoveServer(const ::DomainData::Address& serverAddress)
    throw(::CORBA::SystemException)
{
	// wydobycie z bazy rekordu dla tego serwera
	int recordId;
	if((recordId = ServerDataBase::GetInstance()->Find(const_cast<DomainData::Address&>(serverAddress))) < 0)
		return;

	//usuniecie rekordu
	try
	{
		ServerDataBase::GetInstance()->DeleteRecord(recordId);
	}
	catch(std::exception &)
	{}
}

//
// IDL:IServerServer/PassMessage:1.0
//
void
IServerServer_impl::PassMessage(const ::DomainData::Message& msg,
                                const ::DomainData::Address& senderAddress,
                                const ::DomainData::Address& receiverAddress)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:IServerServer/PassCreatePipeRequest:1.0
//
void
IServerServer_impl::PassCreatePipeRequest(const ::DomainData::Address& pipeHolderAddress,
                                          const ::DomainData::Address& senderAddress,
                                          const ::DomainData::Address& receiverAddress)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}

//
// IDL:IServerServer/ClientStatusChanged:1.0
//
void
IServerServer_impl::ClientStatusChanged(const ::DomainData::Address& clientAddress,
                                        const ::DomainData::Enability& en)
    throw(::CORBA::SystemException)
{
    // TODO: Implementation
}
