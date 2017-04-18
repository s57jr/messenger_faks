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

#ifndef VECTOR_ROUTING_H
#define VECTOR_ROUTING_H


class ComSender;
class Rec;

class Vector_routing: public QWidget
{
public:
    Vector_routing();

    void tick(std::vector<std::vector<uint32_t>> packet, std::vector<std::vector<uint32_t>> &pkt_out);
    int search_for(std::vector<uint32_t> vect, uint32_t value);
    int search_in_row(std::vector<std::vector<uint32_t>> vect,int row, uint32_t value);
    int32_t get_destination_address(int32_t destination);
    void receive_string_table(std::string  string_to_conv);
    void create_sendable_table(std::vector<std::vector<int32_t>> &packet_to_conv, std::string &out_string);

    std::vector<std::vector<uint32_t>> my_table;

    std::vector<std::string> out_string;
    std::vector<std::string> in_string;


    QTimer *my_time;
    QThread *my_thread;
    QThread *recv;
    std::thread t;


    std::vector<std::string>  decompose_package(std::string packet_in);

private slots:

    void rcv_msg();


private:
    std::string received_package;
    bool is_it_in(std::string sequence);
    char my_address;
    bool ACK;
    std::vector<std::string> seq_blacklist = std::vector<std::string>(10);
    int bl_p;
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

#endif // VECTOR_ROUTING_H
