#ifndef CLIENTSDATA_H
#define CLIENTSDATA_H

#include "ClientDataObject.h"
#include "DomainData.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <boost/thread/mutex.hpp>
#include "Model/Exceptions/ModelExceptions.h"
//Do pliku konfiguracyjnego
#include <boost/program_options.hpp>
#include <fstream>
#include "IModel.h"
#include "ContactRecord.h"
namespace po = boost::program_options;

///
///@author	Marian Szczykulski
///@date	2009-01-12
///@brief	Klasa zawierajaca liste kontaktow klienta
///
class ClientsData : public ClientDataObject
{
	private:
		///
		///nazwa pliku konfiguracyjnego
		//
		static const std::string configFileName;
		///
		/// Mutex, gdy¿ kolekcja moze byc uzywana w odzielnych watkach
		///
		boost::mutex _mutex;

		///
		///Wlasny Record Klienta
		///
		ContactRecord ownRecord;

		DomainData::Mode _mode;
		///
		/// Kolekcja trzymajaca kontakty klienta
		///
		std::map<std::string, ContactRecord> _records;


		///
		/// Flaga okreslajaca czy kolekcja ma byc wielowatkowa
		///
		bool isConcurrent;

		///
		///Czytanie z pliku conf odpowiednich danych
		///
		void readClientName();

		///
		///Metody synchronizacji watkow
		///
		void lock_mutex();
		void unlock_mutex();
    public:
		ClientsData(bool con = true);
        virtual ~ClientsData();

		const ContactRecord & GetOwnRecord() const;
		void SetOwnName(const char * c);
		void SetOwnNumber(long l);
		void SetMyAvailability(bool b);


		std::vector<ContactRecord> GetContactsList() const; 
        int DeleteContact(DomainData::User usr);
        int AddContact(DomainData::User usr);
		const ContactRecord & FindByName(std::string name);
		bool ModifyRecord(const ContactRecord & cr);
		void setOwnMode(DomainData::Mode m){_mode = m;}
		DomainData::Mode getOwnMode(){return _mode;}

};  //end class ClientsData

std::ostream & operator<<(std::ostream & os, const ClientsData & db);
#endif
