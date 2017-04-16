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

#include "messagedisplay.h"



extern BlockingQueue<std::string> q;

class QLineEdit;

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
    QComboBox       *comboBox_food;
    QComboBox       *comboBox_fun;
    ComSender       *senderClass;
    Rec             *myrec;
    MessageDisplay  *my_display;

};

#endif // MESSENGER_WINDOW_H
