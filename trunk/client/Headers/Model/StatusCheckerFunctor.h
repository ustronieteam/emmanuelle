#ifndef _STATUSCHECKER_FUNCTOR_H_
#define _STATUSCHECKER_FUNCTOR_H_

#include <boost/shared_ptr.hpp>

#include "ClientsData.h"
#include <log4cxx/logger.h>
#include <log4cxx/level.h>

class StatusCheckerFunctor
{
	private:
		log4cxx::LoggerPtr logger;
		boost::shared_ptr<ClientsData> clientsData;
	public:
		StatusCheckerFunctor(boost::shared_ptr<ClientsData> clData)
		{
			clientsData = clData;
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("StatusCheckerFunctor"));
			logger->setLevel(log4cxx::Level::getAll());
		}

		int operator()();

};


#endif