///@author Marian Szczykulski
///@brief  unit testy do serwera. Testowana jest logika (obserwatorzy)
///@brief  oraz utworzone struktury danych(ClientsDataBase i ServerDataBase)

#include "RemoteServerConnectedObserverTest.h"

#include "PassMessageObserverTest.h"
#include "RemoteClientConnectedObserverTest.h"
#include "RemoteClientDisconnectedObserverTest.h"
#include "RemoteClientSendMessageObserverTest.h"
#include "DataBaseTest.h"

#include <boost/test/debug.hpp>
#include <log4cxx/logger.h>
#include <log4cxx/level.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/file.h>

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[])
{
	boost::shared_ptr<ServerDataBase> ptr_sdb_gl=ServerDataBase::GetInstnace();
	ptr_sdb_gl->Clear();
	boost::shared_ptr<ClientsDataBase> ptr_cdb_gl=ClientsDataBase::GetInstnace();
		ptr_cdb_gl->Clear();
	//Konfiguracja loggera
	log4cxx::File confFile("serverLogger.properties");
	boost::debug::detect_memory_leaks(false);
	
	log4cxx::PropertyConfigurator::configure(confFile);
	
	boost::unit_test::test_suite* ts1 = BOOST_TEST_SUITE( "RemoteServerConnectedObserver" );
	ts1->add(BOOST_TEST_CASE(&test_case_1));
	ts1->add(BOOST_TEST_CASE(&test_case_2));

	boost::unit_test::test_suite* ts2 = BOOST_TEST_SUITE( "PassMessageObserver" );
	ts2->add(BOOST_TEST_CASE(&test_case_passMessage_1));
	ts2->add(BOOST_TEST_CASE(&test_case_passMessage_2));

	boost::unit_test::test_suite* ts3 = BOOST_TEST_SUITE( "RemoteClientConnectedObserver" );
	ts3->add(BOOST_TEST_CASE(&test_case_remoteClientConnected_1));
	ts3->add(BOOST_TEST_CASE(&test_case_remoteClientConnected_2));

	boost::unit_test::test_suite* ts4 = BOOST_TEST_SUITE( "RemoteClientDisconnectedObserver" );
	ts4->add(BOOST_TEST_CASE(&test_case_clientDisconnected_1));
	ts4->add(BOOST_TEST_CASE(&test_case_clientDisconnected_2));

	boost::unit_test::test_suite* ts5 = BOOST_TEST_SUITE( "RemoteClientSendMessageObserver" );
	ts5->add(BOOST_TEST_CASE(&test_case_sendMessage_1));
	ts5->add(BOOST_TEST_CASE(&test_case_sendMessage_2));


	//Dodanie do suitu dla testow obserwatorow
	boost::unit_test::test_suite* mainObserversTest = BOOST_TEST_SUITE( "ObserversTest" );
	mainObserversTest->add(ts1);
	mainObserversTest->add(ts2);
	mainObserversTest->add(ts3);
	mainObserversTest->add(ts4);
	mainObserversTest->add(ts5);


	//Testy bazy danych

	boost::unit_test::test_suite* tc_db = BOOST_TEST_SUITE( "DataBaseTestCase" );
	tc_db->add(BOOST_TEST_CASE(&test_case_ClientsDataBase));
	tc_db->add(BOOST_TEST_CASE(&test_case_ServerDataBase));
	//Dodanie do suitu dla testow bazy danych
	boost::unit_test::test_suite* mainDataBaseTest = BOOST_TEST_SUITE( "DataBaseTest" );
	mainDataBaseTest->add(tc_db);

	//dodanie do glownego test suite-u
	boost::unit_test::framework::master_test_suite().add( mainObserversTest );
	boost::unit_test::framework::master_test_suite().add( mainDataBaseTest );

	return 0;

}