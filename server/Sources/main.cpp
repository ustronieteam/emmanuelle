///
/// @author	Wojciech Grze�kowiak
///			Mateusz Ko�odziejczyk
///			Marian Szczykulski
/// @date	06.01.2009
///
/// @brief	Server EMMANUELLE v1.0 
///

#include <iostream>
#include "Server.h"

using namespace std;

int main(int argc, char * argv[])
{
	if(argc != 2)
	{
		cout << "Zla liczba paramaetrow";
		return 1;
	}

	log4cxx::LoggerPtr logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("MAIN"));
	logger->setLevel(log4cxx::Level::getAll());

	Server * serv = Server::GSetInstance(argv[1]);
	if(serv->Run())
	{
		LOG4CXX_ERROR(logger, "Serwer zosta� nieprawidlowo zamkniety z powodyu b��du");
		return 1;
	}

/*
	Server * serv = Server::GetInstance("test.txt");
	serv->Run();
*/
	return 0;
}
