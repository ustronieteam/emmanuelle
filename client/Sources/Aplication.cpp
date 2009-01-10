#include "Aplication.h"

using namespace std;

int Aplication::Run() 
{
	std::string address = "";
	if(openConfFile(address))
	{
		LOG4CXX_ERROR(logger, "Brak pliku konfiguracyjnego");
		return 1;
	}

	this->model->SetServerAddress(address.c_str());

	// TODO: tu cos trzeba dodac ... jakies wywolanie ktore nie zakonczy aplikacji ... nie wiem - chyba jakas metode na widoku

    return 0;
}

bool Aplication::openConfFile(std::string & address)
{
	fstream conf;
	conf.open(configFileName, ios_base::out | ios_base::in);

	if(!conf.is_open())
	{
		LOG4CXX_ERROR(logger, "Nie ma takiego pliku konfiguracyjnego !");

		return 1;
	}

	if(conf.fail())
		conf.clear();

	conf.seekp(0, ios_base::beg);

	string line;
	while(getline(conf, line))
	{
		string::const_iterator it = line.begin();

		if(*it == '#')
			continue;

		string name = "";
		string value = "";

		for(it; it < line.end(); ++it)
		{
			if(*it != ' ' && *it != '=')
			{
				name += *it;
			}
			else if(*it == '=')
				break;
		}

		if(*it == '=')
		{		
			for(++it; it < line.end(); ++it)
			{
				if(*it != '\n' && *it != ' ')
					value += *it;
			}

			if(!name.compare(NADDRESS))
			{
				address = value;
			}
		}
	}

	conf.close();

	return 0;
}
