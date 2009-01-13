#ifndef _IOBSERVERVIEW_H_
#define _IOBSERVERVIEW_H_

#include "DomainData.h"
#include "ContactRecord.h"

class IObserverView
{
	public:
		///
		/// Odebranie wiadomosci
		/// @param[in] senderAddress Adres nadawcy.
		/// @param[in] message Wiadomosc.
		///
		virtual void Obsrv_ReciveMessage(const DomainData::User & senderAddress, const DomainData::Message & message) = 0;

		///
		/// Zmiana statusu osoby na liscie kontatkow.
		/// @param[in] contact Kontakt ktory sie zmienil.
		///
		virtual void Obsrv_StatusChanged(const ContactRecord & contact) = 0;

		///
		/// Odebranie pliku.
		/// @param[in]
		///
		virtual void Obsrv_File() = 0;
};

#endif /* _IOBSERVERVIEW_H_ */