#ifndef APLICATION_H
#define APLICATION_H

#include "CorbaConnector.h"

#include <iostream>
#include <string>
#include <boost/thread.hpp>

#include "CorbaConnector.h"
#include "IClientClient.h"
#include "IClientClient_impl.h"
#include "IClientServer.h"
#include "IClientServer_impl.h"

#include "IModel.h"
#include "Model.h"
#include "Controller.h"
#include "View.h"

#include <log4cxx/logger.h>
#include <log4cxx/level.h>

///
/// @author	Mateusz Ko³odziejczyk
/// @date	06.01.2009
///
/// @brief	G³ówna klasa aplikacji. Startuje program klienta i wi¹¿e odpowiednie warstwy ze sob¹.
///
class Aplication : CorbaConnector
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

		///
		/// wskaznik do obiektu zdalnego udostepnianego serwerom
		///
		IClientServer_impl * serverImpl;

		///
		/// wskaznik do obiektu zdalnego udostepnianego klientom
		///
		IClientClient_impl * clientImpl;

		// logger
		log4cxx::LoggerPtr logger;

		///
		/// konstruktor prywatny
		///
        Aplication()
		{
			//logger
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("AplicationClass"));
			logger->setLevel(log4cxx::Level::getAll());

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

		///
		/// Stworzenie brokera po stronie klienta, zarejestrownie obiektow zdalnych i uruchomienie
		/// nasluchiwania na porcie CLNTPORT
		///
		void ActivateListning();

};  //end class Aplication

#endif
