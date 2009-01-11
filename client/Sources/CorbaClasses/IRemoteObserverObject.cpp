#include "IRemoteObserverObject.h"


int IRemoteObserverObject::RegisterObserv(IRemoteObserver * observer)
{
	LOG4CXX_DEBUG(logger, "Zarejestrowanie obserwatora.");
	RemoteObserversList.push_back(observer);
	return 0;
}

int IRemoteObserverObject::UnregisterObserv(IRemoteObserver * observer)
{
	LOG4CXX_DEBUG(logger, "Wyrejestrowanie obserwatora.");
	return 0;
}

void IRemoteObserverObject::Notify(RemoteObserverData objectData)
{
	LOG4CXX_DEBUG(logger, "Wywolanie 'Refresh' na kazdym obserwatorze w kolekcji.");
	for(std::vector<IRemoteObserver *>::iterator it = RemoteObserversList.begin(); it != RemoteObserversList.end(); ++it)
		(*it)->Refresh(objectData);
}
