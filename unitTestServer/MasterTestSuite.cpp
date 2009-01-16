
#include "RemoteServerConnectedObserverTest.h"

#include "PassMessageObserverTest.h"
#include "RemoteClientConnectedObserverTest.h"
#include "RemoteClientDisconnectedObserverTest.h"
#include "RemoteClientSendMessageObserverTest.h"

#include <log4cxx/logger.h>
#include <log4cxx/level.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/file.h>

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[])
{
	//Konfiguracja loggera
	log4cxx::File confFile("serverLogger.properties");
	log4cxx::PropertyConfigurator::configure(confFile);

	boost::unit_test::test_suite* ts1 = BOOST_TEST_SUITE( "RemoteServerConnectedObserver" );
	ts1->add(BOOST_TEST_CASE(&test_case_1));
	ts1->add(BOOST_TEST_CASE(&test_case_2));

	//boost::unit_test::test_suite* ts2 = BOOST_TEST_SUITE( "RemoteServerDisconnectedObserver" );
	//ts2->add(BOOST_TEST_CASE(&test_case_serverDisconnected_1));
	//ts2->add(BOOST_TEST_CASE(&test_case_serverDisconnected_2));

	//boost::unit_test::test_suite* ts3 = BOOST_TEST_SUITE( "RemoteServerUpdateClientObserver" );
	//ts3->add(BOOST_TEST_CASE(&test_case_updateClient_1));
	//ts3->add(BOOST_TEST_CASE(&test_case_updateClient_2));

	//boost::unit_test::test_suite* ts4 = BOOST_TEST_SUITE( "PassMessageObserver" );
	//ts4->add(BOOST_TEST_CASE(&test_case_passMessage_1));
	//ts4->add(BOOST_TEST_CASE(&test_case_passMessage_2));

	//boost::unit_test::test_suite* ts5 = BOOST_TEST_SUITE( "RemoteClientConnectedObserver" );
	//ts5->add(BOOST_TEST_CASE(&test_case_remoteClientConnected_1));
	//ts5->add(BOOST_TEST_CASE(&test_case_remoteClientConnected_2));

	//boost::unit_test::test_suite* ts6 = BOOST_TEST_SUITE( "RemoteClientCreatePipeObserver" );
	//ts6->add(BOOST_TEST_CASE(&test_case_clientCreatePipe_1));
	//ts6->add(BOOST_TEST_CASE(&test_case_clientCreatePipe_2));

	//boost::unit_test::test_suite* ts7 = BOOST_TEST_SUITE( "RemoteClientDisconnectedObserver" );
	//ts7->add(BOOST_TEST_CASE(&test_case_clientDisconnected_1));
	//ts7->add(BOOST_TEST_CASE(&test_case_clientDisconnected_2));

	//boost::unit_test::test_suite* ts8 = BOOST_TEST_SUITE( "RemoteClientSendMessageObserver" );
	//ts8->add(BOOST_TEST_CASE(&test_case_sendMessage_1));
	//ts8->add(BOOST_TEST_CASE(&test_case_sendMessage_2));

	//boost::unit_test::test_suite* ts9 = BOOST_TEST_SUITE( "ServerCreatePipeObserver" );
	//ts9->add(BOOST_TEST_CASE(&test_case_sendMessage_1));
	//ts9->add(BOOST_TEST_CASE(&test_case_sendMessage_2));*/

	//Dodanie do suitu dla testow obserwatorow
	boost::unit_test::test_suite* mainObserversTest = BOOST_TEST_SUITE( "ObserversTest" );
	mainObserversTest->add(ts1);
	//mainObserversTest->add(ts2);
	//mainObserversTest->add(ts3);
	//mainObserversTest->add(ts4);
	//mainObserversTest->add(ts5);
	//mainObserversTest->add(ts6);
	//mainObserversTest->add(ts7);
	//mainObserversTest->add(ts8);
	//mainObserversTest->add(ts9);

	//dodanie do glownego test suite-u
	boost::unit_test::framework::master_test_suite().add( mainObserversTest );

	return 0;

}