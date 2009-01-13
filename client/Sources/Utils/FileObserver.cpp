#include "FileObserver.h"

///
/// Konstruktor.
///
FileObserver::FileObserver(IObserverView * view) 
{
    // Inicjalizacja loggera.
	_logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("FileObserver"));
	_logger->setLevel(log4cxx::Level::getAll());

	_view = view;
}

///
/// Destruktor.
///
FileObserver::~FileObserver() 
{

}

///
/// Metoda wywolujaca.
///
int FileObserver::Refresh(RemoteObserverData objectData)
{
	LOG4CXX_DEBUG(_logger, "Uruchomiono obserwatora plikow. Typ: " << objectData.GetObserverType() );

	if ( objectData.GetObserverType() != FFILE )
		return -1;

	LOG4CXX_DEBUG(_logger, "Prawidlowy typ zdarzenia. Wywolanie obiektu widoku.");

	_view->Obsrv_File();

	return 0;
}
