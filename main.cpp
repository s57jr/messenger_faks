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
    w.resize (400, 400); // initial size
    w.setSizePolicy (QSizePolicy::Ignored, QSizePolicy::Ignored);
    w.setMinimumSize(400,400);
    w.show();

   return a.exec();
}

