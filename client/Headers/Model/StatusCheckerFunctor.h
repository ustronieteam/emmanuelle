#ifndef _STATUSCHECKER_FUNCTOR_H_
#define _STATUSCHECKER_FUNCTOR_H_

#include <boost/shared_ptr.hpp>

#include "ClientsData.h"
#include "Client.h"

#include <vector>

#include <log4cxx/logger.h>
#include <log4cxx/level.h>

class StatusCheckerFunctor
{
	private:
		static const int sleepTime = 10000;
		log4cxx::LoggerPtr logger;
		boost::shared_ptr<ClientsData> clientsData;
		boost::shared_ptr<Client> _client;
	public:
		StatusCheckerFunctor(boost::shared_ptr<ClientsData> clData, boost::shared_ptr<Client> client)
		{
			clientsData = clData;
			_client = client;
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("StatusCheckerFunctor"));
			logger->setLevel(log4cxx::Level::getAll());
		}

		int operator()();

};


#endif