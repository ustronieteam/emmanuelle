#ifndef CLIENTDATAOBJECT_H
#define CLIENTDATAOBJECT_H
//Begin section for file ClientDataObject.h
//TODO: Add definitions that you want preserved
//End section for file ClientDataObject.h

#include "DataObserverData.h"
#include "DataObserver.h"


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class ClientDataObject
{

    //Begin section for ClientDataObject
    //TODO: Add attributes that you want preserved
    //End section for ClientDataObject

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        DataObserver * dataObserver;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        ClientDataObject();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~ClientDataObject();

        //get dataObserver
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual DataObserver * & get_dataObserver() = 0;

        //set dataObserver
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual void set_dataObserver(DataObserver * & dataObserver) = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int Notify(DataObserverData data) = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int Unregister(DataObserver & dataObserver) = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int Register(DataObserver & dataObserver) = 0;

};  //end class ClientDataObject

#endif
