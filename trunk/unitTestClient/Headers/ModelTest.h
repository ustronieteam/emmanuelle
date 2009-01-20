#ifndef _MODEL_TEST_H_
#define _MODEL_TEST_H_


#include "Client.h"
#include "IModel.h"
#include "ClientsData.h"

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <iostream>
#include <log4cxx/logger.h>
#include <log4cxx/level.h>

void test_case_ContactDataBase();
void test_case_Client();
void test_case_Model();


#endif