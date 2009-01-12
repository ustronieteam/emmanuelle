#ifndef DATAOBSERVERDATA_H
#define DATAOBSERVERDATA_H

#include "ContactRecord.h"

class DataObserverData
{

	ContactRecord cr;

    public:


        DataObserverData();

		void setContactRecord(const ContactRecord & c){cr = c;}
		const ContactRecord & getContactRecord(){return cr;}

        virtual ~DataObserverData();

};  //end class DataObserverData

#endif
