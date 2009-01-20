#include "RemoteClientDisconnectedObserverTest.h"
//extern ServerDataBase * sdb_gl;
//extern boost::shared_ptr<ServerDataBase> ptr_sdb_gl;
//
//extern ClientsDataBase * cdb_gl;
//extern boost::shared_ptr<ClientsDataBase> ptr_cdb_gl;
void test_case_clientDisconnected_1()
{
	boost::shared_ptr<ServerDataBase> ptr_sdb_gl=ServerDataBase::GetInstnace();
	boost::shared_ptr<ClientsDataBase> ptr_cdb_gl=ClientsDataBase::GetInstnace();
	
	ServerDataBase * sdb_gl = ptr_sdb_gl.get();
	ClientsDataBase * cdb_gl = ptr_cdb_gl.get();

	BOOST_TEST_MESSAGE("********** TEST OGOLNY RemoteClientDisconnectedObserver...");
	RemoteClientDisconnectedObserver rcdo;
	BOOST_TEST_MESSAGE("* Konstruktor domyslny...");
	BOOST_WARN((const int)rcdo.get_serverDataBase().get()==NULL);

	boost::shared_ptr<ServerDataBase> ptr_sdb(ptr_sdb_gl);
	rcdo.set_serverDataBase(ptr_sdb);
	BOOST_TEST_MESSAGE("* Ustawienie bazy danych serwerow...");
	BOOST_CHECK_EQUAL(rcdo.get_serverDataBase().get(), sdb_gl);

	boost::shared_ptr<ClientsDataBase> ptr_cdb(ptr_cdb_gl);
	rcdo.set_clientsDataBase(ptr_cdb);
	BOOST_TEST_MESSAGE("* Ustawienie bazy danych klientow...");
	BOOST_CHECK_EQUAL(rcdo.get_clientsDataBase().get(), cdb_gl);

	BOOST_TEST_MESSAGE("* Konstruktor kopiujacy...");
	RemoteClientDisconnectedObserver rcdo2(rcdo);
	BOOST_REQUIRE(rcdo2.get_serverDataBase().get()==sdb_gl);
	BOOST_REQUIRE(rcdo2.get_clientsDataBase().get()==cdb_gl);

	BOOST_TEST_MESSAGE("* Konstruktor jedno argumentowy...");
	//ServerDataBase * sdb2 = ServerDataBase::GetInstance();
	boost::shared_ptr<ServerDataBase> ptr_sdb2(ptr_sdb_gl);
	//ClientsDataBase * cdb2 = ClientsDataBase::GetInstance();
	boost::shared_ptr<ClientsDataBase> ptr_cdb2(ptr_cdb_gl);
	RemoteClientDisconnectedObserver rcdo3(ptr_sdb2,ptr_cdb2);
	BOOST_WARN(rcdo3.get_serverDataBase().get()==sdb_gl);
	BOOST_WARN(rcdo3.get_clientsDataBase().get()==cdb_gl);
	ptr_sdb_gl->Clear();
	BOOST_TEST_MESSAGE("* Operator przypisania...");
	rcdo3=rcdo;
	BOOST_WARN(rcdo3.get_serverDataBase().get()==sdb_gl);
	BOOST_WARN(rcdo3.get_clientsDataBase().get()==cdb_gl);
	BOOST_TEST_MESSAGE("********** Koniec TESTU OGOLNEGO RemoteClientDisconnectedObserver");
}
void test_case_clientDisconnected_2()
{
	boost::shared_ptr<ServerDataBase> ptr_sdb_gl=ServerDataBase::GetInstnace();

	boost::shared_ptr<ClientsDataBase> ptr_cdb_gl=ClientsDataBase::GetInstnace();
	
	ServerDataBase * sdb_gl = ptr_sdb_gl.get();
	ClientsDataBase * cdb_gl = ptr_cdb_gl.get();

	BOOST_TEST_MESSAGE("********** TEST LOGIKI RemoteClientDisconnectedObserver...");
	boost::shared_ptr<ServerDataBase> ptr_sdb(ptr_sdb_gl);
	ptr_sdb->Clear();
	boost::shared_ptr<ClientsDataBase> ptr_cdb(ptr_cdb_gl);
	ptr_cdb->Clear();
	
	RemoteObserverData observerData;
	RemoteClientDisconnectedObserverLogicRunnable rcdolr(ptr_sdb,ptr_cdb, observerData);
	BOOST_TEST_MESSAGE("* Baza klientow jest pusta");
	BOOST_CHECK_EQUAL(rcdolr(), -1);
	//------
	BOOST_TEST_MESSAGE("* Baza klientow jest nie pusta");
	ClientRecord cr;
	DomainData::Address addr;
	addr.localization = CORBA::string_dup("addr");
	cr.SetAddress(addr);
	ptr_cdb->InsertRecord(cr);
	BOOST_CHECK_EQUAL(rcdolr(), -2);
	//----
	BOOST_TEST_MESSAGE("* Baza serverow zawiera adres lokalnego serwera");
	DomainData::Address myAddr;
	addr.localization = CORBA::string_dup("myAddr");
	Server * serv = Server::GetInstance("plik.txt");
	serv->SetMyIP(myAddr);
	ServerRecord sr;
	sr.SetAddress(myAddr);
	ptr_sdb->InsertRecord(sr);
	BOOST_CHECK_EQUAL(rcdolr(), 0);


	BOOST_TEST_MESSAGE("********** Koniec TESTU LOGIKI RemoteClientDisconnectedObserver");
}