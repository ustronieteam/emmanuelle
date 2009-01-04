#include "Server.h"
//Begin section for file Server.cpp
//TODO: Add definitions that you want preserved
//End section for file Server.cpp

Server::Server(const char * fileName) 
{
    // stworzenie obiektow baz danych: klienta i serwera
	this->clientDataBaseObj = new ClientsDataBase();
	this->serverDataBaseObj = new ServerDataBase();

	configFileName = fileName;
}

/*
Server::Server(const Server & arg) 
{
    return arg;
}

*/

Server::~Server() 
{
    //TODO Auto-generated method stub
}



bool Server::run() 
{
    //TODO Auto-generated method stub
    return 0;
}


bool Server::init() 
{
    //TODO Auto-generated method stub
    return 0;
}
