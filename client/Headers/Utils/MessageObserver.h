#ifndef MESSAGEOBSERVER_H
#define MESSAGEOBSERVER_H

#include <log4cxx/logger.h>
#include <log4cxx/level.h>

#include "IObserverView.h"

#include "IRemoteObserver.h"

///
/// MessageObserver
/// @brief Obserwator czekajacy na wiadomosci.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.11
///
class MessageObserver : public IRemoteObserver
{
	private:

		///
		/// Obiekt logowania.
		///
		log4cxx::LoggerPtr _logger;

		///
		/// Interfejs modelu do wywolan.
		///
		IObserverView * _view;

    public:

		///
		/// Konstruktor.
		///
        MessageObserver(IObserverView * view);

		///
		/// Destruktor.
		///
        virtual ~MessageObserver();
		
		///
		/// Metoda wywolujaca.
		///
		int Refresh(RemoteObserverData objectData);
};

#endif
