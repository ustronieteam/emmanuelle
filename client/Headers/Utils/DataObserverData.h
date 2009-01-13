#ifndef DATAOBSERVERDATA_H
#define DATAOBSERVERDATA_H

#include "ContactRecord.h"

///
/// DataObserverData
/// @brief Dane dla obserwatorow typu Data Observer.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.13
///
class DataObserverData
{
	private:

		///
		/// Informacje o kontakcie.
		///
		ContactRecord _cr;

    public:

		///
		/// Konstruktor.
		///
        DataObserverData();

		///
		/// Destruktor.
		///
        virtual ~DataObserverData();

		///
		/// Ustawienie informacji o kliencie.
		/// @param[in] c Informacje o kliencie.
		///
		void setContactRecord(const ContactRecord & c);

		///
		/// Pobiera informacji o kliencie.
		/// @return Informacje o kliencie.
		///
		const ContactRecord & getContactRecord();
};

#endif
