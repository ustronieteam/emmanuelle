#ifndef APLICATION_H
#define APLICATION_H

#include <iostream>
#include <fstream>
#include <string>
#include <boost/regex.hpp>

#include "IModel.h"
#include "Model.h"
#include "Controller.h"
#include "View.h"

#include <log4cxx/logger.h>
#include <log4cxx/level.h>


const std::string NADDRESS = "server_address";

///
/// @author	Mateusz Ko�odziejczyk
/// @date	06.01.2009
///
/// @brief	G��wna klasa aplikacji. Startuje program klienta i wi��e odpowiednie warstwy ze sob�.
///
class Aplication
{
    private:

		///
		/// obiekt kontrolera
		///
		Controller * controller;

		/// 
		/// obiekt widoku
		///
		View * view;

		///
		/// obiekt modelu
		///
        IModel * model;

		// logger
		log4cxx::LoggerPtr logger;

		///
		/// konstruktor prywatny
		///
        Aplication()
		{
			//logger
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("AplicationClass"));
			logger->setLevel(LOGLEVEL);

			LOG4CXX_DEBUG(logger, "Stworzenie i powiazanie obiektow klienta ... ");

			// stworzenie obietku modelu
			model = Model::GetInstance();
			LOG4CXX_DEBUG(logger, "... stworzono model!");

			// stworzenie obiektu kontrolera i powiazanie go z modelem
			controller = Controller::GetInstance();
			controller->SetModel(model);
			LOG4CXX_DEBUG(logger, "... stworzono kontroler!");

			// utworzenie obiektu widoku i powiazanie go z kontrolerem
			view = View::GetInstance();
			view->SetController(controller);
			LOG4CXX_DEBUG(logger, "... stworzono widok!");
		}

    public:

		///
		/// @return	obiekt aplikacji, ktory jest obiektem typu singleton
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

		///
		/// @return	0 - poprawne zamkniecie, 1 - niepoparwne zamkniecie
		///
		/// uruchomienie klienta
		///
        int Run();

};  //end class Aplication

#endif
