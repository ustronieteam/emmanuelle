#ifndef _PASSMESSAGEOBSERVERTEST_H_
#define _PASSMESSAGEOBSERVERTEST_H_

#include "PassMessageObserver.h"
//#define BOOST_TEST_MODULE ObserversTests
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <iostream>
#include "ServerRecord.h"
#include "ServerDataBase.h"
#include "ClientsDataBase.h"
#include <log4cxx/logger.h>
#include <log4cxx/level.h>



void test_case_passMessage_1();
void test_case_passMessage_2();

#endif