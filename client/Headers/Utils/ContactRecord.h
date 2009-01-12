#ifndef _CONTACTSRECORD_H_
#define _CONTACTSRECORD_H_

#include "DomainData.h"
#include <string>

namespace config
{
	const std::string configFileName = "client.config";
}

struct ContactRecord
{
	DomainData::User userDesc;
	bool isAvailable;
};
typedef struct ContactRecord ContactRecord;

#endif