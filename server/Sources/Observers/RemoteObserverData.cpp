#include "Observers/RemoteObserverData.h"

RemoteObserverData::RemoteObserverData() 
{
}

RemoteObserverData::~RemoteObserverData() 
{
}

EventType & RemoteObserverData::get_eventType() 
{
    return eventType;
}

void RemoteObserverData::set_eventType(EventType eventType) 
{
    this->eventType = eventType;
}
