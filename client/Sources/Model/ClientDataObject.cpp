#include "ClientDataObject.h"


ClientDataObject::ClientDataObject() 
{
    logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("ClientDataObject"));
	logger->setLevel(log4cxx::Level::getAll());
}

ClientDataObject::~ClientDataObject() 
{

}

int ClientDataObject::Notify(DataObserverData data)
{
	LOG4CXX_DEBUG(logger, "ClientObjectDataObserver dla usera: " <<data.getContactRecord().userDesc.name.in());

	for(std::vector<DataObserver *>::iterator it = dataObserver.begin();
		it != dataObserver.end();	//Dopuki nie doszlismy do konca zbioru
		++it)
	{
		(*it)->Refresh(data);
	}
	return 0;

}
int ClientDataObject::Unregister(DataObserver & dat)
{
	LOG4CXX_DEBUG(logger, "Wyrejestrowywanie Obserwatorow statusu");
	return 0;
}
int ClientDataObject::Register(DataObserver * dat)
{
	LOG4CXX_DEBUG(logger, "Rejestrowanie Obserwatorow statusu");
	dataObserver.push_back(dat);
	return 0;
}

