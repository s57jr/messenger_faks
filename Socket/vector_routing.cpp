#include "vector_routing.h"

Vector_routing::Vector_routing()
{

}


int step=0;

void DummyRoutingProtocol::tick(std::vector<client::Packet> packets) {
    if(step == 0) std::cout << "step s 0" << std::endl;
    std::cout << "step:" << step << std::endl;
    // Get the adstd::cout << "step s 0" << std::endl;dress of this node
    int32_t myAddress = this->linkLayer->getOwnAddress();

    // print something useful for debugging
    std::cout << "tick; received " << packets.size() << " packets\n";
    int exception =0;

    int32_t i;
    // first process the incoming packets; loop over them:
    for (i = 0; i < packets.size(); i++) {
        int32_t neighbour = packets[i].getSourceAddress();            // from whom is the packet?
        int32_t linkcost = this->linkLayer->getLinkCost(neighbour);   // what's the link cost from/to this neighbour?
        client::DataTable *dt = packets[i].getDataTable();        // other data contained in the packet
      //  std::cout << "received packet from " << neighbour << " with "
        //          << dt->getNRows() << " rows and "
          //        << dt->getNColumns() << " columns of data\n";


        protocol::DummyRoute r;


        if(linkcost >= 0 || (dt->get(0,0)==3)){			//is there a failed link??
        if(dt->getNRows() > 0 && (packets.size() != 0)){
        if(!dt->get(0,0)){
            if (!(myForwardingTable.count( neighbour ))) {
                protocol::DummyRoute r;
                r.nextHop = neighbour;
                r.cost	  = linkcost;
                myForwardingTable[neighbour]=r; 		//fill in neighbours

            }else{
                if(myForwardingTable[neighbour].cost > linkcost){
                    r.nextHop = neighbour;
                    r.cost = linkcost;
                    myForwardingTable[neighbour] = r;
                }
            }
       }else if(dt->get(0,0)){
           //start building table
           for(int g =1; g < dt->getNColumns();g++){
               if(myForwardingTable.count( dt->get(0,g) ) /*&& (dt->get(0,g) != myAddress)*/){  //if it is in check for lower cost
                      if(myForwardingTable[dt->get(0,g)].cost > (dt->get(2,g)+linkcost)){
                          r.nextHop=neighbour;
                          r.cost =(dt->get(2,g)+linkcost);
                          myForwardingTable[dt->get(0,g)] = r;
                      }
               }else{
                   //add entry
                  r.nextHop=neighbour;
                  r.cost =(dt->get(2,g)+linkcost);
                  myForwardingTable[dt->get(0,g)] = r;
               }
           }
       }
       }
       }else{  //reinitialize the link sice one of the links failed

       std::cout << "dt:" << dt->get(0,0) << std::endl;

       step = 0;

       client::DataTable dta = client::DataTable(1);
       std::vector<int32_t> a;
       a.push_back(0);
       exception = 1;
       dta.addRow(a);

       dta.set(0,0,3);

       std::cout << "dta:" << dta.get(0,0) << std::endl;

       for(int b =0;b < myForwardingTable.size(); b++){

       }
       for (std::map<int32_t, DummyRoute>::iterator it = myForwardingTable.begin();it != myForwardingTable.end(); it++) {
           int32_t destination = it->first;
           if(destination != neighbour){
               client::Packet pkt = client::Packet(myAddress, destination, &dta);
               this->linkLayer->transmit(pkt);
           }

       }

       myForwardingTable.clear();

       break;
       }
    }





    client::DataTable dta = client::DataTable(myForwardingTable.size()+1);   // the 3 is the number of columns, you can change this

    if(step == 0 && (exception != 1)){
        std::vector<int32_t> a,b,c;
        a.reserve(myForwardingTable.size()+1);
        b.reserve(myForwardingTable.size()+1);
        c.reserve(myForwardingTable.size()+1);

        for (int g = 0; g< (myForwardingTable.size()+1); g++){
            b.push_back(0);
            c.push_back(0);

            a.push_back(0);

        }

        dta.addRow(a);
        dta.addRow(b);
        dta.addRow(c);

        std::cout << "step s 0" << std::endl;

        std::cout << myForwardingTable.size()+1 << std::endl;

        dta.set(0,0,0);	// first broadcast my address to neighbours
        step+=1;
    }else{
        std::vector<int> a,b,c;
        a.reserve(myForwardingTable.size()+1);
        b.reserve(myForwardingTable.size()+1);
        c.reserve(myForwardingTable.size()+1);

        for (int g = 0; g< (myForwardingTable.size()+1); g++){
            b.push_back(0);
            c.push_back(0);

            a.push_back(0);

        }

        dta.addRow(a);
        dta.addRow(b);
        dta.addRow(c);


        dta.set(0,0,1);
        int cnt = 1;
        for (std::map<int32_t, DummyRoute>::iterator it = myForwardingTable.begin();it != myForwardingTable.end(); it++) {
            int32_t destination = it->first;
            int32_t nextHop = it->second.nextHop;
            int32_t cost	= it->second.cost;

            dta.set(0,cnt,destination);
            dta.set(1,cnt,nextHop);
            dta.set(2,cnt,cost);

            cnt+=1;
        }
    }

    /*
     * add1  | add2
     * hop1  | hop2
     * cost1 | cost2
     *
     *
     *
     */


    if(exception != 1){
    client::Packet pkt = client::Packet(myAddress, 0, &dta);
    this->linkLayer->transmit(pkt);
    }

}

std::map<int32_t, int32_t> DummyRoutingProtocol::getForwardingTable() {
    // This code transforms your forwarding table which may contain extra information
    // to a simple one with only a next hop (value) for each destination (key).
    // The result of this method is send to the server to validate and score your protocol.

    //  <Destination, NextHop>
    std::map<int32_t, int32_t> ft;

    for (std::map<int32_t, DummyRoute>::iterator it = myForwardingTable.begin();
         it != myForwardingTable.end(); it++) {
        int32_t destination = it->first;
        int32_t nextHop = it->second.nextHop;

        ft[destination] = nextHop;
    }

    return ft;
    }

