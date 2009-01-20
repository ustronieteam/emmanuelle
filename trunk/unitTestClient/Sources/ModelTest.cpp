#include "ModelTest.h"
#include "Model.h"

void test_case_ContactDataBase()
{
	BOOST_TEST_MESSAGE("****** TEST BAZY KONTAKTOW ********");
	ClientsData cl_data(true); //Utworzenie listy kontaktów (wielowatkowej)
	DomainData::User usr;
	BOOST_TEST_MESSAGE("Usuniecie nie istniejacego rekordu");
	BOOST_CHECK_THROW(cl_data.DeleteContact(usr),ContactNotFoundException); //Usuniecie nie istniejacego rekordu
	BOOST_TEST_MESSAGE("Wyszukanie nie istniejacego rekordu");
	BOOST_CHECK_THROW(cl_data.FindByName(""),ContactNotFoundException);
	
	usr.name = CORBA::string_dup("TestName");
	BOOST_TEST_MESSAGE("TestWstawiania rekordu");
	BOOST_CHECK_EQUAL(cl_data.AddContact(usr),0);

	BOOST_TEST_MESSAGE("Ponowne wstawienie tego samego rekordu");
	BOOST_CHECK_THROW(cl_data.AddContact(usr),ContactAlreadyExistsException );

	BOOST_TEST_MESSAGE("Wyszukiwanie istniejacego rekordu");
	ContactRecord cr = cl_data.FindByName(usr.name.in());
	BOOST_CHECK_EQUAL(std::string(cr.userDesc.name.in()),"TestName");

	BOOST_TEST_MESSAGE("Usuniecie istniejacego rekordu");
	BOOST_CHECK_EQUAL(cl_data.DeleteContact(usr),1);

	BOOST_TEST_MESSAGE("****** KONIEC TESTU BAZY KONTAKTOW ********");
}
void test_case_Client()
{
	BOOST_TEST_MESSAGE("****** TEST CONNECTORA CLIENT ********");
	Client cl;
	BOOST_TEST_MESSAGE("Proba podlaczenia sie do serwera(bez ustalenia jego adresu)");
	BOOST_CHECK_THROW(cl.ConnectToServer(), std::exception);

	DomainData::Address addr;
	addr.localization = CORBA::string_dup("addres");
	BOOST_TEST_MESSAGE("Proba podlaczenia sie do serwera(po ustaleniu jego adresu)");
	BOOST_CHECK_THROW(cl.ConnectToServer(), std::exception);
	DomainData::User usr1;
	BOOST_TEST_MESSAGE("Próba rozlaczenia sie bez podlaczania");
	BOOST_CHECK_EQUAL(cl.Disconnect(usr1), -2);

	
	DomainData::User usr2;
	DomainData::Message msg;
	BOOST_TEST_MESSAGE("Proba wyslania wiadomoœci bez podlaczania");
	BOOST_CHECK_EQUAL(cl.SendMessageToClient(usr1, usr2, msg), -2);

	DomainData::File fil;
	BOOST_TEST_MESSAGE("Proba wyslania pliku bez podlaczenia sie");
	BOOST_CHECK_EQUAL(cl.SendPackage(usr1,usr2,fil), -1);

	BOOST_TEST_MESSAGE("****** KONIEC TESTU CONNECTORA CLIENT ********");
}
void test_case_Model()
{
	BOOST_TEST_MESSAGE("****** TEST INTERFEJSU MODELU ********");
	IModel * modelAbstr = Model::GetInstance();

	//Zwiazane z zarzadzaniem kontaktami
	DomainData::User usr;
	BOOST_TEST_MESSAGE("Dodanie kontaktu");
	BOOST_CHECK_EQUAL(modelAbstr->AddContact(usr), 0);
	BOOST_TEST_MESSAGE("Ponowne dodanie kontaktu");
	BOOST_CHECK_THROW(modelAbstr->AddContact(usr), ContactAlreadyExistsException);
	BOOST_TEST_MESSAGE("Usuniecie kontaktu");
	BOOST_CHECK_EQUAL(modelAbstr->DeleteContact(usr), 0);
	BOOST_TEST_MESSAGE("Ponowne usuniecie kontaktu");
	BOOST_CHECK_THROW(modelAbstr->DeleteContact(usr), ContactNotFoundException);

	//Zwiazane z polaczeniami
	
	BOOST_TEST_MESSAGE("Rozlaczenie sie od serwera");
	BOOST_CHECK_EQUAL(modelAbstr->Disconnect() , 0);



	BOOST_TEST_MESSAGE("****** KONIEC TESTU INTERFEJSU MODELU ********");
}