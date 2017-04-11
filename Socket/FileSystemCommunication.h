/*
 * FileSystemCommunication.h
 *
 *  Created on: Apr 11, 2017
 *      Author: raoul
 */

#ifndef PROTOCOL_FILESYSTEMCOMMUNICATION_H_
#define PROTOCOL_FILESYSTEMCOMMUNICATION_H_

#include "special_data_types.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


//#include "../client/Utils.h"

class FileSystemCommunication {
public:
	FileSystemCommunication();
	virtual ~FileSystemCommunication();

	static void save(std::string filename,std::string file_extension, std::string data);


};


#endif /* PROTOCOL_FILESYSTEMCOMMUNICATION_H_ */
