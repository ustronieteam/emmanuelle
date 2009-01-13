#ifndef IREMOTEOBSERVER_H
#define IREMOTEOBSERVER_H

#include "RemoteObserverData.h"

///
/// IRemoteObserver
/// @brief Klasa bazowa dla obserwatorow zdalnych.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.13
///
class IRemoteObserver
{
    public:

		///
		/// Konstruktor.
		///
        IRemoteObserver();

		///
		/// Destruktor.
		///
        virtual ~IRemoteObserver();

		///
		/// Refresh.
		///
        virtual int Refresh(RemoteObserverData objectData) = 0;
};

#endif
