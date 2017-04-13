#ifndef REC_H
#define REC_H
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
#include "messenger_window.h"
#include "messagedisplay.h"

class MessageDisplay;

class Rec : public QObject
{
    Q_OBJECT
public:
    explicit Rec(std::string ip, uint port, std::string group);
    int get_receive_socket();

    std::string message;
    std::mutex mut;
signals:

public slots:
    int receivePacket();

private:
    std::string ip;
    std::string group;
    uint port;
};

#endif // REC_H
