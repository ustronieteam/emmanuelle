#ifndef APLICATION_H
#define APLICATION_H

#include <iostream>
#include <fstream>
#include <string>

#include "IModel.h"
#include "Model.h"
#include "Controller.h"
#include "View.h"

#include <log4cxx/logger.h>
#include <log4cxx/level.h>



const std::string NADDRESS = "server_address";

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
		/// nazwa pliku konfiguracyjnego
		///
        const char * configFileName;

		// logger
		log4cxx::LoggerPtr logger;

		///
		/// konstruktor prywatny
		///
        Aplication(const char * fileName)
		{
			//logger
			logger = log4cxx::LoggerPtr(log4cxx::Logger::getLogger("AplicationClass"));
			logger->setLevel(log4cxx::Level::getAll());

			LOG4CXX_DEBUG(logger, "Stworzenie i powiazanie obiektow klienta ... ");

			// zapisanie nazwy pliku konfiguracyjnego
			configFileName = fileName;

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

		///
		///	@param [out]	address		miejsce gdzie ma byc zapisany adress serwera odczytany z pliku
		/// @return						0 - powodzenie, 1 - niepowodzenie
		///
		/// Otwarcie pliku konfiguracyjnego o nawie 'configFileName' i odczytanie 
		/// addresu serwera i przekazanie go do 'address'
		///
		bool openConfFile(std::string & address);

    public:

		///
		/// @return	obiekt aplikacji, ktory jest obiektem typu singleton
		///
		/// statyczna metoda zwracajaca wskaznik do obiektu klasy Server jesli
		/// istnieje badz tworzaca go jesli nie istnieje
		///
		static Aplication * GetInstance(const char * configFileName)
		{
			static Aplication * instance = new Aplication(configFileName);

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
