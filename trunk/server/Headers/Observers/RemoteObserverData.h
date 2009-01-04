#ifndef REMOTEOBSERVERDATA_H
#define REMOTEOBSERVERDATA_H
//Begin section for file RemoteObserverData.h
//TODO: Add definitions that you want preserved
//End section for file RemoteObserverData.h

#include "EventType.h"


//Dane przekazywane przez zdalny obiekt obserwowany do odpowiedniego obserwatora. Dzieki temu bedzie wiedzial co sie
//zmienilo.
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class RemoteObserverData
{

    //Begin section for RemoteObserverData
    //TODO: Add attributes that you want preserved
    //End section for RemoteObserverData

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        EventType eventType;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteObserverData();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteObserverData(RemoteObserverData & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        RemoteObserverData & operator =(const RemoteObserverData & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~RemoteObserverData();

        //get eventType
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline EventType & get_eventType();

        //set eventType
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline void set_eventType(EventType & eventType);

};  //end class RemoteObserverData

#endif
