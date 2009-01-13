#ifndef DATAOBSERVER_H
#define DATAOBSERVER_H

#include "DataObserverData.h"

///
/// DataObserver
/// @brief Klasa bazowa dla obserwatorow danych.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.13
///
class DataObserver
{
    public:

        ///
		/// Kosntruktor.
		///
        DataObserver();

		///
		/// Destruktor.
		///
        virtual ~DataObserver();

        ///
		/// Metoda referesh.
		///
        virtual int Refresh(DataObserverData data) = 0;
};

#endif
