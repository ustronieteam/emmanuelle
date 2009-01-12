#ifndef _IOBSERVERVIEW_H_
#define _IOBSERVERVIEW_H_

#include "DomainData.h"

///
/// IObserverView
/// @brief Interfejs dla obserwatorow wykonujacych zadania na widoku.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.12
///
class IObserverView
{
	///
	/// Odebranie wiadomosci
	/// @param[in] senderAddress Adres nadawcy.
	/// @param[in] message Wiadomosc.
	///
	virtual void Obsrv_ReciveMessage(const DomainData::Address & senderAddress, const DomainData::Message & message) = 0;
};

#endif /* _IOBSERVERVIEW_H_ */
