#ifndef APLICATION_H
#define APLICATION_H

#include <iostream>
#include <string>
#include <boost/thread.hpp>

#include <log4cxx/logger.h>
#include <log4cxx/level.h>

class Controller;
class View;
class IModel;

///
/// @author	Mateusz Ko³odziejczyk
/// @date	06.01.2009
///
/// @brief	G³ówna klasa aplikacji. Startuje program klienta i wi¹¿e odpowiednie warstwy ze sob¹.
///
class Aplication
{
    private:

		///
		/// obiekt kontrolera
		///
		boost::shared_ptr<Controller> controller;

		/// 
		/// obiekt widoku
		///
        boost::shared_ptr<View> view;

		///
		/// obiekt modelu
		///
        boost::shared_ptr<IModel> iModel;

		// logger
		log4cxx::LoggerPtr logger;

		///
		/// konstruktor prywatny
		///
        Aplication()
		{
			//logger
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("ServerLogicRunnable"));
			logger->setLevel(log4cxx::Level::getAll());
		}

    public:

		///
		/// statyczna metoda zwracajaca wskaznik do obiektu klasy Server jesli
		/// istnieje badz tworzaca go jesli nie istnieje
		///
		static Aplication * GetInstance()
		{
			static Aplication * instance = new Aplication();

			return instance;
		}

		///
		/// destruktor
		///
        ~Aplication()
		{}

        int Run();

};  //end class Aplication

#endif
