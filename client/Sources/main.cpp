///
/// @author	Wojciech Grzeœkowiak
///			Mateusz Ko³odziejczyk
///			Marian Szczykulskih
/// @date	10.01.2009
///
/// @brief	Client EMMANUELLE v1.0 
///

#include <iostream>
#include "Aplication.h"

#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/file.h>

using namespace std;

int main(int argc, char * argv[])
{
	log4cxx::File confFile("logger.properties");
	log4cxx::PropertyConfigurator::configure(confFile);

	log4cxx::LoggerPtr logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("MAIN"));
	logger->setLevel(log4cxx::Level::getAll());

	Aplication * app = Aplication::GetInstance();
	if(app->Run())
	{
		LOG4CXX_ERROR(logger, "Klient zosta³ nieprawidlowo zamkniety z powodu b³êdu");
		return 1;
	}

	return 0;
}
