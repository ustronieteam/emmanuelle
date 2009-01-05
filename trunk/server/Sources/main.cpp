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

	Server * serv = Server::getInstance(argv[1]);
	serv->Run();
/*
	Server * serv = Server::getInstance("test.txt");
	serv->Run();
*/
	return 0;
}
