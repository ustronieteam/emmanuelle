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

		View();

    public:

		static View * GetInstance()
		{
			static View * instance = new View();

			return instance;
		}

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~View();

        //get controller
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        Controller * GetController();

        //set controller
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        void SetController(Controller * controller);

};  //end class View

#endif
