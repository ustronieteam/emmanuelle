#include "DataObserverData.h"

///
/// Konstruktor.
///
DataObserverData::DataObserverData() 
{
 
}

///
/// Destruktor.
///
DataObserverData::~DataObserverData() 
{

}

///
/// Ustawienie informacji o kliencie.
/// @param[in] c Informacje o kliencie.
///
void DataObserverData::setContactRecord(const ContactRecord & c)
{
	_cr = c;
}

///
/// Pobiera informacji o kliencie.
/// @return Informacje o kliencie.
///
const ContactRecord & DataObserverData::getContactRecord()
{
	return _cr;
}
