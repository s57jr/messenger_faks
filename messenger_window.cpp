#include "messenger_window.h"
#include "icons.h"
#include <thread>
#include <cstring>
#include <unistd.h>
#include <iostream>
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
    create_buttons();

    num_of_receivers=0;
    //signals

    connect(comboBox_food,SIGNAL(currentIndexChanged(int)),this,SLOT(emoji_chosen_food()));
    connect(comboBox_fun,SIGNAL(currentIndexChanged(int)),this,SLOT(emoji_chosen_fun()));
    connect(line_to_write,SIGNAL(returnPressed()),this,SLOT(send_text()));
    connect(ip1,SIGNAL(stateChanged(int)),this,SLOT(set_receiver()));
    connect(ip2,SIGNAL(stateChanged(int)),this,SLOT(set_receiver()));
    connect(ip3,SIGNAL(stateChanged(int)),this,SLOT(set_receiver()));
    connect(ip4,SIGNAL(stateChanged(int)),this,SLOT(set_receiver()));
    connect(multicast,SIGNAL(stateChanged(int)),this,SLOT(set_receiver()));




    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(type_object,3,1,2,4,Qt::AlignBottom);
    mainLayout->addWidget(display_object,1,1,5,4,Qt::AlignTop);
    mainLayout->addWidget(choose_rec_object,2,1,1,4,Qt::AlignTop);
    mainLayout->setRowStretch(1,5);
    setLayout(mainLayout);

    setWindowTitle(tr("MessengerPro2"));

    router1 = new router;

    my_time = new QTimer(this);
    connect(my_time,SIGNAL(timeout()),this,SLOT(rcv_msg()));
    my_time->start(0);

}

void Messenger_window::set_receiver(){
    current_receivers=std::vector<std::string>(0);
    if(ip1->checkState()){
        current_receivers.push_back("1");
    }
    if(ip2->checkState()){
        current_receivers.push_back("2");
    }
    if(ip3->checkState()){
        current_receivers.push_back("3");
    }
    if(ip4->checkState()){
        current_receivers.push_back("4");
    }
    if(multicast->checkState()){
        current_receivers=std::vector<std::string>(0);
        current_receivers.push_back("1");
        current_receivers.push_back("2");
        current_receivers.push_back("3");
        current_receivers.push_back("4");


    }
}


void  Messenger_window::rcv_msg(){
  //  std::string message = q.pop();
  //  std::cout << "Packet of size " << message.size() << " received, message: " << message << std::endl;
    if(router1->message_to_disp.size()){
        router1->m.lock();
                QString qs = QString::fromLocal8Bit(router1->message_to_disp.c_str());
                router1->message_to_disp = "";
        router1->m.unlock();
        switch(router1->source){
            case '1': my_display->insertPlainText("ERNEST SAID: " + qs + "\n");break;
            case '2': my_display->insertPlainText("JOST SAID: " + qs + "\n");break;
            case '3': my_display->insertPlainText("FLORIAN SAID: " + qs + "\n");break;
            case '4': my_display->insertPlainText("RAOUL SAID: " + qs + "\n");break;

        }



    }else if(router1->my_message_to_disp.size()){
        router1->m.lock();
                QString qs = QString::fromLocal8Bit(router1->my_message_to_disp.c_str());
                router1->my_message_to_disp = "";
        router1->m.unlock();
        switch(std::stoi(current_receivers[0])){
            case 1: my_display->insertPlainText("YOU SAID TO ERNEST: " + qs + "\n");break;
            case 2: my_display->insertPlainText("YOU SAID TO JOST: " + qs + "\n");break;
            case 3: my_display->insertPlainText("YOU SAID TO FLORIAN: " + qs + "\n");break;
            case 4: my_display->insertPlainText("YOU SAID TO RAOUL: " + qs + "\n");break;

        }
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
    layout->addWidget(comboBox_food,2,3,1,1, Qt::AlignRight);
    layout->addWidget(comboBox_fun, 2,4,1,1,Qt::AlignRight);
    layout->addWidget(line_to_write,3,1,2,4,Qt::AlignBottom);
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
        std::cout << "sending" << std::endl;
        for(int t =0 ; t<current_receivers.size();t++){
            router1->send_text(line_to_write->text().toStdString(), current_receivers[t]);
            router1->increment_seq_nr();

        }
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

void Messenger_window::create_buttons(){

    choose_rec_object = new QGroupBox(tr("choose receiver"));
    choose_rec_object->setPalette(QPalette(Qt::black    ));

    ip1=new QCheckBox;
    ip2=new QCheckBox;
    ip3=new QCheckBox;
    ip4=new QCheckBox;
    multicast=new QCheckBox;


    ip1_label = new QLabel(tr("Ernest"));
    ip2_label = new QLabel(tr("Jost"));
    ip3_label = new QLabel(tr("Florian"));
    ip4_label = new QLabel(tr("Raoul"));
    multicast_label = new QLabel(tr("To all"));

    ip1_label->setStyleSheet("QLabel { background-color : white; color : blue; }");
    ip2_label->setStyleSheet("QLabel { background-color : white; color : blue; }");
    ip3_label->setStyleSheet("QLabel { background-color : white; color : blue; }");
    ip4_label->setStyleSheet("QLabel { background-color : white; color : blue; }");
    multicast_label->setStyleSheet("QLabel { background-color : white; color : blue; }");

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(ip1,1,1,1,1);
    layout->addWidget(ip2,1,2,1,1);
    layout->addWidget(ip3,1,3,1,1);
    layout->addWidget(ip4,1,4,1,1);
    layout->addWidget(multicast,1,5,1,1);

    layout->addWidget(ip1_label,2,1,1,1);
    layout->addWidget(ip2_label,2,2,1,1);
    layout->addWidget(ip3_label,2,3,1,1);
    layout->addWidget(ip4_label,2,4,1,1);
    layout->addWidget(multicast_label,2,5,1,1);

    choose_rec_object->setLayout(layout);
}

void Messenger_window::clearLineEditTextFormat(QLineEdit* lineEdit)
{
    setLineEditTextFormat(lineEdit, QList<QTextLayout::FormatRange>());
}
