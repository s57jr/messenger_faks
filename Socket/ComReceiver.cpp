/*
 * ComComReceiver.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: raoul
 */

#include "ComReceiver.h"

ComReceiver::ComReceiver() {

}

ComReceiver::~ComReceiver() {
	// TODO Auto-generated destructor stub
}

//General

unsigned long long int ComReceiver::hash(std::string *str){

	std::string i = *str;
	// << i << std::endl;
	std::size_t str_hash = std::hash<std::string>{}(i);
	return str_hash;

}

//For the receiving part

void ComReceiver::send_ack(missed_list_type pkt){

	missed_list_type pkt2;

	if(pkt.size()==0){ //SUCCESS! send special message

		pkt2.push_back(1);
		pkt2.push_back(1);
		pkt2.push_back(1);
		pkt2.push_back(1);

		std::cout << "\n" << "Done sending, we got them all!" << std::endl;

	}else{

		std::cout << "Send ACK, with missing packets at location(s):";

		for(uint32_t i=0;i<pkt.size();i++){
			if(pkt[i]==0){
				pkt2.push_back((i+1));
				std::cout << std::to_string((i+1)) << " ";
			}
		}

		std::cout << std::endl;

	}

	//networkLayer->sendPacket(pkt2); // send the packet to the network layer

	return;

}

int ComReceiver::get_from_pack(int pack1, int pack2, packet_type packet){

	int new_value=0;

	new_value	=new_value | (int) packet.total_package[pack1];
	new_value	=new_value << 8;
	new_value	=new_value | packet.total_package[pack2];

	return new_value;

}

std::string ComReceiver::make_pack_string(int from,int to,packet_type packet){

	std::string new_string;

	for(int i=from;i<to;i++){
		new_string+=std::to_string(packet.total_package[i]);
	}

	return new_string;

}

unsigned long long int ComReceiver::get_hash(int from,int to,packet_type package){

	std::string new_hash;

	for(int i=from;i<=to;i++){

		if(package.total_package[i]<=9 && i!=to){
			new_hash += std::to_string(0);
		}

		new_hash += std::to_string(package.total_package[(i)]);
	}

	unsigned long long int new_hash_int	=	std::stoull(new_hash); 	//Go from string to unsigned long long integer

	return new_hash_int;

}

bool ComReceiver::timer_expired(time_type t1,time_type t2,uint32_t timeout_time){

	if((std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count())>timeout_time){
		return true;
	}else{
		return false;
	}

}

part_image_type ComReceiver::make_pack_vector(int from,int to,packet_type packet){

	part_image_type new_part((to-from));

	for(int i=from;i<to;i++){

		new_part[(i-from)]=packet.total_package[i];

	}

	return new_part;
}
