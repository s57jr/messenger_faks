#include <QApplication>
#include "messenger_window.h"
#include <thread>
#include <cstring>
#include <unistd.h>
#include <iostream>

#include "receiver.h"
#include "BlockingQueue.h"




using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Messenger_window w;
    w.resize (400, 400); // initial size
    w.setSizePolicy (QSizePolicy::Ignored, QSizePolicy::Ignored);
    w.setMinimumSize(400,400);
    w.show();

   return a.exec();
}

//void check_queue(){
//    std::string message = q.pop();
//    std::cout << "Packet of size " << message.size() << " received, message: " << message << std::endl;
//}
