#ifndef RECEIVER_H
#define RECEIVER_H

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdexcept>
#include <iostream>
#include <thread>
#include <QObject>
#include <QWidget>
#include "BlockingQueue.h"
/*

class Receiver : public QObject
{
    Q_OBJECT
public:
    Receiver(std::string ip, uint port, std::string group, BlockingQueue<std::string> &q)
    {
            this->ip = ip;
            this->port = port;
            this->group = group;
            this->message = "";
            this->q=q;
    }
    ~Receiver();
    int get_receive_socket();

signals:

public slots:
    int receivePacket();

private:
    std::string ip;
    std::string group;
    uint port;
    std::string message;
    BlockingQueue<std::string> q;
};
*/
#endif // RECEIVER_H

