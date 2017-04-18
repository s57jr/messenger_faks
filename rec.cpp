#include "rec.h"

Rec::Rec(std::string ip, uint port, std::string group)
{
    this->ip = ip;
    this->port = port;
    this->group = group;
    this->message = "";
}

int Rec::get_receive_socket() {

    int retsock;
    if ((retsock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) //Get a IPv4 (AF_INET) socket for UDP packets (SOCK_DGRAM)
        throw std::runtime_error("Failed to create socket!");


    int reuse = 0;
    if(setsockopt(retsock, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
        throw std::runtime_error("Failed to set SO_REUSEADDR!");


    struct sockaddr_in local = {0};
    memset((char *) &local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(port);
    local.sin_addr.s_addr = INADDR_ANY;
    if(bind(retsock, (struct sockaddr*)&local, sizeof(local)))
        throw std::runtime_error("Failed to bind socket!");


    struct ip_mreq group_req; //struct for multicast group requests
    group_req.imr_multiaddr.s_addr = inet_addr(group.c_str()); //the multicast address to join
    group_req.imr_interface.s_addr = inet_addr(ip.c_str()); //the address of the interface to perform the join on (our IP address)
    if(setsockopt(retsock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group_req, sizeof(group_req)) < 0)
        throw std::runtime_error("Failed to join multicast group!");

    return retsock;
}

int Rec::receivePacket()
{
    try
    {
        int rsock;

        rsock = get_receive_socket();

        // prepare a structure to put peer data into
        struct sockaddr_in peer_address;
        socklen_t peer_address_len;
        peer_address_len = sizeof(struct sockaddr_storage);

        // allocate memory to put the received data into
        char data[1500];
        int len;
        len = 0;

        while (1) {
            // Receive packet and put its contents in data, recvfrom will block until a packet for this socket has been received
            len = recvfrom(rsock, data, sizeof(data), 0, (struct sockaddr *) &peer_address, &peer_address_len);
            if(len > 0){
                mut.lock();
                //q.push(std::string(data, len));
                message = std::string(data, len); //q.pop();
                mut.unlock();
                std::cout << "Packet of size " << message.size() << " received, message: " << message << std::endl;
            }
            sleep(1);
        }
    } catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
        exit(0);
    }

    return 0;
}
