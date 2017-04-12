/*
 * FileSystemCommunication.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: raoul
 */

#include "FileSystemCommunication.h"

FileSystemCommunication::FileSystemCommunication() {
	// TODO Auto-generated constructor stub

}

FileSystemCommunication::~FileSystemCommunication() {
	// TODO Auto-generated destructor stub
}

void FileSystemCommunication::save(std::string filename,std::string file_extension, std::string data){

	std::string new_file_name= filename;
	new_file_name+= ".";
	new_file_name+=file_extension;

	std::ofstream myfile;
	myfile.open (new_file_name);
	myfile << data;
	myfile.close();

	return;

}
