#ifndef IREMOTEOBSERVER_H
#define IREMOTEOBSERVER_H

#include "RemoteObserverData.h"


///@author Marian Szczykulski
///@date 2009-01-09
///@brief Abstrakcyjna klasa obserwatora
class IRemoteObserver
{

    public:

        IRemoteObserver();
        virtual ~IRemoteObserver();
        virtual int Refresh(RemoteObserverData observerData) = 0;

};  //end class IRemoteObserver

#endif
