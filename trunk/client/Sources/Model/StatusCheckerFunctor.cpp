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

			LOG4CXX_DEBUG(logger, "Wywolanie metody na kliencie check status");
			bool stat = _client->CheckStatus(addr);
			LOG4CXX_DEBUG(logger, "Wywolano metode na kliencie check status");
			ContactRecord cr = *it;
			cr.isAvailable = stat;
			LOG4CXX_DEBUG(logger, "Sprawdzanie czy status sie zmienil");
			if(stat != it->isAvailable)
			{
				LOG4CXX_DEBUG(logger, "Wykryto zmieniony status klienta");
				this->clientsData->ModifyRecord(cr);
				LOG4CXX_DEBUG(logger, "Zmieniono record");
				DataObserverData obsrData;
				obsrData.setContactRecord(cr);
				LOG4CXX_DEBUG(logger, "Uruchamianie obserwatora");
				clientsData->Notify(obsrData);
				LOG4CXX_DEBUG(logger, "Uruchomiono obserwatorow");
			}
		}

#ifndef WIN32
		sleep(10);
#else
		Sleep(10000);
#endif

	}
			
	
	return 0;

}