#include "FilePackage.h"

///
///@author Marian Szczykulski
///@brief Konstruktor domyslny
FilePackage::FilePackage() 
{
	_data = NULL;
	_size = 0;
	_name = "";
}


FilePackage::~FilePackage() 
{

}
void FilePackage::SetData(char * data)
{
}
char * FilePackage::GetData()
{
	return NULL;
}