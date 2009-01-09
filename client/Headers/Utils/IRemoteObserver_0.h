#ifndef IREMOTEOBSERVER_0_H
#define IREMOTEOBSERVER_0_H
//Begin section for file IRemoteObserver_0.h
//TODO: Add definitions that you want preserved
//End section for file IRemoteObserver_0.h

#include "RemoteObserverData_0.h"


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class IRemoteObserver_0
{

    //Begin section for IRemoteObserver_0
    //TODO: Add attributes that you want preserved
    //End section for IRemoteObserver_0



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        IRemoteObserver_0();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~IRemoteObserver_0();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int Refresh(RemoteObserverData_0 objectData) = 0;

};  //end class IRemoteObserver_0

#endif
