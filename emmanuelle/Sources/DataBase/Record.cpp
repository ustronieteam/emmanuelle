#include "Record.h"
//Begin section for file Record.cpp
//TODO: Add definitions that you want preserved
//End section for file Record.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Record::Record() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Record::Record(Record & arg) 
{
    //TODO Auto-generated method stub
    this->recordId = arg.recordId;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Record & Record::operator =(const Record & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->recordId = arg.recordId;
    }
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Record::~Record() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int & Record::get_recordId() 
{
    //TODO Auto-generated method stub
    return recordId;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void Record::set_recordId(int & recordId) 
{
    //TODO Auto-generated method stub
    this->recordId = recordId;
}
