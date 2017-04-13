#include <iostream>
#include <vector>
#include <time.h>

#include "datatable.h"


#ifndef VECTOR_ROUTING_H
#define VECTOR_ROUTING_H


class Vector_routing
{
public:
    Vector_routing();

    void tick(std::vector<std::vector<uint32_t>> packet, std::vector<std::vector<uint32_t>> &pkt_out);
    int search_for(std::vector<uint32_t> vect, uint32_t value);
    int search_in_row(std::vector<std::vector<uint32_t>> vect,int row, uint32_t value);
    int32_t get_destination_address(int32_t destination);
    void receive_string_table(std::string  string_to_conv, std::vector<std::vector<int32_t>> &in_packet);
    void create_sendable_table(std::vector<std::vector<int32_t>> &packet_to_conv, std::string &out_string);

    std::vector<std::vector<uint32_t>> my_table;

     std::vector<std::string> out_string;
     std::vector<std::string> in_string;



private:
    int step;

    struct NInfo{
        uint32_t address;
          time_t last;
    };

    std::vector<std::vector<uint32_t>> blacklist;
    std::vector<NInfo> neighbours;
};

#endif // VECTOR_ROUTING_H
