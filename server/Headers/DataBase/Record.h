#ifndef RECORD_H
#define RECORD_H
//Begin section for file Record.h
//TODO: Add definitions that you want preserved
//End section for file Record.h


//Trzyma tak¿e zdalne objekty odpowiadaj¹ce danemu rekordowi
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class Record
{

    //Begin section for Record
    //TODO: Add attributes that you want preserved
    //End section for Record

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int recordId;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Record();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Record(Record & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Record & operator =(const Record & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~Record();

        //get recordId
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline int & get_recordId();

        //set recordId
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        inline void set_recordId(int & recordId);

};  //end class Record

#endif
