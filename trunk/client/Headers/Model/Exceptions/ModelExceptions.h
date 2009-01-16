#ifndef _MODELEXCEPTIONS_H_
#define _MODELEXCEPTIONS_H_

///
///Wyjatek rzucany podczas wstawiania
///@author Marian Szczykulski
///@date 2009-01-12
///
class ContactAlreadyExistsException : public std::exception
{
	public:
		ContactAlreadyExistsException(): std::exception(){}
};

///
///Wyjatek rzucany podczas wyszukiwania i usuwania
///@author Marian Szczykulski
///@date 2009-01-12
///
class ContactNotFoundException : public std::exception
{
	public:
		ContactNotFoundException(): std::exception(){}
};

#endif