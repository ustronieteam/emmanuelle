#include "ContactWindow.h"

///
/// Konstruktor.
/// @param[in] controller Kontroler.
///
ContactWindow::ContactWindow(Controller * controller, std::list<CONTACT> * contacts) : Window(controller, WIN_CONTACT)
{
	_contacts = contacts;
}

///
/// Renderowanie okienka.
/// @param[in] o Strumien do ktorego renderujemy obraz.
///
void ContactWindow::Render(std::ostream & out)
{
	out	<< HEADLINE
		<< SIDE << "^ Kontakty\n" << SIDE << '\n';

	// Brak kontatkow na liscie.
	if ( this->_contacts->size() == 0 )
	{
		out << SIDE << WIN_CONTACT_NO_CON << '\n';
	}
	// Istnieja kontakty na liscie.
	else
	{
		// Wypisywanie kontaktow.
		for(std::list<CONTACT>::iterator i = this->_contacts->begin(); i != this->_contacts->end(); i++)
		{
			out << SIDE << '\t';

			// Status.
			if ( (*i).status )
				out << WIN_CONTACT_CON_EN;
			else
				out << WIN_CONTACT_CON_DI;

			// Nazwa oraz numer.
			out << ' ' << (*i).name << " (" << (*i).number << ")\n";
		}
	}

	out << SIDE << '\n' << LINE;

	if ( ! this->GetMsg().empty() )
	{
		out << SIDE << this->GetMsg() << '\n';
		this->ClearMsg();
	}

	out << PROMPT;
}

///
/// Komenda przekazana do okna.
/// @param[in] cmd Komenda.
///
void ContactWindow::Command(std::string & cmd)
{
	std::string mcmd;

	// Dodanie kontaktu.
	if ( !cmd.compare("add") )
	{
		CONTACT newContact;

		newContact.status = false;

		std::cin >> newContact.name;
		std::cin >> newContact.number;

		/* Sprawdzanie poprawnosci. */
		if ( std::cin.fail() )
		{
			this->SetMsg(WIN_CONTACT_ER_NEW_CON);
			std::cin.clear( std::cin.rdstate() & ~std::ios::failbit );

			// Pobranie smieci.
			std::cin >> mcmd;
		}
		else
		{
			this->_contacts->push_back(newContact);
			this->SetMsg(WIN_CONTACT_NEW_CON);
		}
	}
	// Usuniecie kontaktu.
	else if ( !cmd.compare("del") )
	{
		std::list<CONTACT>::iterator i;

		// Nazwa kontaktu do usuniecia.
		std::cin >> mcmd;

		for(i = this->_contacts->begin(); i != this->_contacts->end(); i++)
			if ( !(*i).name.compare(mcmd) )
				break;

		if ( i != this->_contacts->end() )
		{
			this->_contacts->erase(i);
			this->SetMsg(WIN_CONTACT_DEL_CON);
		}
		else
			this->SetMsg(WIN_CONTACT_ER_NO_CON);
	}
	else
		this->SetMsg(NO_COMMAND);
}