#ifndef VIEW_H
#define VIEW_H
//Begin section for file View.h
//TODO: Add definitions that you want preserved
//End section for file View.h


class Controller;

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class View
{

    //Begin section for View
    //TODO: Add attributes that you want preserved
    //End section for View

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Controller * controller;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        View();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~View();

        //get controller
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Controller * & get_controller();

        //set controller
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        void set_controller(Controller * & controller);

};  //end class View

#endif
