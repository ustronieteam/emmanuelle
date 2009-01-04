#ifndef IREMOTEOBJECTS_H
#define IREMOTEOBJECTS_H
//Begin section for file IRemoteObjects.h
//TODO: Add definitions that you want preserved
//End section for file IRemoteObjects.h

#include "RemoteObserverData.h"
#include "IRemoteObserver.h"


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class IRemoteObjects
{

    //Begin section for IRemoteObjects
    //TODO: Add attributes that you want preserved
    //End section for IRemoteObjects

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        IRemoteObserver * iRemoteObserver; //Zmieniæ na kolekcjê !!!!!!!!!!!!!



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        IRemoteObjects();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~IRemoteObjects();

        //get iRemoteObserver
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual IRemoteObserver * & get_iRemoteObserver() = 0;

        //set iRemoteObserver
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual void set_iRemoteObserver(IRemoteObserver * & iRemoteObserver) = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int Notify(RemoteObserverData observerData) = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int Unregister(IRemoteObserver & observer) = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int Register(IRemoteObserver & observer) = 0;

};  //end class IRemoteObjects

#endif
