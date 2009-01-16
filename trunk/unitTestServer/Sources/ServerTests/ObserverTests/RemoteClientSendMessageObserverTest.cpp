#include "RemoteClientSendMessageObserverTest.h"
#include "testData.h"
extern ServerDataBase * sdb_gl;
extern boost::shared_ptr<ServerDataBase> ptr_sdb_gl;

extern ClientsDataBase * cdb_gl;
extern boost::shared_ptr<ClientsDataBase> ptr_cdb_gl;
void test_case_sendMessage_1()
{
	BOOST_TEST_MESSAGE("* TEST OGOLNY RemoteClientSendMessageObserver...");
	RemoteClientSendMessageObserver rcsmo;
	BOOST_TEST_MESSAGE("* Konstruktor domyslny...");
	BOOST_WARN((const int)rcsmo.get_serverDataBase().get()==NULL);

	boost::shared_ptr<ServerDataBase> ptr_sdb(ptr_sdb_gl);
	rcsmo.set_serverDataBase(ptr_sdb);
	BOOST_TEST_MESSAGE("* Ustawienie bazy danych serwerow...");
	BOOST_CHECK_EQUAL(rcsmo.get_serverDataBase().get(), sdb_gl);

	ClientsDataBase * cdb = ClientsDataBase::GetInstance();
	boost::shared_ptr<ClientsDataBase> ptr_cdb(ptr_cdb_gl);
	rcsmo.set_clientsDataBase(ptr_cdb);
	BOOST_TEST_MESSAGE("* Ustawienie bazy danych klientow...");
	BOOST_CHECK_EQUAL(rcsmo.get_clientsDataBase().get(), cdb_gl);

	BOOST_TEST_MESSAGE("* Konstruktor kopiujacy...");
	RemoteClientSendMessageObserver rcsmo2(rcsmo);
	BOOST_REQUIRE(rcsmo2.get_serverDataBase().get()==sdb_gl);
	BOOST_REQUIRE(rcsmo2.get_clientsDataBase().get()==cdb_gl);

	BOOST_TEST_MESSAGE("* Konstruktor jedno argumentowy...");
	ServerDataBase * sdb2 = ServerDataBase::GetInstance();
	boost::shared_ptr<ServerDataBase> ptr_sdb2(ptr_sdb_gl);
	ClientsDataBase * cdb2 = ClientsDataBase::GetInstance();
	boost::shared_ptr<ClientsDataBase> ptr_cdb2(ptr_cdb_gl);
	RemoteClientSendMessageObserver rcsmo3(ptr_sdb2,ptr_cdb2);
	BOOST_WARN(rcsmo3.get_serverDataBase().get()==sdb_gl);
	BOOST_WARN(rcsmo3.get_clientsDataBase().get()==cdb_gl);

	BOOST_TEST_MESSAGE("* Operator przypisania...");
	rcsmo3=rcsmo;
	BOOST_WARN(rcsmo3.get_serverDataBase().get()==sdb_gl);
	BOOST_WARN(rcsmo3.get_clientsDataBase().get()==cdb_gl);

}
void test_case_sendMessage_2()
{
	BOOST_TEST_MESSAGE("*********** TEST LOGIKI RemoteClientSendMessageObserver...");
	BOOST_TEST_MESSAGE("* Test na pustej bazie");
	boost::shared_ptr<ClientsDataBase> ptr_cdb(ptr_cdb_gl);
	ptr_cdb->Clear();
	boost::shared_ptr<ServerDataBase> ptr_sdb(ptr_sdb_gl);
	ptr_sdb->Clear();
	RemoteObserverData observerData;
	RemoteClientSendMessageObserverLogicRunnable rccolr(ptr_sdb,ptr_cdb,observerData);
	BOOST_CHECK_EQUAL(rccolr(), -1);
	//----
	BOOST_TEST_MESSAGE("* Baza klientow jest nie pusta");
	ClientRecord cr;
	DomainData::Address addr;
	addr.localization = CORBA::string_dup("addr");
	cr.SetAddress(addr);
	ptr_cdb->InsertRecord(cr);
	BOOST_CHECK_EQUAL(rccolr(), -2);
	//----
	BOOST_TEST_MESSAGE("* Baza serverow zawiera adres lokalnego serwera");
	DomainData::Address myAddr;
	addr.localization = CORBA::string_dup("myAddr");
	Server * serv = Server::GetInstance("plik.txt");
	serv->SetMyIP(myAddr);
	ServerRecord sr;
	sr.SetAddress(myAddr);
	ptr_sdb->InsertRecord(sr);
	BOOST_CHECK_EQUAL(rccolr(), 0);
	BOOST_TEST_MESSAGE("******* Koniec TESTU LOGIKI RemoteClientSendMessageObserver...");

}