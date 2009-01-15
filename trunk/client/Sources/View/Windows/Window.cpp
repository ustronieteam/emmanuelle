#include "Window.h"

Window::Window(Controller * controller, std::string name) : _controller(controller), _name(name)
{

}

void Window::SetController(Controller * controller)
{
	this->_controller = controller;
}

Controller * Window::GetController()
{
	return this->_controller;
}

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

const std::string & Window::GetMsg()
{
	return this->_msg;
}

void Window::ClearMsg()
{
	this->_msg.clear();
}

std::string & Window::GetName()
{
	return this->_name;
}

void Window::SetName(const std::string & name)
{
	this->_name = name;
}