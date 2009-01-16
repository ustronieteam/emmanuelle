///
/// @author	Wojciech Grzeœkowiak
///			Mateusz Ko³odziejczyk
///			Marian Szczykulskih
/// @date	06.01.2009
///
/// @brief	Server EMMANUELLE v1.0 
///

#include <iostream>
#include "Server.h"

#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>

#ifdef WIN32
	#include <log4cxx/file.h>
#endif

using namespace std;

int main(int argc, char * argv[])
{
	if(argc < 2)
	{
		cout << "Zla liczba paramaetrow";
		return 1;
	}

#ifdef WIN32
	log4cxx::File confFile("serverLogger.properties");
	log4cxx::PropertyConfigurator::configure(confFile);
#else
	log4cxx::PropertyConfigurator::configure("serverLogger.properties");
#endif

	log4cxx::LoggerPtr logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("MAIN"));
	logger->setLevel(LOGLEVEL);

	Server * serv = Server::GetInstance(argv[1]);
	if(serv->Run())
	{
		LOG4CXX_ERROR(logger, "Serwer zosta³ nieprawidlowo zamkniety z powodu b³êdu");
		return 1;
	}

	return 0;
}
