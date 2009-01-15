#include "StatusObserver.h"

StatusObserver::StatusObserver(IObserverView * view) 
{
	// Inicjalizacja loggera.
	_logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("StatusObserver"));
	_logger->setLevel(log4cxx::Level::getAll());

	_view = view;
}

StatusObserver::~StatusObserver() 
{

}

int StatusObserver::Refresh(DataObserverData data)
{
	LOG4CXX_DEBUG(_logger, "Uruchomiono obserwatora statusu. Wywolanie obiektu widoku." );

	_view->Obsrv_StatusChanged(data.getContactRecord());

	LOG4CXX_DEBUG(_logger, "Zakonczono obserwatora statusu." );

	return 1;
}
