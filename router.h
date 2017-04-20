#ifndef ROUTER_H
#define ROUTER_H
#include <iostream>
#include <vector>
#include <time.h>
#include "ComSender.h"
#include "rec.h"
#include <mutex>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include "encryption.h"
#include "encryption.h"

#include <QtWidgets>
#include <QWidget>
#include <QObject>



#define PORT 14000 //The port you want to use
const std::string IP="192.168.5.2"; //The IP address of this computer
#define GROUP "228.0.0.0" //The multicast group you want to use


class Rec;

class router : public QObject
{
    Q_OBJECT
public:
    explicit router(QObject *parent = 0);
    int32_t get_destination_address(int32_t destination);
    int search_in_row(std::vector<std::vector<uint32_t>> vect,int row, uint32_t value);

    void send_text(std::string text, string dest);
    std::vector<std::vector<uint32_t>> my_table;

    void  add_to_array(std::string id);
    void  add_ack_to_array(std::string id);
    bool is_it_in_ack(std::string sequence);
    void increment_seq_nr();

    std::vector<std::string> out_string;
    std::vector<std::string> in_string;
    char source;

    QTimer *my_timer;
    QThread *my_thread;
    QThread *recv;
    std::thread t;

    std::mutex m;
    std::string message_to_disp;
    std::string my_message_to_disp;
    Encryption      *encr;


    std::vector<std::string>  decompose_package(std::string packet_in);

public slots:

    void rcve_msg();


private:
    std::string received_package;
    bool is_it_in(std::string sequence);
    char my_address;
    bool ACK;
    std::vector<std::string> seq_blacklist = std::vector<std::string>(100);
    std::vector<std::string> seq_ack_blacklist = std::vector<std::string>(100);

    int bl_p;
    int bl_p_ack;
    char sender;
    uint8_t sequenceNr;
    int step;
    std::vector<std::vector<int32_t>> in_packet;

    struct NInfo{
        uint32_t address;
        time_t last;
    };

    ComSender       *senderClass;
    Rec             *myrec;

    std::vector<std::vector<uint32_t>> blacklist;
    std::vector<NInfo> neighbours;
};

#endif // ROUTER_H
