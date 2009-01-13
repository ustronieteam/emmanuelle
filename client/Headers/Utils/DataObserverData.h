#ifndef DATAOBSERVERDATA_H
#define DATAOBSERVERDATA_H

#include "ContactRecord.h"

class DataObserverData
{
	private:

		ContactRecord cr;

    public:

        DataObserverData();

        virtual ~DataObserverData();

		void setContactRecord(const ContactRecord & c)
		{
			cr = c;
		}

		const ContactRecord & getContactRecord()
		{
			return cr;
		}
};

#endif
