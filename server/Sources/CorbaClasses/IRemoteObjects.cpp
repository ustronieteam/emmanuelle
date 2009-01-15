#include "IRemoteObjects.h"

int IRemoteObjects::Notify(RemoteObserverData observerData)
{
	LOG4CXX_DEBUG(logger, "ObserverData->serverAddress:" <<observerData.getServerAddress().localization.in());

	for(std::vector<IRemoteObserver *>::iterator it = RemoteObserversList.begin();
		it != RemoteObserversList.end();
		++it)
	{
		(*it)->Refresh(observerData);
	}
	return 0;
}

int IRemoteObjects::UnregisterObserv(IRemoteObserver * observer)
{
	// TODO: dodac w klasie IRemoteObserver jakas skladowa do porownywania 2 obiektow tej klasy

	return 0;
}

int IRemoteObjects::RegisterObserv( IRemoteObserver * observer)
{
	RemoteObserversList.push_back(observer);
	return 0;
}
