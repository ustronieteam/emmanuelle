#include "MessageObserver.h"

MessageObserver::MessageObserver(IObserverView * view) 
{
	// Inicjalizacja loggera.
	_logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("MessageObserver"));
	_logger->setLevel(LOGLEVEL);

	_view = view;
}

MessageObserver::~MessageObserver() 
{

}

int MessageObserver::Refresh(RemoteObserverData objectData)
{
	LOG4CXX_DEBUG(_logger, "Uruchomiono obserwatora wiadomosci. Typ: " << objectData.GetObserverType() );

	if ( objectData.GetObserverType() != MESSAGE )
		return -1;

	LOG4CXX_DEBUG(_logger, "Prawidlowy typ zdarzenia. Wywolanie obiektu widoku.");

	_view->Obsrv_ReciveMessage(objectData.GetUser(), objectData.GetSenderMessage());

	return 0;
}
