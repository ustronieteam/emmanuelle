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
	for(std::vector<RemoteObserver *>::iterator it = RemoteObserversList.begin();
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
	for(std::vector<RemoteObserver *>::const_iterator it = RemoteObserversList.begin();
		it != RemoteObserversList.end();	//Dopuki nie doszlismy do konca zbioru
			it++)
	{
		if((*(*it)) == observer)
			break;
	}
	RemoteObserversList.erase(it);
	return 0;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int IRemoteObjects::RegisterObserv( IRemoteObserver * observer)
{
	RemoteObserversList.push_back(observer);
	return 0;
}
