#ifndef EVENTTYPE_H
#define EVENTTYPE_H
//Begin section for file EventType.h
//TODO: Add definitions that you want preserved
//End section for file EventType.h


//<p>
//    Konwencja:
//</p>
//<p>
//    Pierwszy wyraz mówi czy zdarzenie pochodzi od klienta, który komunikuje sie z serwerem
//</p>
//<p>
//    czy od innego serwera.
//</p>

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
enum EventType
{

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        SERVER_CONNECTED = 0,

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        SERVER_DISCONNECTED = 1,

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        CLIENT_CONNECTED = 2,

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        CLIENT_DISCONNECTED = 3,

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        CLIENT_SEND_MESSAGE = 4,

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        SERVER_PASS_MESSAGE = 5,

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        SERVER_UPDATE_CLIENT = 6,

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        CLIENT_CREATE_PIPE_REQUEST = 7,

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        SERVER_CREATE_PIPE_REQUEST = 8

}; //end enum EventType 

#endif
