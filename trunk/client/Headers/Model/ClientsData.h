#ifndef CLIENTSDATA_H
#define CLIENTSDATA_H

#include "ClientDataObject.h"
#include "Domaindata.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <boost/thread/mutex.hpp>
#include "Model/Exceptions/ModelExceptions.h"


struct ContactRecord
{
	DomainData::User userDesc;
	bool isAvailable;
};
typedef struct ContactRecord ContactRecord;
///
///@author	Marian Szczykulski
///@date	2009-01-12
///@brief	Klasa zawierajaca liste kontaktow klienta
class ClientsData : public ClientDataObject
{
	private:
		///
		/// Mutex, gdy¿ kolekcja moze byc uzywana w odzielnych watkach
		boost::mutex _mutex;

		///
		/// Kolekcja trzymajaca kontakty klienta
		std::map<std::string, ContactRecord> _records;


		///
		/// Flaga okreslajaca czy kolekcja ma byc wielowatkowa
		bool isConcurrent;
		///
		///Metody synchronizacji watkow
		void lock_mutex();
		void unlock_mutex();
    public:
		ClientsData(bool con = true);
        virtual ~ClientsData();


		std::vector<ContactRecord> GetContactsList() const; 
        int DeleteContact(DomainData::User usr);
        int AddContact(DomainData::User usr);
		const ContactRecord & FindByName(std::string name);

};  //end class ClientsData
#endif
