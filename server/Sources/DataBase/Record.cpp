#include "Record.h"

int Record::_newId = 1;

boost::mutex Record::_mutex;

Record::Record() 
{
	// Mozliwosc otrzymania jednakowego identyfikatora.
	_mutex.lock();

    _recordId = _newId++;

	_mutex.unlock();
}

Record::Record(const Record & arg) 
{
    this->_recordId = arg._recordId;
	this->_address	= arg._address;
	this->_broker	= arg._broker;
}

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

Record::~Record() 
{

}

const int & Record::GetRecordId() const
{
    return this->_recordId;
}

const struct DomainData::Address & Record::GetAddress() const
{
	return this->_address;
}

void Record::SetAddress(const struct DomainData::Address & address)
{
	this->_address = address;
}

const CORBA::ORB_var & Record::GetBroker() const
{
	return this->_broker;
}

void Record::SetBroker(const CORBA::ORB_var & broker)
{
	this->_broker = broker;
}
