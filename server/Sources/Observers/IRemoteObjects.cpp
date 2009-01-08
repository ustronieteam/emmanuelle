#include "IRemoteObjects.h"
//Begin section for file IRemoteObjects.cpp
//TODO: Add definitions that you want preserved
//End section for file IRemoteObjects.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
IRemoteObjects::IRemoteObjects() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
IRemoteObjects::~IRemoteObjects() 
{
    //TODO Auto-generated method stub
}


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int IRemoteObjects::Notify(RemoteObserverData observerData)
{
	log4cxx::LoggerPtr logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("IRemoteObjects"));
	logger->setLevel(log4cxx::Level::getAll());
	LOG4CXX_DEBUG(logger, "ObserverData->serverAddress:" <<observerData.getServerAddress().localization.in());
	for(std::vector<IRemoteObserver *>::iterator it = RemoteObserversList.begin();
		it != RemoteObserversList.end();	//Dopuki nie doszlismy do konca zbioru
			it++)
	{
		(*it)->Refresh(observerData);
	}
	return 0;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int IRemoteObjects::UnregisterObserv(IRemoteObserver & observer)
{
	// TODO: dodac w klasie IRemoteObserver jakas skladowa do porownywania 2 obiektow tej klasy
	/*
	std::vector<IRemoteObserver *>::const_iterator it = RemoteObserversList.begin();
	for(it;
		it != RemoteObserversList.end();	//Dopuki nie doszlismy do konca zbioru
			it++)
	{
		if((*(*it)) == observer)
			break;
	}
	RemoteObserversList.erase(it);
	*/
	return 0;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int IRemoteObjects::RegisterObserv( IRemoteObserver * observer)
{
	RemoteObserversList.push_back(observer);
	return 0;
}
