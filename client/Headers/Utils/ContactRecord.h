#ifndef _CONTACTSRECORD_H_
#define _CONTACTSRECORD_H_

#include "DomainData.h"
#include <string>

namespace config
{
	const std::string configFileName = "client.config";
}

///
/// Struktura przechowywujaca informacje o kontakcie.
///
struct ContactRecord
{
	///
	/// Informacje o uzytkowniku.
	///
	DomainData::User userDesc;

	///
	/// Aktywnosc.
	///
	bool isAvailable;
};

typedef struct ContactRecord ContactRecord;

#endif