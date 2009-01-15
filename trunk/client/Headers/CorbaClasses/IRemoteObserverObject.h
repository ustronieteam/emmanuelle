#ifndef IREMOTEOBSERVEROBJECT_H
#define IREMOTEOBSERVEROBJECT_H

#include "RemoteObserverData.h"

#include "IRemoteObserver.h"
#include <iostream>
#include <vector>

#include <log4cxx/logger.h>
#include <log4cxx/level.h>

///
/// @author	Mateusz Ko³odziejczyk
/// @date	10.01.2009
///
/// @brief	Interfejs ktory implementuja klasy namistek udostapnianych przez klienta
///
/// Rejestruje i wyrejestrowuje obiekty obserwatorw \; posiada metode Notify ktora
/// wywoluje metode Refresh na kazdym obserwatorze w koleksji obserwatorow (ktora
/// takze znajduje sie w tej klasie)
///
class IRemoteObserverObject
{

    private:

		///
		/// kolekcji obserwatorow, czyli obiektow klasy IRemoteObserver
		///
        IRemoteObserver * observer;

		// logger
		log4cxx::LoggerPtr logger;

    public:

		///
		/// konstruktor
		///
        IRemoteObserverObject()
		{
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("IRemoteObjects"));
			logger->setLevel(log4cxx::Level::getAll());
		}

		///
		/// destruktor
		///
        virtual ~IRemoteObserverObject()
		{
		}

		///
		/// wyrejestrowuje danego obserwatora
		///
        virtual int UnregisterObserv();

		///
		/// @param [in] observer	obiekt obserwatora
		///
		/// rejestruje obserwatora observer
		///
        virtual int RegisterObserv(IRemoteObserver * observer);

		///
		/// @param [in] objectData	dane 
		///
		/// wywoluje metode Refresh na kazdym obserwatorze z kolekcji RemoteObserversList
		///
        virtual void Notify(RemoteObserverData objectData);

};  //end class IRemoteObserverObject

#endif
