#include "StatusCheckerFunctor.h"

int StatusCheckerFunctor::operator()()
{
	LOG4CXX_INFO(logger, "Nasluchiwanie zmiany statusu klientow na liscie kontaktow");
	

	while(_running == true)
	{
		LOG4CXX_DEBUG(logger, "Petla Watku");
		std::vector<ContactRecord> contactList = clientsData->GetContactsList();
		LOG4CXX_DEBUG(logger, "Obudzony watek: Sprawdzanie statusow");
		LOG4CXX_DEBUG(logger, "Aktualna lista kontaktow: "<<clientsData);
		for(std::vector<ContactRecord>::iterator it = contactList.begin();
				it != contactList.end();
				it++)
		{
			DomainData::User usr;
			usr.name	= it->userDesc.name;
			//addr.localization = CORBA::string_dup("NIEPOTRZEBNY_JEST_ADDRESS");

			LOG4CXX_DEBUG(logger, "Wywolanie metody na kliencie check status");
			bool stat = _client->CheckStatus(usr);
			LOG4CXX_DEBUG(logger, "Wywolano metode na kliencie check status");
			ContactRecord cr = *it;
			cr.isAvailable = stat;
			LOG4CXX_DEBUG(logger, "Sprawdzanie czy status sie zmienil");
			if(stat != it->isAvailable)
			{
				LOG4CXX_DEBUG(logger, "Wykryto zmieniony status klienta. Stary status: " << it->isAvailable <<" Nowy: " <<stat);
				this->clientsData->ModifyRecord(cr);
				LOG4CXX_DEBUG(logger, "Zmieniono record(Nowy status : " << clientsData->FindByName(it->userDesc.name.in()).isAvailable);
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
			
	LOG4CXX_DEBUG(logger, "Zakonczono nasluchiwanie statusu!!!");
	return 0;

}