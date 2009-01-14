#ifndef REMOTEOBSERVERDATA_H
#define REMOTEOBSERVERDATA_H

#include "DomainData.h"
#include "ObserverType.h"

///
/// RemoteObserverData
/// @brief Dane dla obserwatorow typu RemoteObserver.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.13
///
class RemoteObserverData
{
	private:

		///
		/// Rodzaj zdarzenia.
		///
		ObserverType _eventType;

		///
		/// Wyslana wiadomosc.
		///
		DomainData::Message _message;

		///
		/// Nadawca.
		///
		DomainData::User _user;

		///
		/// Nazwa pliku.
		///
		std::string _fileName;

    public:

		///
		/// Konstruktor.
		///
        RemoteObserverData();

		///
		/// Destruktor.
		///
        virtual ~RemoteObserverData();

		///
		/// Pobiera typ zdarzenia.
		/// @return Typ zdarzenia.
		///
		const ObserverType & GetObserverType() const;

		///
		/// Ustawia typ zdarzenia.
		/// @param[in] type Typ zdarzenia.
		///
		void SetObserverType(const ObserverType & type);

		///
		/// Pobiera wiadomosc.
		/// @return Wiadomosc.
		///
		const DomainData::Message & GetSenderMessage() const;

		///
		/// Ustawia wiadomosc.
		/// @param[in] msg Wiadomosc
		///
		void SetSenderMessage(const DomainData::Message & msg);

		///
		/// Pobiera nadawce.
		/// @return Nadawca
		///
		const DomainData::User & GetUser() const;

		///
		/// Ustawia nadawce.
		/// @parm[in] user Nadawca
		///
		void SetUser(const DomainData::User & user);
		
		///
		/// Pobiera nazwe pliku.
		/// @return Nazwa pliku.
		///
		const std::string & GetFileName() const;

		///
		/// Ustawia nazwe pliku.
		/// @parm[in] file Nazwa pliku.
		///
		void SetFileName(const std::string & file);
}; 

#endif
