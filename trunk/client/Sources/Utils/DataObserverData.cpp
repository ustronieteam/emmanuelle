#include "DataObserverData.h"

DataObserverData::DataObserverData() 
{
 
}

DataObserverData::~DataObserverData() 
{

}

void DataObserverData::setContactRecord(const ContactRecord & c)
{
	_cr = c;
}

const ContactRecord & DataObserverData::getContactRecord()
{
	return _cr;
}
