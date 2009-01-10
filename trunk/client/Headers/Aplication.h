#ifndef APLICATION_H
#define APLICATION_H
//Begin section for file Aplication.h
//TODO: Add definitions that you want preserved
//End section for file Aplication.h


class Controller;
class View;
class IModel;

//G³ówna klasa aplikacji. Startuje program klienta i wi¹¿e odpowiednie warstwy ze sob¹.
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class Aplication
{

    //Begin section for Aplication
    //TODO: Add attributes that you want preserved
    //End section for Aplication

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Controller * controller;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        View * view;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        IModel * iModel;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Aplication();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~Aplication();

        //get controller
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Controller * & get_controller();

        //set controller
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        void set_controller(Controller * & controller);

        //get view
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        View * & get_view();

        //set view
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        void set_view(View * & view);

        //get iModel
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        IModel * & get_iModel();

        //set iModel
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        void set_iModel(IModel * & iModel);

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int Run();

};  //end class Aplication

#endif
