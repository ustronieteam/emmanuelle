#include "IRemoteObserverObject.h"


int IRemoteObserverObject::RegisterObserv(IRemoteObserver * observ)
{
	LOG4CXX_DEBUG(logger, "Zarejestrowanie obserwatora.");
	observer = observ;
	return 0;
}

int IRemoteObserverObject::UnregisterObserv()
{
	LOG4CXX_DEBUG(logger, "Wyrejestrowanie obserwatora.");
	delete observer;
	return 0;
}

void IRemoteObserverObject::Notify(RemoteObserverData objectData)
{
	observer->Refresh(objectData);
}
