#ifndef ROUTER_H
#define ROUTER_H
#include <iostream>
#include <vector>
#include <time.h>
#include "ComSender.h"
#include "rec.h"
#include <mutex>
#include "datatable.h"
#include <thread>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include "receiver.h"

#include <QtWidgets>
#include <QWidget>
#include <QObject>



#define PORT 14000 //The port you want to use
const std::string IP="192.168.5.2"; //The IP address of this computer
#define GROUP "228.0.0.0" //The multicast group you want to use



class router : public QObject
{
    Q_OBJECT
public:
    explicit router(QObject *parent = 0);

    void tick(std::vector<std::vector<uint32_t>> packet, std::vector<std::vector<uint32_t>> &pkt_out);
    int search_for(std::vector<uint32_t> vect, uint32_t value);
    int search_in_row(std::vector<std::vector<uint32_t>> vect,int row, uint32_t value);
    int32_t get_destination_address(int32_t destination);
    void receive_string_table(std::string  string_to_conv);
    void create_sendable_table(std::vector<std::vector<int32_t>> &packet_to_conv, std::string &out_string);
    void send_text(std::string text, string dest);
    std::vector<std::vector<uint32_t>> my_table;

    void  add_to_array(std::string id);
    void  add_ack_to_array(std::string id);
    bool is_it_in_ack(std::string sequence);


    std::vector<std::string> out_string;
    std::vector<std::string> in_string;


    QTimer *my_timer;
    QThread *my_thread;
    QThread *recv;
    std::thread t;

    std::mutex m;
    std::string message_to_disp;
    std::string my_message_to_disp;


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
