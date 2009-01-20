#include "RemoteServerConnectedObserverTest.h"

//extern ServerDataBase * sdb_gl;
//extern boost::shared_ptr<ServerDataBase> ptr_sdb_gl;
//
//extern ClientsDataBase * cdb_gl;
//extern boost::shared_ptr<ClientsDataBase> ptr_cdb_gl;
//Przypadki testowe dla RemoteServerConnectedObserver
//Testowanie konstruktorow, operatorow, getterow i setterow
void test_case_1()
{	BOOST_TEST_MESSAGE("*************** TEST OGOLNY RemoteServerConnectedObserver...");
	boost::shared_ptr<ServerDataBase> ptr_sdb_gl(ServerDataBase::GetInstnace());
	boost::shared_ptr<ClientsDataBase> ptr_cdb_gl=ClientsDataBase::GetInstnace();
	ServerDataBase * sdb_gl = ptr_sdb_gl.get();
	ClientsDataBase * cdb_gl = ptr_cdb_gl.get();

	RemoteServerConnectedObserver rsco;
	BOOST_TEST_MESSAGE("* Konstruktor domyslny...");
	BOOST_WARN((const int)rsco.get_serverDataBase().get()==NULL);

	boost::shared_ptr<ServerDataBase> ptr_sdb(ptr_sdb_gl);
	rsco.set_serverDataBase(ptr_sdb);
	BOOST_TEST_MESSAGE("* Ustawienie bazy danych serwerow...");
	BOOST_CHECK_EQUAL(rsco.get_serverDataBase().get(), sdb_gl);


	BOOST_TEST_MESSAGE("* Konstruktor kopiujacy...");
	RemoteServerConnectedObserver rsco2(rsco);
	BOOST_REQUIRE(rsco2.get_serverDataBase().get()==sdb_gl);

	BOOST_TEST_MESSAGE("* Konstruktor jedno argumentowy...");
	boost::shared_ptr<ServerDataBase> ptr_sdb2 = ptr_sdb_gl;;
	RemoteServerConnectedObserver rsco3(ptr_sdb2);
	BOOST_WARN(rsco3.get_serverDataBase().get()==sdb_gl);

	BOOST_TEST_MESSAGE("* Operator przypisania...");
	rsco3=rsco;
	BOOST_WARN(rsco3.get_serverDataBase().get()==sdb_gl);
	BOOST_TEST_MESSAGE("*************** Koniec Testu Ogolnego RemoteServerConnectedObserver");
}
//Przypadki testowe dla RemoteServerConnectedObserver
//Testowanie logiki
void test_case_2()
{
	boost::shared_ptr<ServerDataBase> ptr_sdb_gl=ServerDataBase::GetInstnace();

	boost::shared_ptr<ClientsDataBase> ptr_cdb_gl=ClientsDataBase::GetInstnace();
	
	ServerDataBase * sdb_gl = ptr_sdb_gl.get();
	ClientsDataBase * cdb_gl = ptr_cdb_gl.get();

	BOOST_TEST_MESSAGE("*********** TEST LOGIKI RemoteServerConnectedObserver...");
	RemoteObserverData observerData;
	boost::shared_ptr<ServerDataBase> ptr_sdb(ptr_sdb_gl);
	RemoteServerConnectedObserverLogicRunnable rsco(ptr_sdb,observerData);
	BOOST_TEST_MESSAGE("* Test na pustej bazie");
	BOOST_CHECK_EQUAL(rsco(), -1);
	//BOOST_CHECK_MESSAGE( rsco()==-2, "Zly kod bledu") ;
	//-----------------
	BOOST_TEST_MESSAGE("* Baza zawiera adres nowego serwera(nie ma swojego)");
	ServerRecord sr;
	DomainData::Address addr;
	addr.localization = CORBA::string_dup("addr");
	sr.SetAddress(addr);
	ptr_sdb->InsertRecord(sr);
	observerData.setServerAddress(addr);
	RemoteServerConnectedObserverLogicRunnable rsco2(ptr_sdb,observerData);
	BOOST_CHECK_EQUAL(rsco2(), -2);
	//-------------------
	BOOST_TEST_MESSAGE("* Baza zawiera adres nowego serwera oraz swoj adres");
	DomainData::Address myAddr;
	addr.localization = CORBA::string_dup("myAddr");
	Server * serv = Server::GetInstance("plik.txt");
	serv->SetMyIP(myAddr);
	ServerRecord sr2;
	sr2.SetAddress(myAddr);
	ptr_sdb->InsertRecord(sr2);
	BOOST_CHECK_EQUAL(rsco2(), 0);
}


