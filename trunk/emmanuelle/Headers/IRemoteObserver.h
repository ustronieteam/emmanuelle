#ifndef IREMOTEOBSERVER_H
#define IREMOTEOBSERVER_H
//Begin section for file IRemoteObserver.h
//TODO: Add definitions that you want preserved
//End section for file IRemoteObserver.h

#include "RemoteObserverData.h"


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class IRemoteObserver
{

    //Begin section for IRemoteObserver
    //TODO: Add attributes that you want preserved
    //End section for IRemoteObserver



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        IRemoteObserver();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~IRemoteObserver();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int Refresh(RemoteObserverData observerData) = 0;

};  //end class IRemoteObserver

#endif
