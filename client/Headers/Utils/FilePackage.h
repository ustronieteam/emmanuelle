#ifndef FILEPACKAGE_H
#define FILEPACKAGE_H

#include <iostream>
#include <vector>
class FilePackage
{


    private:

        long _size; 

        char * _data;

		std::string _name;



    public:


        FilePackage();
        virtual ~FilePackage();
		
		void SetSize(long size){_size = size;}
		long GetSize(){return _size;}

		void SetData(char * data);
		char * GetData();

		void SetName(std::string str){_name = str;}
		std::string GetName(){return _name;}

};  //end class FilePackage

#endif
