#include "Record.h"

///
/// Zrodlo do generacji ID.
int Record::_newId = 1;

///
/// Konstruktor bezparametrowy.
Record::Record() 
{
    _recordId = _newId++;
}

///
/// Konstruktor kopiujacy.
/// @param[in] arg Record do skopiowania.
Record::Record(const Record & arg) 
{
    this->_recordId = arg._recordId;
}

///
/// Operator przypisania.
/// param[in] arg Record ktory chcemy przypisac.
Record & Record::operator =(const Record & arg) 
{
	/// Jesli sa to rozne obiekty.
    if (this != &arg)
    {
        this->_recordId = arg._recordId;
    }

	return const_cast<Record &>(arg);
}

///
/// Destruktor.
Record::~Record() 
{

}

///
/// Zwraca identyfikator rekordu.
/// @return Identyfikator rekordu.
int Record::GetRecordId() const
{
    return _recordId;
}

///
/// Ustawia identyfikator rekordu.
/// param[in] recordId Identyfikator do ustawienia.
void Record::SetRecordId(int & recordId) 
{
    this->_recordId = _recordId;
}
