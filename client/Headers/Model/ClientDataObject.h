#ifndef CLIENTDATAOBJECT_H
#define CLIENTDATAOBJECT_H
//Begin section for file ClientDataObject.h
//TODO: Add definitions that you want preserved
//End section for file ClientDataObject.h

#include "DataObserverData.h"
#include "DataObserver.h"

#include <iostream>
#include <vector>

#include <log4cxx/logger.h>
#include <log4cxx/level.h>
///
///@author Marian Szczykulski
///@date 2009-01-13
///@brief Objekt obserwowany(Status)
class ClientDataObject
{


    private:

		std::vector< DataObserver *> dataObserver;
		
		// logger
		log4cxx::LoggerPtr logger;
    public:

        ClientDataObject();
        virtual ~ClientDataObject();


        virtual int Notify(DataObserverData data);
        virtual int Unregister(DataObserver & dat);
        virtual int Register(DataObserver * dat);

};  //end class ClientDataObject

#endif
