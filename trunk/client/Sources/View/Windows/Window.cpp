#include "Window.h"

///
/// Konstruktor.
/// @param[in] controller Kontroller.
///
Window::Window(Controller * controller) : _controller(controller)
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