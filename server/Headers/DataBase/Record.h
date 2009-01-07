#ifndef RECORD_H
#define RECORD_H

//#include <boost/thread/mutex.hpp>

#include "IServerServer.h"
#include "IClientServer.h"

///
/// Rekord
/// @brief Podstawowa jednosta informacji w bazie danych.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.06
///
class Record
{
    protected:

        ///
		/// Identyfikator rekordu.
        int _recordId;

		///
		/// Adres klienta.
		struct DomainData::Address _address;

		///
		/// Broker
		CORBA::ORB_var _broker;

	private:

		///
		/// Zrodlo do generacji ID.
		static int _newId;

		///
		/// Mutex potrzebny go generowania id rekordow.
		//static boost::mutex _mutex;

    public:

        ///
		/// Konstruktor bezparametrowy.
        Record();

		///
		/// Konstruktor kopiujacy.
		/// @param[in] arg Record do skopiowania.
        Record(const Record & arg);

        ///
		/// Operator przypisania.
		/// @param[in] arg Record ktory chcemy przypisac.
        Record & operator =(const Record & arg);

        ///
		/// Destruktor.
        virtual ~Record();

		///
		/// Zwraca identyfikator rekordu.
		/// @return Identyfikator rekordu.
        const int & GetRecordId() const;

		///
		/// Ustawia identyfikator rekordu.
		/// @param[in] recordId Identyfikator do ustawienia.
        void SetRecordId(const int & recordId);

		///
		/// Pobiera adresu.
		/// @return Adres.
		const struct DomainData::Address & GetAddress() const;

		///
		/// Ustawia adres.
		/// @param[in] address Adres.
		void SetAddress(const struct DomainData::Address & address);

		///
		/// Pobiera broker.
		/// @return Broker.
		const CORBA::ORB_var & GetBroker() const;

		///
		/// Ustawia broker.
		/// @param[in] broker Broker.
		void SetBroker(const CORBA::ORB_var & broker);
};

#endif
