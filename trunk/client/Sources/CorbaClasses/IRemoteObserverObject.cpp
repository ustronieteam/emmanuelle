#include "IRemoteObserverObject.h"


int IRemoteObserverObject::RegisterObserv(IRemoteObserver * observ)
{
	LOG4CXX_DEBUG(logger, "Zarejestrowanie obserwatora.");
	RemoteObserversList.push_back(observ);
	return 0;
}

int IRemoteObserverObject::UnregisterObserv()
{
	LOG4CXX_DEBUG(logger, "Wyrejestrowanie obserwatora.");
	for(std::vector<IRemoteObserver *>::const_iterator it = RemoteObserversList.begin(); it < RemoteObserversList.end(); ++it)
		delete *it;

	return 0;
}

void IRemoteObserverObject::Notify(RemoteObserverData objectData)
{
	for(std::vector<IRemoteObserver *>::const_iterator it = RemoteObserversList.begin(); it < RemoteObserversList.end(); ++it)
		(*it)->Refresh(objectData);
}
