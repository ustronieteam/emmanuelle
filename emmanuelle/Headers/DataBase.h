#ifndef DATABASE_H
#define DATABASE_H
//Begin section for file DataBase.h
//TODO: Add definitions that you want preserved
//End section for file DataBase.h

#include "Record.h"


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class DataBase
{

    //Begin section for DataBase
    //TODO: Add attributes that you want preserved
    //End section for DataBase

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Record * record; // Zmieniæ na kolekcjê!!!!!!!!!!!!!!!!



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        DataBase();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        DataBase(DataBase & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        DataBase & operator =(const DataBase & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~DataBase();

        //get record
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline Record * & get_record();

        //set record
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline void set_record(Record * & record);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int GetRecord(int recordId);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
         GetAllRecords();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int InsertRecord(Record record);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int DeleteRecord(int recordId);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int ModifyRecord(Record record);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int Close() = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int Initialize() = 0;

};  //end class DataBase

#endif
