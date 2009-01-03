#include "RemoteObserverData.h"
//Begin section for file RemoteObserverData.cpp
//TODO: Add definitions that you want preserved
//End section for file RemoteObserverData.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteObserverData::RemoteObserverData() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteObserverData::RemoteObserverData(RemoteObserverData & arg) 
{
    //TODO Auto-generated method stub
    this->eventType = arg.eventType;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteObserverData & RemoteObserverData::operator =(const RemoteObserverData & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->eventType = arg.eventType;
    }
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
RemoteObserverData::~RemoteObserverData() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
EventType & RemoteObserverData::get_eventType() 
{
    //TODO Auto-generated method stub
    return eventType;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void RemoteObserverData::set_eventType(EventType & eventType) 
{
    //TODO Auto-generated method stub
    this->eventType = eventType;
}
