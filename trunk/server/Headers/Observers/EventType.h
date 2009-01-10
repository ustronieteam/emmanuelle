#ifndef EVENTTYPE_H
#define EVENTTYPE_H




///@author Marian Szczykulski
///@date 2009-01-09
///@brief Typ wyliczeniowy (rodzaj zdarzenia)
///@brief    Konwencja:
///@brief    Pierwszy wyraz mówi czy zdarzenie pochodzi od klienta, który komunikuje sie z serwerem
///@brief    czy od innego serwera.
enum EventType
{
        SERVER_CONNECTED = 0,
        SERVER_DISCONNECTED = 1,
        CLIENT_CONNECTED = 2,
        CLIENT_DISCONNECTED = 3,
        CLIENT_SEND_MESSAGE = 4,
        SERVER_PASS_MESSAGE = 5,
        SERVER_UPDATE_CLIENT = 6,
        CLIENT_CREATE_PIPE_REQUEST = 7,
        SERVER_CREATE_PIPE_REQUEST = 8

}; //end enum EventType 

#endif
