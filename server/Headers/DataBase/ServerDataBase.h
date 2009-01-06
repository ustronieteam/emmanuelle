#ifndef SERVERDATABASE_H
#define SERVERDATABASE_H

#include "DataBase.h"
#include "ServerRecord.h"

///
/// ClientDataBase
/// @brief Baza danych trzymajaca rekordy informacyjne o klientach.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.06
///
class ServerDataBase : public DataBase
{
	public:

        ///
		/// Konstruktor bezparametrowy.
        ServerDataBase();

        ///
		/// Konstruktor kopiujacy.
		/// @param[in] arg Baza danych do skopiowania.
        ServerDataBase(const ServerDataBase & arg);

        ///
		/// Operator przypisania.
		/// param[in] arg Baza danych ktora chcemy przypisac.
        ServerDataBase & operator =(const ServerDataBase & arg);

        ///
		/// Destruktor.
        virtual ~ServerDataBase();

		///
		/// Zamyka baze danych.
		/// @return ???
		virtual int Close();

		///
		/// Inicjalizuje baze danych.
		/// @return ???
		virtual int Initialize();

		/// Metody szukajace.

		///
		/// Znajdz rekord servera.
		/// @param[in] address Adres do wyszukania rekordu.
		/// @return ID wyszukanego rekordu.
		int Find(struct DomainData::Address & address);
};

#endif
