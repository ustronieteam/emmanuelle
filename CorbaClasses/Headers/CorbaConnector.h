#ifndef CORBACONNECTOR_H
#define CORBACONNECTOR_H

#include <OB/CORBA.h>
#include <OB/BootManager.h>
#include <OB/OCI_IIOP.h>

#include "IServerServer.h"
#include "IServerClient.h"
#include "IClientServer.h"
#include "IClientClient.h"

#include <iostream>

static const std::string SRVPORT = "7080";
static const std::string CLNTPORT = "7081";

class CorbaConnector
{
	public:

		///
		/// statyczna metoda sluzaca do pobrania adresu serwera juz podlaczonego
		/// do danego serwera
		///
		static char * GetRemotedAddress(const char * port)
		{
			char* orb_options[] = { "-OAport", const_cast<char *>(port) };
			int optc = sizeof(orb_options)/sizeof(char *);

			CORBA::ORB_var orb = CORBA::ORB_init(optc, orb_options);

			CORBA::Object_var baseCurrent = orb->resolve_initial_references("OCICurrent");
			OCI::Current_var current = OCI::Current::_narrow(baseCurrent);

			OCI::TransportInfo_var info = current->get_oci_transport_info();
			OCI::IIOP::TransportInfo_var iiopInfo = OCI::IIOP::TransportInfo::_narrow(info);

			if(CORBA::is_nil(iiopInfo))
				return "";

			char * str = iiopInfo->remote_addr();

			return str;
		}


		///
		/// @param [in]		address	adres serwera do ktorego chcemy sie polaczyc
		/// @param [out]	orb		wsk na obiekt brokera - trzyma polaczenie
		/// @param [out]	server	wsk na obiekt namiastki
		/// @return			0 - powodznie, 1 - niepowodzenie
		///
		/// Laczy sie do serwera o zadanym adresie nasluchujacym na porcie LPORT; efektem polaczenia jest 
		/// zwrocenie wskaznikow do brokera polaczenia i obiektu namastki
		///
		static bool connectToServerServer(std::string address, CORBA::ORB_out orb, IServerServer_out server)
		{
			char* orb_options[] = { const_cast<char *>(address.c_str()) , const_cast<char *>(SRVPORT.c_str()) };
			int optc = sizeof(orb_options)/sizeof(char *);

			orb = CORBA::ORB_init(optc, orb_options);

			CORBA::String_var strIOR = CORBA::string_dup("corbaloc:iiop:");
			strIOR += address.c_str();
			strIOR += ":";
			strIOR += SRVPORT.c_str();
			strIOR += "/serverserver";

			CORBA::Object_var oServer = orb->string_to_object(strIOR);
			if (CORBA::is_nil(oServer))
			{
				std::cout << "oServer nil" << std::endl;
				return false;
			}

			server = IServerServer::_narrow(oServer);
		    
			if (CORBA::is_nil(server))
			{
				std::cout << "server nil" << std::endl;
				return false;
			}

			return true;
		}

		///
		/// @param [in]		address	adres serwera do ktorego chcemy sie polaczyc
		/// @param [out]	orb		wsk na obiekt brokera - trzyma polaczenie
		/// @param [out]	client	wsk na obiekt namiastki
		/// @return			0 - powodznie, 1 - niepowodzenie
		///
		/// Laczy sie do klienta o zadanym adresie nasluchujacym na porcie LPORT; efektem polaczenia jest 
		/// zwrocenie wskaznikow do brokera polaczenia i obiektu namastki
		///
		static bool connectToClientServer(std::string address, CORBA::ORB_out orb, IClientServer_out client)
		{
			char* orb_options[] = { const_cast<char *>(address.c_str()) , const_cast<char *>(CLNTPORT.c_str()) };
			int optc = sizeof(orb_options)/sizeof(char *);

			orb = CORBA::ORB_init(optc, orb_options);

			CORBA::String_var strIOR = CORBA::string_dup("corbaloc:iiop:");
			strIOR += address.c_str();
			strIOR += ":";
			strIOR += SRVPORT.c_str();
			strIOR += "/serverclient";

			CORBA::Object_var oClient = orb->string_to_object(strIOR);
			if (CORBA::is_nil(oClient))
			{
				return false;
			}

			client = IClientServer::_narrow(oClient);
		    
			if (CORBA::is_nil(client))
			{
				return false;
			}

			return true;
		}

		///
		/// @param [in]		address	adres klienta do ktorego ma sie polaczyc serwer
		/// @param [out]	orb		wsk na obiekt brokera - trzyma polaczenie
		/// @param [out]	client	wsk na obiekt namiastki
		/// @return			0 - powodznie, 1 - niepowodzenie
		///
		/// Laczy sie do klienta o zadanym adresie nasluchujacym na porcie LPORT; efektem polaczenia jest 
		/// zwrocenie wskaznikow do brokera polaczenia i obiektu namastki
		///
		static bool connectToServerClient(std::string address, CORBA::ORB_out orb, IServerClient_out server)
		{
			char* orb_options[] = { const_cast<char *>(address.c_str()) , const_cast<char *>(SRVPORT.c_str()) };
			int optc = sizeof(orb_options)/sizeof(char *);

			orb = CORBA::ORB_init(optc, orb_options);

			CORBA::String_var strIOR = CORBA::string_dup("corbaloc:iiop:");
			strIOR += address.c_str();
			strIOR += ":";
			strIOR += CLNTPORT.c_str();
			strIOR += "/clientserver";

			CORBA::Object_var oServer = orb->string_to_object(strIOR);
			if (CORBA::is_nil(oServer))
			{
				return false;
			}

			server = IServerClient::_narrow(oServer);
		    
			if (CORBA::is_nil(server))
			{
				return false;
			}

			return true;
		}

		///
		/// @param [in]		address	adres klienta do ktorego chce sie polaczyc klient
		/// @param [out]	orb		wsk na obiekt brokera - trzyma polaczenie
		/// @param [out]	client	wsk na obiekt namiastki
		/// @return			0 - powodznie, 1 - niepowodzenie
		///
		/// Laczy sie do klienta o zadanym adresie nasluchujacym na porcie LPORT; efektem polaczenia jest 
		/// zwrocenie wskaznikow do brokera polaczenia i obiektu namastki
		///
		static bool connectToClientClient(std::string address, CORBA::ORB_out orb, IClientClient_out client)
		{
			char* orb_options[] = { const_cast<char *>(address.c_str()) , const_cast<char *>(CLNTPORT.c_str()) };
			int optc = sizeof(orb_options)/sizeof(char *);

			orb = CORBA::ORB_init(optc, orb_options);

			CORBA::String_var strIOR = CORBA::string_dup("corbaloc:iiop:");
			strIOR += address.c_str();
			strIOR += ":";
			strIOR += CLNTPORT.c_str();
			strIOR += "/clientclient";

			CORBA::Object_var oClient = orb->string_to_object(strIOR);
			if (CORBA::is_nil(oClient))
			{
				return false;
			}

			client = IClientClient::_narrow(oClient);
		    
			if (CORBA::is_nil(client))
			{
				return false;
			}

			return true;
		}
};

#endif