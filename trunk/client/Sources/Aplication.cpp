#include "Aplication.h"

using namespace std;

int Aplication::Run() 
{
	// Uruchomienie widoku.
	// Tutaj sie cala aplikacja blokuje, wyjscie z tej funkcji nastepuje 
	// wtedy kiedy uzytkownik chce zakonczyc prace.
	this->view->Run();

    return 0;
}
