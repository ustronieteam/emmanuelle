#ifndef FILEPACKAGE_H
#define FILEPACKAGE_H
//Begin section for file FilePackage.h
//TODO: Add definitions that you want preserved
//End section for file FilePackage.h


//<p>
//    Paczka, która powinna byæ przesy³ana. Zawiera:
//</p>
//<p>
//    -dane w postaci binarnej (tablica char[PACKAGE_SIZE])
//</p>
//<p>
//    -informacje nag³ówkowe (numer paczki, iloœæ paczek w ca³ym pakiecie)
//</p>
//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
class FilePackage
{

    //Begin section for FilePackage
    //TODO: Add attributes that you want preserved
    //End section for FilePackage

    private:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        static int PACKAGE_SIZE;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int packageData; // TODO: zmienic typ zwracany

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int packageNumber;

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int packageAmount;



    public:

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        FilePackage();

        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        virtual ~FilePackage();

        //get PACKAGE_SIZE
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        static int & get_PACKAGE_SIZE();

        //set PACKAGE_SIZE
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        static void set_PACKAGE_SIZE(int & PACKAGE_SIZE);

        //get packageData
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int get_packageData(); // TODO: zmienic typ zwracany

        //set packageData
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        void set_packageData(int packageData); // TODO: zmienic typ packageData

        //get packageNumber
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int & get_packageNumber();

        //set packageNumber
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        void set_packageNumber(int & packageNumber);

        //get packageAmount
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        int & get_packageAmount();

        //set packageAmount
        //@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
        void set_packageAmount(int & packageAmount);

};  //end class FilePackage

#endif
