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
    bool search_for(std::vector<uint32_t> vect, uint32_t value);
    bool search_in_row(std::vector<std::vector<uint32_t>> vect,int row, uint32_t value);

    std::vector<std::vector<uint32_t>> my_table;

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
