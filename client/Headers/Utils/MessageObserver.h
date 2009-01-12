#ifndef MESSAGEOBSERVER_H
#define MESSAGEOBSERVER_H

#include "View.h"
#include "RemoteObserverData.h"
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

    public:

		///
		/// Konstruktor.
		///
        MessageObserver();

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
