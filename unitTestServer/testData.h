#ifndef _TEST_DATA_H_
#define _TEST_DATA_H_
#include "ServerDataBase.h"
#include "ClientsDataBase.h"
#include <boost/test/unit_test.hpp>
#include <boost/shared_ptr.hpp>

ServerDataBase * sdb_gl = ServerDataBase::GetInstance();
boost::shared_ptr<ServerDataBase> ptr_sdb_gl(sdb_gl);

ClientsDataBase * cdb_gl = ClientsDataBase::GetInstance();
boost::shared_ptr<ClientsDataBase> ptr_cdb_gl(cdb_gl);

#endif