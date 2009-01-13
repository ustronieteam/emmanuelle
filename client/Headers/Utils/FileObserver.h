#ifndef FILEOBSERVER_H
#define FILEOBSERVER_H

#include <log4cxx/logger.h>
#include <log4cxx/level.h>

#include "IObserverView.h"

#include "IRemoteObserver.h"

///
/// FileObserver
/// @brief Obserwator czekajacy na plik.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.11
///
class FileObserver : public IRemoteObserver
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
        FileObserver(IObserverView * view);

		///
		/// Destruktor.
		///
        virtual ~FileObserver();

		///
		/// Metoda wywolujaca.
		///
		int Refresh(RemoteObserverData objectData);
};

#endif
