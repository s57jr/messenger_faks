#include "messenger_window.h"
#include "icons.h"
#include <thread>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include "receiver.h"
#include "BlockingQueue.h"


#include "BlockingQueue.h"

BlockingQueue<std::string> q;



Messenger_window::Messenger_window(QWidget *parent) : QWidget(parent)
{

    QPixmap bkgnd("/home/mujo/qt-proj/MessengerPro2/main_bkgnd.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    set_display_object();
    set_type_object();

    //signals

    connect(comboBox_food,SIGNAL(currentIndexChanged(int)),this,SLOT(emoji_chosen_food()));
    connect(comboBox_fun,SIGNAL(currentIndexChanged(int)),this,SLOT(emoji_chosen_fun()));
    connect(line_to_write,SIGNAL(returnPressed()),this,SLOT(send_text()));



    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(type_object,2,1,2,4,Qt::AlignBottom);
    mainLayout->addWidget(display_object,1,1,5,4,Qt::AlignTop);
    mainLayout->setRowStretch(1,5);
    setLayout(mainLayout);

    setWindowTitle(tr("MessengerPro2"));

    router = new Vector_routing;

    my_time = new QTimer(this);
    connect(my_time,SIGNAL(timeout()),this,SLOT(rcv_msg()));
    my_time->start(100);

}


void  Messenger_window::rcv_msg(){
  //  std::string message = q.pop();
  //  std::cout << "Packet of size " << message.size() << " received, message: " << message << std::endl;

    if(router->message_to_disp.size()){
        router->m.lock();
                QString qs = QString::fromLocal8Bit(router->message_to_disp.c_str());
                router->message_to_disp = "";
        router->m.unlock();
        my_display->insertPlainText("Person said: " + qs + "\n");

    }else if(router->my_message_to_disp.size()){
        router->m.lock();
                QString qs = QString::fromLocal8Bit(router->my_message_to_disp.c_str());
                router->message_to_disp = "";
        router->m.unlock();
        my_display->insertPlainText("You said: " + qs + "\n");
    }

}


void Messenger_window::set_display_object(){

    display_object = new QGroupBox;
    my_display     = new MessageDisplay;
    my_display->setReadOnly(true);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(my_display,1,1,5,4,Qt::AlignTop);
    display_object->setLayout(layout);
}


void Messenger_window::set_type_object(){
    type_object = new QGroupBox(tr("Type"));
    line_to_write = new QLineEdit;
    QFontDatabase fontDB;
    fontDB.addApplicationFont(":/Resources/fonts/seguisym.ttf");
    comboBox_food   = new QComboBox();
    comboBox_fun    = new QComboBox();

    comboBox_food->setFont(QFont(QStringLiteral("Segoe UI Symbol")));
    comboBox_fun->setFont(QFont(QStringLiteral("Segoe UI Symbol")));

    for(int i =0; i< 20; i++){
        comboBox_food->addItem(food[i]);
    }
    for(int i =0; i< 20; i++){
        comboBox_fun->addItem(fun[i]);
    }

    line_to_write->setFont(QFont(QStringLiteral("Segoe UI Symbol")));
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(comboBox_food,1,1,1,1);
    layout->addWidget(comboBox_fun, 1,2,1,1);
    layout->addWidget(line_to_write,2,1,2,4,Qt::AlignBottom);
    type_object->setLayout(layout);
}

void Messenger_window::emoji_chosen_food(){
    line_to_write->insert(comboBox_food->currentText());
}
void Messenger_window::emoji_chosen_fun(){
    line_to_write->insert(comboBox_fun->currentText());
}

void Messenger_window::send_text(){
    if(!((line_to_write->text() == " ")||(line_to_write->text()== "  ")||(line_to_write->text() == "   ")||(line_to_write->text() == "    ")||(line_to_write->text() == "     ")||(line_to_write->text() == ""))){
        //my_display->insertPlainText("You said: " + line_to_write->text() + "\n");
       // senderClass->SendMessage(line_to_write->text().toStdString());
        router->send_text(line_to_write->text().toStdString(), '4');
    }
    line_to_write ->clear();
}

void Messenger_window::setLineEditTextFormat(QLineEdit* lineEdit, const QList<QTextLayout::FormatRange>& formats)
{
    if(!lineEdit)
        return;

    QList<QInputMethodEvent::Attribute> attributes;
    foreach(const QTextLayout::FormatRange& fr, formats)
    {
        QInputMethodEvent::AttributeType type = QInputMethodEvent::TextFormat;
        int start = fr.start - lineEdit->cursorPosition();
        int length = fr.length;
        QVariant value = fr.format;
        attributes.append(QInputMethodEvent::Attribute(type, start, length, value));
    }
    QInputMethodEvent event(QString(), attributes);
    QCoreApplication::sendEvent(lineEdit, &event);

}
void Messenger_window::clearLineEditTextFormat(QLineEdit* lineEdit)
{
    setLineEditTextFormat(lineEdit, QList<QTextLayout::FormatRange>());
}
