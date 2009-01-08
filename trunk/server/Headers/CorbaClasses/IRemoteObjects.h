#ifndef IREMOTEOBJECTS_H
#define IREMOTEOBJECTS_H
//Begin section for file IRemoteObjects.h
//TODO: Add definitions that you want preserved
//End section for file IRemoteObjects.h

#include "RemoteObserverData.h"
#include "IRemoteObserver.h"
#include <iostream>
#include <vector>

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class IRemoteObjects
{

    //Begin section for IRemoteObjects
    //TODO: Add attributes that you want preserved
    //End section for IRemoteObjects

    private:

		std::vector<IRemoteObserver *> RemoteObserversList;

    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        IRemoteObjects();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~IRemoteObjects();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int Notify(RemoteObserverData observerData);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int UnregisterObserv(IRemoteObserver & observer);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int RegisterObserv(IRemoteObserver * observer);

};  //end class IRemoteObjects

#endif