/*
 * ComReceiver.h
 *
 *  Created on: Apr 11, 2017
 *      Author: raoul
 */

#ifndef SOCKET_COMRECEIVER_H_
#define SOCKET_COMRECEIVER_H_

#include "special_data_types.h"
//#include "../client/NetworkLayer.h"
//#include "../client/Utils.h"
//#include "IRDTProtocol.h"

#include <iostream>


class ComReceiver {
public:
	ComReceiver();
	virtual ~ComReceiver();

	static int 						get_from_pack(int pack1, int pack2, packet_type packet);

	static unsigned long long int 	get_hash(int from,int to,packet_type package);
	static unsigned long long int 	hash_string_to_int(std::string);

	static bool 					timer_expired(time_type t1,time_type t2,uint32_t timeout_time);

	static std::string 				make_new_hash(packet_type package);
	static std::string 				make_pack_string(int from,int to,packet_type packet);

	static part_image_type 			make_pack_vector(int from,int to,packet_type packet);

	       void 					send_ack(missed_list_type pkt);

	//Generic Functions

	static unsigned long long int hash(std::string *str);

	const uint32_t timer_timeout	=	3;		//	Timeout in seconds

};

#endif /* SOCKET_COMRECEIVER_H_ */
