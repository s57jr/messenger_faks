#include <iostream>
#include <vector>

#include "datatable.h"


#ifndef VECTOR_ROUTING_H
#define VECTOR_ROUTING_H


class Vector_routing
{
public:
    Vector_routing();

    void Vector_routing::tick(std::vector<std::vector<uint8_t>> packet, std::vector<std::vector<uint8_t>> &my_table);


};

#endif // VECTOR_ROUTING_H
