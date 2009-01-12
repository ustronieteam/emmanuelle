#include "StatusCheckerFunctor.h"

int StatusCheckerFunctor::operator()()
{
	LOG4CXX_INFO(logger, "Nasluchiwanie zmiany statusu klientow na liscie kontaktow");
	std::vector<ContactRecord> contactList = clientsData->GetContactsList();

	while(true)
	{
		LOG4CXX_DEBUG(logger, "Obudzony watek: Sprawdzanie statusow");
		for(std::vector<ContactRecord>::iterator it = contactList.begin();
				it != contactList.end();
				it++)
		{
			DomainData::Address addr;
			addr.name	= it->userDesc.name;
			addr.localization = CORBA::string_dup("NIEPOTRZEBNY_JEST_ADDRESS");

			bool stat = _client->CheckStatus(addr);
			ContactRecord cr = *it;
			cr.isAvailable = stat;
			if(stat != it->isAvailable)
			{
				LOG4CXX_DEBUG(logger, "Wykryto zmieniony status klienta");
				this->clientsData->ModifyRecord(cr);			
				DataObserverData obsrData;
				obsrData.setContactRecord(cr);
				clientsData->Notify(obsrData);
			}
		}
		Sleep(sleepTime);
	}
			
	
	return 0;

}