#ifndef MESSENGER_WINDOW_H
#define MESSENGER_WINDOW_H

#include <stdlib.h>
#include <QTimer>
#include <math.h>
#include <QDebug>
#include <iostream>
#include <QKeyEvent>
#include <QtWidgets>
#include <QWidget>
#include "ComSender.h"
#include "rec.h"
#include <mutex>
#include "vector_routing.h"
#include "router.h"

#include "messagedisplay.h"

class router;

extern BlockingQueue<std::string> q;

class QLineEdit;
class QCheckBox;
class QLabel;
class MessageDisplay;
class ComSender;
class Rec;

class Messenger_window : public QWidget
{
    Q_OBJECT
public:
    Messenger_window(QWidget *parent = 0);
    void clearLineEditTextFormat(QLineEdit* lineEdit);
    void setLineEditTextFormat(QLineEdit* lineEdit, const QList<QTextLayout::FormatRange>& formats);

    QTimer *my_time;
    QThread *my_thread;
    QThread *recv;
    std::thread t;

    std::vector<uint16_t> sequence_nr;
    void create_buttons();
signals:


public slots:
    void set_display_object();
    void set_type_object();
    void rcv_msg();

private slots:
    void emoji_chosen_food();
    void emoji_chosen_fun();
    void send_text();


private:
    QLineEdit       *line_to_write;
    QGroupBox       *display_object;
    QGroupBox       *type_object;
    QGroupBox       *choose_rec_object;
    QComboBox       *comboBox_food;
    QComboBox       *comboBox_fun;
    ComSender       *senderClass;
    Rec             *myrec;
    MessageDisplay  *my_display;
    router          *router1;
    QCheckBox       *ip1;
    QCheckBox       *ip2;
    QCheckBox       *ip3;
    QCheckBox       *ip4;
    QCheckBox       *multicast;
    QLabel          *ip1_label;
    QLabel          *ip2_label;
    QLabel          *ip3_label;
    QLabel          *ip4_label;
    QLabel          *multicast_label;
};

#endif // MESSENGER_WINDOW_H
