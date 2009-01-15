#ifndef IREMOTEOBJECTS_H
#define IREMOTEOBJECTS_H

#include "RemoteObserverData.h"
#include "IRemoteObserver.h"

#include <iostream>
#include <vector>

#include <log4cxx/logger.h>
#include <log4cxx/level.h>

///
/// @author	Mateusz Ko³odziejczyk
/// @date	09.01.2009
///
/// @brief	Klasa sytyczna posiadajaca metody korzystajace z CORBY i wykorzystywane przy polaczaniu
///
class IRemoteObjects
{

    private:

		/// lista obserwatorow
		std::vector<IRemoteObserver *> RemoteObserversList;

		// logger
		log4cxx::LoggerPtr logger;

    public:

		///
		/// konstruktor
		///
        IRemoteObjects()
		{
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("IRemoteObjects"));
			logger->setLevel(log4cxx::Level::getAll());
		}

        ///
		/// destruktor
		///
		virtual ~IRemoteObjects()
		{}

		///
		/// @param [in]	observerData	dane dla obserwatora
		///
		/// wywoluje metode Refresh na kazdym obserwatorze z kolekji
		///
        virtual int Notify(RemoteObserverData observerData);

        ///
		/// @param [in] observer	obiekt obserwatora
		///
		/// wyrejestrowuje danego obserwatora
		///
		virtual int UnregisterObserv(IRemoteObserver * observer);

        ///
		/// @param [in] observer	obiekt obserwatora
		///
		/// rejestruje obserwatora observer
		///
        virtual int RegisterObserv(IRemoteObserver * observer);

};  //end class IRemoteObjects

#endif
