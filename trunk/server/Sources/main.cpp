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
#include <log4cxx/file.h>

using namespace std;

int main(int argc, char * argv[])
{
	if(argc < 2)
	{
		cout << "Zla liczba paramaetrow";
		return 1;
	}

	log4cxx::File confFile("logger.properties");
	log4cxx::PropertyConfigurator::configure(confFile);

	log4cxx::LoggerPtr logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("MAIN"));
	logger->setLevel(log4cxx::Level::getAll());

	Server * serv = Server::GetInstance(argv[1]);
	if(serv->Run())
	{
		LOG4CXX_ERROR(logger, "Serwer zosta³ nieprawidlowo zamkniety z powodu b³êdu");
		return 1;
	}

/*
	Server * serv = Server::GetInstance("test.txt");
	serv->Run();
*/	
	return 0;
}
