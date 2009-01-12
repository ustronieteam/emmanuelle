#include "StatusCheckerFunctor.h"

int StatusCheckerFunctor::operator()()
{
	LOG4CXX_INFO(logger, "Nasluchiwanie zmiany statusu klientow na liscie kontaktow");
	return 0;

}