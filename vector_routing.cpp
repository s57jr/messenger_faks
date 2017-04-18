#include "vector_routing.h"



#define PORT 14000 //The port you want to use
const std::string IP="192.168.5.2"; //The IP address of this computer
#define GROUP "228.0.0.0" //The multicast group you want to use


Vector_routing::Vector_routing():
    step(0),
    sender(0),
    sequenceNr(10),
    my_address(IP[IP.size()-1]),
    bl_p(0),
    ACK(false),
    message_to_disp(""),
    my_message_to_disp(""),
    received_package("")
{

    senderClass = new ComSender(IP,PORT,GROUP) ;
    myrec = new Rec(IP,PORT,GROUP);



    std::cout << "Pqwetrqwertqewrtqwertzq   wt!" << std::endl;

    recv = new QThread;
    myrec->moveToThread(recv);
    connect(recv,SIGNAL(started()),myrec,SLOT(receivePacket()));
    recv->start();

    my_thread = new QThread;
    senderClass->moveToThread(my_thread);
    connect(my_thread,SIGNAL(started()),senderClass,SLOT(SendPacket()));
    my_thread->start();

    my_time = new QTimer(this);
    connect(my_time,SIGNAL(timeout()),this,SLOT(rcv_msg()));
    my_time->start(400);

}



/*  PACKET STRUCTURE
* type      | add1  | add2
* dest      | hop1  | hop2
* src_add
*  add_a
*  add_a
*/

void Vector_routing::rcv_msg(){

    std::string to_d;

    if(myrec->message.size()){
        myrec->mut.lock();
                to_d = myrec->message;
                myrec->message = "";
        myrec->mut.unlock();

        std::string id;// = received_package[1]+received_package[2]+received_package[3];

        id.assign(received_package[1],1);
        id.assign(received_package[2],1);
        id.assign(received_package[3],1);

        char destination = received_package[0];

        if(received_package[4]=='t'){
            ACK = true;
        }else{
            ACK = false;
        }

        if(!is_it_in(id)){

            if(destination == my_address){

                if(!ACK){
                    received_package[4] = 't';
                    received_package[0] = received_package[1];
                    received_package[1] = destination;
                    senderClass->SendMessage(received_package);
                    m.lock();
                        message_to_disp =  to_d;
                    m.unlock();
                    //write to display
                }else{
                    //write acked message to display
                    m.lock();
                        my_message_to_disp = to_d;
                    m.unlock();
                }
            }else{
                senderClass->SendMessage(received_package);
            }
            add_to_array(id);
        }
    }
}


void Vector_routing::send_text(std::string text, char dest){
    std::string package_to_send = "";
    package_to_send+=dest;
    package_to_send+=my_address;
    package_to_send+=std::to_string(sequenceNr);
    package_to_send+="f";
    package_to_send+=text;
    if(sequenceNr==99)sequenceNr=9;
    sequenceNr+=1;
}

bool Vector_routing::is_it_in(std::string sequence){
    for(int i =0;i< seq_blacklist.size(); i++){
        if(sequence == seq_blacklist[i]){
            //drop the package
            return true;
        }
    }
}

void  Vector_routing::add_to_array(std::string id){
    if(bl_p == 9 )bl_p=0;
    seq_blacklist[bl_p]=id;
    bl_p++;
}


int32_t Vector_routing::get_destination_address(int32_t destination){
    int index = search_in_row(my_table, 0, destination);
    return my_table[index][2];
}


void Vector_routing::tick(std::vector<std::vector<uint32_t>> packet, std::vector<std::vector<uint32_t> > &pkt_out){


    for (int32_t i = 0; i < packet.size(); i++) {

        int32_t neighbour = my_table[0][2];//packet.getSourceAddress();                   // from whom is the packet?

        bool in = false;
        NInfo curr;
        curr.address = neighbour;
        time_t now;
        time(&now);
        curr.last = now;

        for(int o=0; o< neighbours.size();o++){

            if((difftime(neighbours[o].last, now))>5){
                //neighbour disconnected!!

            }

            if(neighbours[o].address == neighbour){
               in = true;
               neighbours[o] = curr;
            }
        }
        if(!(in)){                  //add neighbour to the list of neighbours
            neighbours.push_back(curr);
        }

        std::cout << "received packet from " << neighbour << " with "
                  << packet[1].size() << " rows and "
                  << packet.size() << " columns of data\n";



        if(!packet[0][0]){                                              //is this broadcast?
            if (search_in_row(my_table, 0 , neighbour) == -1){              //already in table?
                std::vector<uint32_t> tmp ={neighbour, neighbour};
                my_table.push_back(tmp);
            }
        }else if(packet[0][0]){                                         //table packet
            for(int g =1; g < packet.size();g++){
                if(search_in_row(my_table, 0 , packet[g][0]) != -1){
                    //the entry is already here
                }else{                                                  //path through neighbour found, make sure not to advertise it back
                    if(packet[g][0] != neighbour){
                        std::vector<uint32_t> blist_col={neighbour, packet[g][0]};
                        blacklist.push_back(blist_col);
                    }
                    std::vector<uint32_t> tmp ={packet[g][0],neighbour};
                    my_table.push_back(tmp);
                }
            }
        }


        if(step == 0){

            std::vector<uint32_t> vct;                                                      // first broadcast my address to neighbours
            vct.insert(vct.begin(),0);
            vct.shrink_to_fit();        //size should be one here

            pkt_out.insert(pkt_out.begin(), vct);
            pkt_out.shrink_to_fit();     //size should be 1 here!!

            //packet is ready here!!

            step+=1;

        }else{                              //create packet out, note that it is different for some neighbours

            for(int i=0; i < blacklist.size(); i++){
                std::vector<std::vector<uint32_t>> pkt_to_send;
                std::vector<uint32_t> first_c = {1, blacklist[i][0]};
                pkt_to_send.push_back(first_c);
                for(int j =1 ; j < my_table.size(); j++){
                       bool blacklisted = false;
                       for(int a =1; a < blacklist[i].size(); a++){
                            if(!(my_table[j][0] == blacklist[i][a])){
                                blacklisted = true;
                            }
                       }
                       if(!(blacklisted)){
                           pkt_to_send.push_back(my_table[j]);

                           //packet is ready here!
                       }
                }
            }
            for(int n =0; n<neighbours.size(); n++){
                bool already_sent = false;
                for(int z =0; z< blacklist.size();z++){
                    if(neighbours[n].address == blacklist[z][0]){
                        already_sent = true;
                    }
                    if(!(already_sent)){
                        std::vector<std::vector<uint32_t>> pkt_to_send;
                        std::vector<uint32_t> first_c = {1, neighbours[n].address};
                        pkt_to_send.push_back(first_c);
                        for(int j =1 ; j < my_table.size(); j++){
                            pkt_to_send.push_back(my_table[j]);
                        }

                        //packet is ready here!
                    }
                }
            }
        }
    }
}

int Vector_routing::search_for(std::vector<uint32_t> vect, uint32_t value){ 	//return index or -1 if not found
    for(int i = 0 ; i < vect.size(); i++){
        if(vect.at(i) == value){
            return i;
        }
    }
    return -1;
}

int Vector_routing::search_in_row(std::vector<std::vector<uint32_t>> vect,int row, uint32_t value){ //return index or -1 if not found
    for(int i = 0 ; i < vect.size(); i++){
        if(vect[i][row] == value){
            return i;
        }
    }
    return -1;
}

void Vector_routing::create_sendable_table(std::vector<std::vector<int32_t>> &packet_to_conv, std::string &out_string){

    for(int u =0; u< packet_to_conv.size();u++){
        for(int i=0; i < packet_to_conv[u].size();){
            if(i){
                out_string+="|";
            }
            out_string+=(std::to_string(packet_to_conv[u][i]));
        }
        out_string+="&";
        std::cout << out_string << std::endl;
    }
}

void Vector_routing::receive_string_table(std::string  string_to_conv){
    std::string::size_type sz;
    for(int u =0; u< 3 ;u++){
          std::size_t found = string_to_conv.find_first_of("|");
          int a =0;
          while (found!=std::string::npos)
          {
            std::string entry;
         //   string_to_conv.copy(entry,found-1);
            for(int z =0; z < static_cast<int>(found-1);z++){
                entry[z]=string_to_conv[z];
            }

            in_packet[u][a] = std::stoi (entry,&sz);
            a++;
            string_to_conv.erase(0,found);
            found=string_to_conv.find_first_of("|");
          }
          found=string_to_conv.find_first_of("&");
          std::string entry;
          for(int z =0; z < static_cast<int>(found-1);z++){
              entry[z]=string_to_conv[z];
          }
          in_packet[u][a] = std::stoi (entry,&sz);

          string_to_conv.erase(0,found);

    }
}


