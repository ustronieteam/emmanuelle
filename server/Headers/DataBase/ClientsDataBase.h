#ifndef CLIENTSDATABASE_H
#define CLIENTSDATABASE_H

#include "DataBase.h"

///
/// ClientDataBase
/// @brief Baza danych trzymajaca rekordy informacyjne o klientach.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.06
///
class ClientsDataBase : public DataBase
{
    public:

        ///
		/// Konstruktor bezparametrowy.
        ClientsDataBase();

        ///
		/// Konstruktor kopiujacy.
		/// @param[in] arg Baza danych do skopiowania.
        ClientsDataBase(const ClientsDataBase & arg);

        ///
		/// Operator przypisania.
		/// param[in] arg Baza danych ktora chcemy przypisac.
        ClientsDataBase & operator =(const ClientsDataBase & arg);

        ///
		/// Destruktor.
        virtual ~ClientsDataBase();

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
		/// Znajdz rekord klienta.
		/// @param[in] address Adres do wyszukania rekordu.
		/// @return ID wyszukanego rekordu.
		int Find(DomainData::Address & address);
};

#endif
