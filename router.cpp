#include "router.h"

router::router(QObject *parent) : QObject(parent),
  step(0),
  sender(0),
  sequenceNr(10),
  my_address(IP[IP.size()-1]),
  bl_p(0),
  ACK(false),
  bl_p_ack(0)

{

  senderClass = new ComSender(IP,PORT,GROUP) ;
  myrec = new Rec(IP,PORT,GROUP);

  message_to_disp="";
  my_message_to_disp="";
  received_package="";

  std::cout << "Pqwetrqwertqewrtqwertzq   wt!" << std::endl;

  recv = new QThread;
  myrec->moveToThread(recv);
  connect(recv,SIGNAL(started()),myrec,SLOT(receivePacket()));
  recv->start();

  my_thread = new QThread;
  senderClass->moveToThread(my_thread);
  connect(my_thread,SIGNAL(started()),senderClass,SLOT(SendPacket()));
  my_thread->start();

  my_timer = new QTimer(this);
  connect(my_timer,SIGNAL(timeout()),this,SLOT(rcve_msg()));
  my_timer->start(5);

}



/*  PACKET STRUCTURE
* type      | add1  | add2
* dest      | hop1  | hop2
* src_add
*  add_a
*  add_a
*/

void router::rcve_msg(){

  std::string to_d;

  if(myrec->message.size()){
      myrec->mut.lock();
              to_d = myrec->message;
              myrec->message = "";
      myrec->mut.unlock();

      std::cout << "printing rec." << to_d <<std::endl;

      std::string id;// = received_package[1]+received_package[2]+received_package[3];

      id.assign(to_d[1],1);
      id.assign(to_d[2],1);
      id.assign(to_d[3],1);

      char destination = to_d[0];
      char source = to_d[1];

      std::cout << destination << std::endl;

      if(to_d[4]=='t'){
          ACK = true;
      }else{
          ACK = false;
      }

      if((!is_it_in(id)&&!ACK)||(!is_it_in_ack(id)&&ACK)){

          if(destination == my_address){

              if(!ACK){
                  std::cout << "this is not ack" << std::endl;

                  to_d[4] = 't';
                  to_d[0] = source;
                  to_d[1] = destination;
                  senderClass->SendMessage(to_d);
                  m.lock();
                      message_to_disp =  to_d.substr(5,to_d.size()-1);
                  m.unlock();
                  std::cout << "receiving this: " << to_d << std::endl;
                  add_to_array(id);

                  //write to display
              }else{
                  std::cout << "this is ack" << std::endl;
                  add_ack_to_array(id);
                  //write acked message to display
                  m.lock();
                      my_message_to_disp = to_d.substr(5,to_d.size()-1);
                  m.unlock();
                  std::cout << "acking this: " << to_d << std::endl;

              }
          }else if(source != my_address){
              std::cout << "this is not for me" << std::endl;

              if(ACK){
                  add_ack_to_array(id);
              }else{
                  add_to_array(id);
              }

              senderClass->SendMessage(to_d);
          }
      }

  }
}


void router::send_text(std::string text, std::string dest){
    std::string str(1, my_address);
  std::string package_to_send = "";
  package_to_send+=dest;
  package_to_send+=str;//std::to_string(my_address);
  package_to_send+=std::to_string(sequenceNr);
  package_to_send+="f";
  package_to_send+=text;
  std::cout << "sending this: " << package_to_send<< std::endl;
  senderClass->SendMessage(package_to_send);

}

void router::increment_seq_nr(){
    if(sequenceNr>=99)sequenceNr=9;
    sequenceNr+=1;
}

bool router::is_it_in(std::string sequence){
  for(int i =0;i< seq_blacklist.size(); i++){
      if(sequence == seq_blacklist[i]){
          //drop the package
          return true;
      }
  }
}

bool router::is_it_in_ack(std::string sequence){
  for(int i =0;i< seq_ack_blacklist.size(); i++){
      if(sequence == seq_ack_blacklist[i]){
          //drop the package
          return true;
      }
  }
}

void  router::add_ack_to_array(std::string id){
  if(bl_p_ack == 99 )bl_p_ack=10;
  seq_ack_blacklist[bl_p_ack]=id;
  bl_p_ack++;
}

void  router::add_to_array(std::string id){
  if(bl_p == 99 )bl_p=10;
  seq_blacklist[bl_p]=id;
  bl_p++;
}


int32_t router::get_destination_address(int32_t destination){
  int index = search_in_row(my_table, 0, destination);
  return my_table[index][2];
}



int router::search_in_row(std::vector<std::vector<uint32_t>> vect,int row, uint32_t value){ //return index or -1 if not found
  for(int i = 0 ; i < vect.size(); i++){
      if(vect[i][row] == value){
          return i;
      }
  }
  return -1;
}
