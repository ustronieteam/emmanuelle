#include "FilePackage.h"
//Begin section for file FilePackage.cpp
//TODO: Add definitions that you want preserved
//End section for file FilePackage.cpp

int FilePackage::PACKAGE_SIZE = 0;

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
FilePackage::FilePackage() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
FilePackage::FilePackage(FilePackage & arg) 
{
    //TODO Auto-generated method stub
    this->packageData = arg.packageData;
    this->packageNumber = arg.packageNumber;
    this->packageAmount = arg.packageAmount;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
FilePackage & FilePackage::operator =(const FilePackage & arg) 
{
    //TODO Auto-generated method stub
    if (this != &arg)
    {
        this->packageData = arg.packageData;
        this->packageNumber = arg.packageNumber;
        this->packageAmount = arg.packageAmount;
    }

	return *this;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
FilePackage::~FilePackage() 
{
    //TODO Auto-generated method stub
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int & FilePackage::get_PACKAGE_SIZE() 
{
    //TODO Auto-generated method stub
    return PACKAGE_SIZE;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void FilePackage::set_PACKAGE_SIZE(int & PACKAGE_SIZE) 
{
    //TODO Auto-generated method stub
    PACKAGE_SIZE = PACKAGE_SIZE;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int FilePackage::get_packageData() // TODO: poprawic typ zwracany
{
    //TODO Auto-generated method stub
    return packageData;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void FilePackage::set_packageData(int packageData) // TODO: poprawic typ packageData
{
    //TODO Auto-generated method stub
    this->packageData = packageData;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int & FilePackage::get_packageNumber() 
{
    //TODO Auto-generated method stub
    return packageNumber;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void FilePackage::set_packageNumber(int & packageNumber) 
{
    //TODO Auto-generated method stub
    this->packageNumber = packageNumber;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
int & FilePackage::get_packageAmount() 
{
    //TODO Auto-generated method stub
    return packageAmount;
}

//@generated "UML to C++ (com.ibm.xtools.transform.uml2.cpp.CPPTransformation)"
void FilePackage::set_packageAmount(int & packageAmount) 
{
    //TODO Auto-generated method stub
    this->packageAmount = packageAmount;
}
