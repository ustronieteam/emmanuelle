#include "DataBase.h"
//Begin section for file DataBase.cpp
//TODO: Add definitions that you want preserved
//End section for file DataBase.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
DataBase::DataBase() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
DataBase::DataBase(DataBase & arg) 
{
    //TODO Auto-generated method stub
    this->record = arg.record;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
DataBase & DataBase::operator =(const DataBase & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->record = arg.record;
    }

	return const_cast<DataBase &>(arg);
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
DataBase::~DataBase() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Record * & DataBase::get_record() 
{
    //TODO Auto-generated method stub
    return record;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void DataBase::set_record(Record * & record) 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int DataBase::GetRecord(int recordId) 
{
    //TODO Auto-generated method stub
    return 0;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int DataBase::GetAllRecords() 
{
    //TODO Auto-generated method stub
    return 0;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int DataBase::InsertRecord(Record record) 
{
    //TODO Auto-generated method stub
    return 0;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int DataBase::DeleteRecord(int recordId) 
{
    //TODO Auto-generated method stub
    return 0;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int DataBase::ModifyRecord(Record record) 
{
    //TODO Auto-generated method stub
    return 0;
}
