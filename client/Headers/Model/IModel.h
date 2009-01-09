#ifndef IMODEL_H
#define IMODEL_H
//Begin section for file IModel.h
//TODO: Add definitions that you want preserved
//End section for file IModel.h

#include "../Utils/DataObserver.h"
#include "../Utils/FilePackage.h"
#include "../Utils/IRemoteObserver_0.h"


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class IModel
{

    //Begin section for IModel
    //TODO: Add attributes that you want preserved
    //End section for IModel



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        IModel();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~IModel();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int AddStatusObserver(DataObserver & observer) = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int SendPackage(FilePackage package) = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int DeleteContact() = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int SendMessage() = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int AddContact() = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int Disconnect() = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual bool ConnectToServer() = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int AddFileObserver(IRemoteObserver_0 & observer) = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int AddMessageObserver(IRemoteObserver_0 & observer) = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual  int GetContactsList() = 0; // TODO: poprawic typ zwracany

};  //end class IModel

#endif
