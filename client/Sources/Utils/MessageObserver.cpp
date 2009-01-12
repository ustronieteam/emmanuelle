#include "MessageObserver.h"

///
/// Konstruktor.
///
MessageObserver::MessageObserver() 
{
	// Inicjalizacja loggera.
	_logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("MessageObserver"));
	_logger->setLevel(log4cxx::Level::getAll());
}

///
/// Destruktor.
///
MessageObserver::~MessageObserver() 
{

}

///
/// Metoda wywolujaca.
///
int MessageObserver::Refresh(RemoteObserverData objectData)
{
	LOG4CXX_DEBUG(_logger, "Uruchomiono obserwatora wiadomosci. Typ: " << objectData.GetObserverType() );

	if ( objectData.GetObserverType() != MESSAGE )
		return -1;

	LOG4CXX_DEBUG(_logger, "Prawidlowy typ zdarzenia. Wywolanie obiektu widoku.");

	View::GetInstance()->Obsrv_ReciveMessage(objectData.GetSenderAddress(), objectData.GetSenderMessage());

	return 0;
}
