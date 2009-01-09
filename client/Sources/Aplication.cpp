#include "Aplication.h"
//Begin section for file Aplication.cpp
//TODO: Add definitions that you want preserved
//End section for file Aplication.cpp


//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Aplication::Aplication() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Aplication::Aplication(Aplication & arg) 
{
    //TODO Auto-generated method stub
    this->controller = arg.controller;
    this->view = arg.view;
    this->iModel = arg.iModel;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Aplication & Aplication::operator =(const Aplication & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->controller = arg.controller;
        this->view = arg.view;
        this->iModel = arg.iModel;
    }

	return *this;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Aplication::~Aplication() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
Controller * & Aplication::get_controller() 
{
    //TODO Auto-generated method stub
    return controller;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void Aplication::set_controller(Controller * & controller) 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
View * & Aplication::get_view() 
{
    //TODO Auto-generated method stub
    return view;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void Aplication::set_view(View * & view) 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
IModel * & Aplication::get_iModel() 
{
    //TODO Auto-generated method stub
    return iModel;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void Aplication::set_iModel(IModel * & iModel) 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int Aplication::Run() 
{
    //TODO Auto-generated method stub
    return 0;
}
