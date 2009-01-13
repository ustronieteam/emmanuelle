#ifndef STATUSOBSERVER_H
#define STATUSOBSERVER_H

#include <log4cxx/logger.h>
#include <log4cxx/level.h>

#include "IObserverView.h"

#include "DataObserver.h"

///
/// StatusObserver
/// @brief Obserwator czekajacy na zmiane statusu
/// @author Wojciech Grzeskowiak
/// @date 2009.01.11
///
class StatusObserver : public DataObserver
{
    private:

		///
		/// Obiekt logowania.
		///
		log4cxx::LoggerPtr _logger;

		IObserverView * _view;

    public:

        ///
		/// Konstruktor.
		///
        StatusObserver(IObserverView * view);

        ///
		/// Destruktor.
		///
        virtual ~StatusObserver();

		///
		/// Metoda referesh.
		///
        virtual int Refresh(DataObserverData data);
};

#endif
