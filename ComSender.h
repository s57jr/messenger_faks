/*
 * ComSender.h
 *
 *  Created on: Apr 12, 2017
 *      Author: ee
 */

#ifndef LOGIC_COMSENDER_H_
#define LOGIC_COMSENDER_H_
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdexcept>
#include <iostream>
#include <thread>
#include <QWidget>
//#include "Protocol.h"


class ComSender : public QObject{

       Q_OBJECT
public:
	ComSender(std::string ip, uint port, std::string group);
    ~ComSender();
	int SendMessage(std::string message);
public slots:
	int SendPacket();
private:
	//const uint32_t CASHSIZE         =   2500;
	const uint32_t HEADERSIZE 		= 	16;   	// number of header bytes in each packet
	const uint32_t DATASIZE 		= 	1500;   	// max. number of user data bytes in each packet
	const uint32_t timer_timeout	=	1000;	//	Timeout in seconds
	//bool got_first					=	false;

	std::string ip;
	std::string group;
	uint port;
   // std::vector<std::string> message;
    std::string message;
};

#endif /* LOGIC_COMSENDER_H_ */
