#include <QApplication>
#include "messenger_window.h"
#include <thread>
#include <cstring>
#include <unistd.h>
#include <iostream>




using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Messenger_window w;
    w.resize (400, 500); // initial size
    w.setSizePolicy (QSizePolicy::Ignored, QSizePolicy::Ignored);
    w.setMinimumSize(400,450);
    w.show();

   return a.exec();
}

