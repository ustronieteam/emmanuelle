#include "View.h"
//Begin section for file View.cpp
//TODO: Add definitions that you want preserved
//End section for file View.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
View::View() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
View::View(View & arg) 
{
    //TODO Auto-generated method stub
    this->controller = arg.controller;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
View & View::operator =(const View & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->controller = arg.controller;
    }

	return *this;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
View::~View() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Controller * & View::get_controller() 
{
    //TODO Auto-generated method stub
    return controller;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void View::set_controller(Controller * & controller) 
{
    //TODO Auto-generated method stub
}
