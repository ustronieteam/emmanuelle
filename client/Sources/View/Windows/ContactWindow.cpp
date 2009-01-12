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
	std::vector<ContactRecord> contacts = this->GetController()->GetContactsList();

	out	<< HEADLINE
		<< SIDE << "^ Kontakty\n" << SIDE << '\n';
	
	// Brak kontatkow na liscie.
	if ( contacts.size() == 0 )
	{
		out << SIDE << WIN_CONTACT_NO_CON << '\n';
	}
	// Istnieja kontakty na liscie.
	else
	{
		//Wypisywanie kontaktow.
		for(std::vector<ContactRecord>::iterator i = contacts.begin(); i != contacts.end(); i++)
		{
			out << SIDE << '\t';

			// Status.
			if ( (*i).isAvailable )
				out << WIN_CONTACT_CON_EN;
			else
				out << WIN_CONTACT_CON_DI;

			// Nazwa oraz numer.
			out << ' ' << (*i).userDesc.name << " (" << (*i).userDesc.number << ")\n";
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
		std::string uname;
		int	unumber;

		std::cin >> uname;
		std::cin >> unumber;

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
			if ( this->GetController()->AddContact(uname.c_str(), unumber) >= 0 )
				this->SetMsg(WIN_CONTACT_NEW_CON);
			else
				this->SetMsg(WIN_CONTACT_ER_NEW_CON2);
		}
	}
	// Usuniecie kontaktu.
	else if ( !cmd.compare("del") )
	{
		// Nazwa kontaktu do usuniecia.
		std::cin >> mcmd;

		if ( this->GetController()->DeleteContact(mcmd.c_str(), 0) >= 0 )
			this->SetMsg(WIN_CONTACT_DEL_CON);
		else
			this->SetMsg(WIN_CONTACT_ER_NO_CON);
	}
	else
		this->SetMsg(ER_NO_COMMAND);
}