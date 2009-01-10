#ifndef IMODEL_H
#define IMODEL_H
//Begin section for file IModel.h
//TODO: Add definitions that you want preserved
//End section for file IModel.h

#include "DataObserver.h"
#include "FilePackage.h"
#include "IRemoteObserver.h"


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

		virtual void SetServerAddress(const char * addr) = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int AddStatusObserver(DataObserver & observer) = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int SendPackage(FilePackage package) = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int DeleteContact() = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        //virtual int SendMessage() = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int AddContact() = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int Disconnect() = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual bool ConnectToServer() = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int AddFileObserver(IRemoteObserver & observer) = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual int AddMessageObserver(IRemoteObserver & observer) = 0;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual  int GetContactsList() = 0; // TODO: zmienic typ zwracany

};  //end class IModel

#endif
