#ifndef SERVERRECORD_H
#define SERVERRECORD_H

#include "Record.h"

///
/// Server Rekord
/// @brief Podstawowa jednosta informacji w bazie danych o serwerach.
/// @author Wojciech Grzeskowiak
/// @date 2009.01.06
///
class ServerRecord : Record
{
	private:

		///
		/// Namiastka serwera.
		IServerServer_var _serverRemoteInstance;

    public:

        ///
		/// Konstruktor bezparametrowy.
        ServerRecord();

		///
		/// Konstruktor kopiujacy.
		/// @param[in] arg Record do skopiowania.
        ServerRecord(const ServerRecord & arg);

        ///
		/// Operator przypisania.
		/// param[in] arg Record ktory chcemy przypisac.
        ServerRecord & operator =(const ServerRecord & arg);

        ///
		/// Destruktor.
        virtual ~ServerRecord();

		///
		/// Pobiera namiastke serwera.
		/// @return Namiastka servera.
		IServerServer_var GetServerRemoteInstance() const;

		///
		/// Ustawia namiastke servera.
		/// @param[in] serverRemoteInstance Namiastka servera.
		void SetServerRemoteInstance(IServerServer_var serverRemoteInstance);
};

#endif
