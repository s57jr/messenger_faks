#ifndef MESSAGEDISPLAY_H
#define MESSAGEDISPLAY_H

#include <QWidget>
#include <QtWidgets>
#include <QFile>
#include <mutex>

#include "messenger_window.h"


class MessageDisplay : public QPlainTextEdit
{
    Q_OBJECT
/* snip */
public:
    MessageDisplay();
    void appendMessage(const QString& text);

private:
    QFile m_logFile;
};

#endif // MESSAGEDISPLAY_H
