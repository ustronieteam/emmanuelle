#ifndef CLIENT_H
#define CLIENT_H

#include "IRemoteObserver.h"
#include "IServerClient.h"

///@author Marian Szczykulski
///@brief Model klienta jest
class Client
{

	private:
		IServerClient_var connectedServerInstance; //Namiastka serwera do którego jestesmy pod³¹czeni

    public:

        Client();
        virtual ~Client();
        int AddFileObserver(IRemoteObserver & fileObserver);
        int SendPackage();
        int ConnectToServer();
        int Disconnect();
        int SendMessage();
        int AddMessageObserver(IRemoteObserver & messageObserver);

};  //end class Client

#endif
