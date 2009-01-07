#include "Record.h"

///
/// Zrodlo do generacji ID.
int Record::_newId = 1;

///
/// Mutex potrzebny go generowania id rekordow.
boost::mutex Record::_mutex;

///
/// Konstruktor bezparametrowy.
Record::Record() 
{
	// Mozliwosc otrzymania jednakowego identyfikatora.
	_mutex.lock();

    _recordId = _newId++;

	_mutex.unlock();
}

///
/// Konstruktor kopiujacy.
/// @param[in] arg Record do skopiowania.
Record::Record(const Record & arg) 
{
    this->_recordId = arg._recordId;
	this->_address	= arg._address;
	this->_broker	= arg._broker;
}

///
/// Operator przypisania.
/// @param[in] arg Record ktory chcemy przypisac.
Record & Record::operator =(const Record & arg) 
{
	/// Jesli sa to rozne obiekty.
    if (this != &arg)
    {
        this->_recordId = arg._recordId;
		this->_address	= arg._address;
		this->_broker	= arg._broker;
    }

	return *this;
}

///
/// Destruktor.
Record::~Record() 
{

}

///
/// Zwraca identyfikator rekordu.
/// @return Identyfikator rekordu.
const int & Record::GetRecordId() const
{
    return this->_recordId;
}

///
/// Ustawia identyfikator rekordu.
/// @param[in] recordId Identyfikator do ustawienia.
void Record::SetRecordId(const int & recordId) 
{
    this->_recordId = recordId;
}

///
/// Pobiera adresu.
/// @return Adres.
const struct DomainData::Address & Record::GetAddress() const
{
	return this->_address;
}

///
/// Ustawia adres.
/// @param[in] address Adres.
void Record::SetAddress(const struct DomainData::Address & address)
{
	this->_address = address;
}

///
/// Pobiera broker.
/// @return Broker.
const CORBA::ORB_var & Record::GetBroker() const
{
	return this->_broker;
}

///
/// Ustawia broker.
/// @param[in] broker Broker .
void Record::SetBroker(const CORBA::ORB_var & broker)
{
	this->_broker = broker;
}
