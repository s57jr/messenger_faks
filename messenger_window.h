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


#include "messagedisplay.h"

class QLineEdit;

class MessageDisplay;
class ComSender;

class Messenger_window : public QWidget
{
    Q_OBJECT
public:
    Messenger_window(QWidget *parent = 0);
    void clearLineEditTextFormat(QLineEdit* lineEdit);
    void setLineEditTextFormat(QLineEdit* lineEdit, const QList<QTextLayout::FormatRange>& formats);

    QTimer *my_time;
    std::thread t;
signals:


public slots:
    void set_display_object();
    void set_type_object();
    void send_msg();

private slots:
    void emoji_chosen_food();
    void emoji_chosen_fun();
    void send_text();


private:
    MessageDisplay  *my_display;
    QLineEdit       *line_to_write;
    QGroupBox       *display_object;
    QGroupBox       *type_object;
    QComboBox       *comboBox_food;
    QComboBox       *comboBox_fun;
    ComSender       *senderClass;

};

#endif // MESSENGER_WINDOW_H
