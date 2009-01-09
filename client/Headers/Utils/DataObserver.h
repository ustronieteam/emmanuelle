#ifndef DATAOBSERVER_H
#define DATAOBSERVER_H
//Begin section for file DataObserver.h
//TODO: Add definitions that you want preserved
//End section for file DataObserver.h

#include "DataObserverData.h"


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class DataObserver
{

    //Begin section for DataObserver
    //TODO: Add attributes that you want preserved
    //End section for DataObserver



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        DataObserver();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~DataObserver();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int Refresh(DataObserverData data) = 0;

};  //end class DataObserver

#endif
