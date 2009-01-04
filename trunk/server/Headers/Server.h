#ifndef SERVER_H
#define SERVER_H
//Begin section for file Server.h
//TODO: Add definitions that you want preserved
//End section for file Server.h

#include "DataBase.h"
#include "DataBase/ClientsDataBase.h"
#include "DataBase/ServerDataBase.h"

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class Server
{

    //Begin section for Server
    //TODO: Add attributes that you want preserved
    //End section for Server

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        //DataBase dataBase[2]; //Jedna typu klient jedna typu server
		ClientsDataBase * clientDataBaseObj;
		ServerDataBase * serverDataBaseObj;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        const char * configFileName;

		static Server * instance;

        //<p>
        //    Inicjalizacja servera.
        //</p>
        //<p>
        //    Utworzenie objektów zdalnych i wrzucenie go na broker(udostêpnienie)
        //</p>
        //<p>
        //    Ponad to nale¿y zainstalowaæ ka¿demu obiektowi zdalnemu po jednym obserwatorze
        //</p>
        //<p>
        //    Tworzac obserwatorów nale¿y im dostarczyæ odpowiedniegi obiektu&nbsp;bazy danych
        //</p><br />
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        bool init();


    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Server(const char * fileName);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        //Server(const Server & arg);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~Server();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        bool run();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        static Server * getInstance(const char * fileName)
		{
		    if(!instance)
				instance = new Server(fileName);

			return instance;
		}

};  //end class Server

#endif
