#include "PassMessageObserverTest.h"
#include "testData.h"
//extern ServerDataBase * sdb_gl;
//extern boost::shared_ptr<ServerDataBase> ptr_sdb_gl;

//extern ClientsDataBase * cdb_gl;
//extern boost::shared_ptr<ClientsDataBase> ptr_cdb_gl;
void test_case_passMessage_1()
{
	boost::shared_ptr<ServerDataBase> ptr_sdb_gl=ServerDataBase::GetInstnace();

	boost::shared_ptr<ClientsDataBase> ptr_cdb_gl=ClientsDataBase::GetInstnace();
	
	ServerDataBase * sdb_gl = ptr_sdb_gl.get();
	ClientsDataBase * cdb_gl = ptr_cdb_gl.get();

	BOOST_TEST_MESSAGE("* TEST OGOLNY RemoteServerConnectedObserver...");
	PassMessageObserver pmo;
	BOOST_TEST_MESSAGE("* Konstruktor domyslny...");
	BOOST_WARN((const int)pmo.get_clientsDataBase().get()==NULL);

	boost::shared_ptr<ClientsDataBase> ptr_cdb(ptr_cdb_gl);
	pmo.set_clientsDataBase(ptr_cdb);
	BOOST_TEST_MESSAGE("* Ustawienie bazy danych serwerow...");
	BOOST_CHECK_EQUAL(pmo.get_clientsDataBase().get(), cdb_gl);

	BOOST_TEST_MESSAGE("* Konstruktor kopiujacy...");
	PassMessageObserver pmo2(pmo);
	BOOST_REQUIRE(pmo2.get_clientsDataBase().get()==cdb_gl);

	BOOST_TEST_MESSAGE("* Konstruktor jedno argumentowy...");
	ClientsDataBase * cdb2 = ClientsDataBase::GetInstance();
	boost::shared_ptr<ClientsDataBase> ptr_cdb2(ptr_cdb_gl);
	PassMessageObserver pmo3(ptr_cdb2);
	BOOST_WARN(pmo3.get_clientsDataBase().get()==cdb_gl);

	BOOST_TEST_MESSAGE("* Operator przypisania...");
	pmo3=pmo;
	BOOST_WARN(pmo3.get_clientsDataBase().get()==cdb_gl);
}
void test_case_passMessage_2()
{
	boost::shared_ptr<ServerDataBase> ptr_sdb_gl=ServerDataBase::GetInstnace();

	boost::shared_ptr<ClientsDataBase> ptr_cdb_gl=ClientsDataBase::GetInstnace();
	
	ServerDataBase * sdb_gl = ptr_sdb_gl.get();
	ClientsDataBase * cdb_gl = ptr_cdb_gl.get();
	BOOST_TEST_MESSAGE("*********** TEST LOGIKI RemotePassMessageObserver...");
	BOOST_TEST_MESSAGE("* Test na pustej bazie");
	boost::shared_ptr<ClientsDataBase> ptr_cdb(ptr_cdb_gl);
	ptr_cdb->Clear();
	boost::shared_ptr<ServerDataBase> ptr_sdb(ptr_sdb_gl);
	ptr_sdb->Clear();
	RemoteObserverData observerData;
	PassMessageObserverLogicRunnable rccolr(ptr_cdb,observerData);
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
	BOOST_TEST_MESSAGE("******* Koniec TESTU LOGIKI  RemotePassMessageObserver...");
}