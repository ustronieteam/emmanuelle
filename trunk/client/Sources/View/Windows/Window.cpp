#include "Window.h"

///
/// Konstruktor.
/// @param[in] controller Kontroller.
///
Window::Window(Controller * controller, std::string name) : _controller(controller), _name(name)
{

}

///
/// Ustawienie kontrolera.
/// @param[in] controller Kontroller.
///
void Window::SetController(Controller * controller)
{
	this->_controller = controller;
}

///
/// Pobranie kontroler.
/// @return Kontroler.
///
Controller * Window::GetController()
{
	return this->_controller;
}

///
/// Ustawienie wiadomsoci.
/// @param[in] msg Wiadomosc
///
void Window::SetMsg(const std::string & msg)
{
	boost::mutex::scoped_lock sl(_mxMsg);

	if ( this->_msg.size() != 0 )
	{
		this->_msg.append("\n");
		this->_msg.append(SIDE);
		this->_msg.append(msg);
	}
	else
		this->_msg = msg;
}

///
/// Pobranie wiadomosci.
/// @return Wiadomosc
///
const std::string & Window::GetMsg()
{
	return this->_msg;
}

///
/// Czyszczenie wiadomosci.
///
void Window::ClearMsg()
{
	this->_msg.clear();
}

///
/// Pobiera nazwe okna.
/// @return Nazwa okna.
///
std::string & Window::GetName()
{
	return this->_name;
}

///
/// Ustawia nazwe okna.
/// @param[in] name Nazwa okna.
///
void Window::SetName(const std::string & name)
{
	this->_name = name;
}