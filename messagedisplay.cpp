#include "messagedisplay.h"

MessageDisplay::MessageDisplay()
{

}



void MessageDisplay::appendMessage(const QString& text)
{
    this->appendPlainText(text); // Adds the message to the widget
    this->verticalScrollBar()->setValue(this->verticalScrollBar()->maximum()); // Scrolls to the bottom
    QByteArray encodedString = text.toLocal8Bit();
    m_logFile.write(encodedString); // Logs to file
}
