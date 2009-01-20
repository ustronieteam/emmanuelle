///@author Marian Szczykulski

#include "ControllerTest.h"
#include "ModelTest.h"

#include <boost/test/debug.hpp>
#include <log4cxx/logger.h>
#include <log4cxx/level.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/file.h>

boost::unit_test::test_suite* init_unit_test_suite( int argc, char* argv[])
{

	log4cxx::File confFile("unitLogger.properties");
	log4cxx::PropertyConfigurator::configure(confFile);
	boost::debug::detect_memory_leaks(false);
	
	//Testy bazy danych kontaktów klienta
	boost::unit_test::test_suite* tc_db = BOOST_TEST_SUITE( "ContactDataBaseTestCase" );
	tc_db->add(BOOST_TEST_CASE(&test_case_ContactDataBase));

	boost::unit_test::test_suite* tc_client = BOOST_TEST_SUITE( "ClientTestCase" );
	tc_client->add(BOOST_TEST_CASE(&test_case_Client));

	boost::unit_test::test_suite* tc_model = BOOST_TEST_SUITE( "ModelTestCase" );
	tc_model->add(BOOST_TEST_CASE(&test_case_Model));


	//Dodanie do suitu dla modelu
	boost::unit_test::test_suite* modelSuite = BOOST_TEST_SUITE( "ModelTest" );
	modelSuite->add(tc_db);
	modelSuite->add(tc_client);
	modelSuite->add(tc_model);
		//Dodanie do suitu dla kontrolera
	//dodanie do glownego test suite-u
	boost::unit_test::framework::master_test_suite().add( modelSuite );

	return 0;

}