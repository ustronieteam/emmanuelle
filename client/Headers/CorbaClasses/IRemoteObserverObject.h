#ifndef IREMOTEOBSERVEROBJECT_H
#define IREMOTEOBSERVEROBJECT_H
//Begin section for file IRemoteObserverObject.h
//TODO: Add definitions that you want preserved
//End section for file IRemoteObserverObject.h

#include "RemoteObserverData.h"


class IRemoteObserver;

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class IRemoteObserverObject
{

    //Begin section for IRemoteObserverObject
    //TODO: Add attributes that you want preserved
    //End section for IRemoteObserverObject

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        IRemoteObserver * iObserver;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        IRemoteObserverObject();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~IRemoteObserverObject();

        //get iObserver
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual IRemoteObserver * & get_iObserver() = 0;

        //set iObserver
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual void set_iObserver(IRemoteObserver * & iObserver) = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int Notify(RemoteObserverData objectData) = 0;

};  //end class IRemoteObserverObject

#endif
