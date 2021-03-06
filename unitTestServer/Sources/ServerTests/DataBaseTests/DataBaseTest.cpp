#include "DataBaseTest.h"


void test_case_ClientsDataBase()
{
	BOOST_TEST_MESSAGE("*********** TEST Bazy danych klientow");
	ClientsDataBase *cdb = ClientsDataBase::GetInstance();
	cdb->Clear();
	//BOOST_CHECK_THROW(cdb->Find(12),std::exception);
	BOOST_TEST_MESSAGE("*TestInsertu");
	ClientRecord cr;
	DomainData::Address addr;
	DomainData::User usr;
	usr.name = CORBA::string_dup("testName");
	addr.localization = CORBA::string_dup("test");
	cr.SetAddress(addr);
	cr.SetUser(usr);
	BOOST_CHECK_EQUAL(cdb->InsertRecord(cr),1);
	BOOST_CHECK_THROW(cdb->InsertRecord(cr),std::exception);
	BOOST_TEST_MESSAGE("*Test Find-a");
	DomainData::User usr2;
	BOOST_CHECK_EQUAL(cdb->Find(usr2),-1);
	BOOST_CHECK(cdb->Find(usr)>0);
	BOOST_TEST_MESSAGE("*Test Modify");
	ClientRecord cr2;
	BOOST_CHECK_THROW(cdb->ModifyRecord(cr2),std::exception);
	BOOST_CHECK_NO_THROW(cdb->ModifyRecord(cr));
	BOOST_TEST_MESSAGE("*Test Delete");
	BOOST_CHECK_THROW(cdb->DeleteRecord(-2),std::exception);
	BOOST_CHECK_NO_THROW(cdb->DeleteRecord(cdb->Find(usr)));
	BOOST_TEST_MESSAGE("*Test Clear");
	cdb->Clear();
	BOOST_CHECK_EQUAL(cdb->Size(),0);
	
	BOOST_TEST_MESSAGE("*********** Koniec TESTU Bazy danych klientow");
}
void test_case_ServerDataBase()
{
	BOOST_TEST_MESSAGE("*********** TEST Bazy danych klientow");
	ServerDataBase *cdb = ServerDataBase::GetInstance();
	cdb->Clear();
	//BOOST_CHECK_THROW(cdb->Find(12),std::exception);
	BOOST_TEST_MESSAGE("*TestInsertu");
	ServerRecord sr;
	DomainData::Address addr;
	addr.localization = CORBA::string_dup("test");
	sr.SetAddress(addr);
	BOOST_CHECK_EQUAL(cdb->InsertRecord(sr),1);
	BOOST_CHECK_THROW(cdb->InsertRecord(sr),std::exception);
	BOOST_TEST_MESSAGE("*Test Find-a");
	DomainData::Address ad2;
	BOOST_CHECK_EQUAL(cdb->Find(ad2),-1);
	BOOST_CHECK(cdb->Find(addr)>0);
	BOOST_TEST_MESSAGE("*Test Modify");
	ServerRecord sr2;
	BOOST_CHECK_THROW(cdb->ModifyRecord(sr2),std::exception);
	BOOST_CHECK_NO_THROW(cdb->ModifyRecord(sr));
	BOOST_TEST_MESSAGE("*Test Delete");
	BOOST_CHECK_THROW(cdb->DeleteRecord(-2),std::exception);
	BOOST_CHECK_NO_THROW(cdb->DeleteRecord(cdb->Find(addr)));
	BOOST_TEST_MESSAGE("*Test Clear");
	cdb->Clear();
	BOOST_CHECK_EQUAL(cdb->Size(),0);
	
	BOOST_TEST_MESSAGE("*********** Koniec TESTU Bazy danych klientow");
}