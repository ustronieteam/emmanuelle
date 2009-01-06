#ifndef RECORD_H
#define RECORD_H

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
    private:

        ///
		/// Identyfikator rekordu.
        int _recordId;

		///
		/// Zrodlo do generacji ID.
		static int _newId;

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
		/// param[in] arg Record ktory chcemy przypisac.
        Record & operator =(const Record & arg);

        ///
		/// Destruktor.
        virtual ~Record();

		///
		/// Zwraca identyfikator rekordu.
		/// @return Identyfikator rekordu.
        int GetRecordId() const;

		///
		/// Ustawia identyfikator rekordu.
		/// param[in] recordId Identyfikator do ustawienia.
        void SetRecordId(int & recordId);
};

#endif
