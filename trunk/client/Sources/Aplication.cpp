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

	// Uruchomienie widoku.
	// Tutaj sie cala aplikacja blokuje, wyjscie z tej funkcji nastepuje 
	// wtedy kiedy uzytkownik chce zakonczyc prace.
	this->view->Run();

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

	string s = "^\\s*";
	s += NADDRESS;
	s += "\\s*=\\s*(.*)\\s*$";

	static const boost::regex addr(s.c_str());
	static const boost::regex comment("^#(.*)$");

	string line;
	while(getline(conf, line))
	{
		boost::smatch what;
		if(boost::regex_match(line, what, comment))
		{
			// znaleziono komentarz
		}
		else if(boost::regex_match(line, what, addr))
		{
			// znaleziono address
			address = what[1];
		}
		else
		{
			LOG4CXX_ERROR(logger, "Niedozwolone wyrazenie w pliku !");
			return 1;
		}
	}

	conf.close();

	return 0;
}
