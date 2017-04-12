/*
 * special_data_types.h
 *
 *  Created on: Apr 11, 2017
 *      Author: raoul
 */

#ifndef PROTOCOL_SPECIAL_DATA_TYPES_H_
#define PROTOCOL_SPECIAL_DATA_TYPES_H_

#include <chrono>
#include <vector>
#include <string>

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::high_resolution_clock::time_point time_type;
typedef std::vector<int32_t> missed_list_type;
typedef std::vector<int32_t> part_image_type;
typedef std::vector<part_image_type> image_type;

struct packet_type {
    int total; 							//	Total of packages that we will get
    int current; 						//	Current package number
    int box; 							//	Last number in this package
    unsigned long long int sended_hash; //	The sended hash of the data as an integer
    unsigned long long int our_hash; 	//	Our hash of the data as a integer
    part_image_type sended_data;		//	The sended data
    std::string sended_data_string; 	//	The sended data (string)
    std::vector<int32_t> total_package;	//	The total package as we received them
};

#endif /* PROTOCOL_SPECIAL_DATA_TYPES_H_ */
