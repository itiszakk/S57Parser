#include "logger.h"


Logger::Logger(QTextBrowser *logBrowser)
    :logBrowser(logBrowser)
{

}

void Logger::debug(const QString &message)
{
    QString logMessage = getFormatedString(DEBUG_MESSAGE_TYPE, DEBUG_COLOR, message);

    logBrowser->append(logMessage);
    logBrowser->repaint();
}


void Logger::info(const QString &message)
{
    QString logMessage = getFormatedString(INFORMATION_MESSAGE_TYPE, INFORMATION_COLOR, message);

    logBrowser->append(logMessage);
    logBrowser->repaint();
}


void Logger::warning(const QString &message)
{
    QString logMessage = getFormatedString(WARNING_MESSAGE_TYPE, WARNING_COLOR, message);

    logBrowser->append(logMessage);
    logBrowser->repaint();
}


void Logger::error(const QString &message)
{
    QString logMessage = getFormatedString(ERROR_MESSAGE_TYPE, ERROR_COLOR, message);

    logBrowser->append(logMessage);
    logBrowser->repaint();
}

QString Logger::getFormatedString(const QString &messageType, const QString &htmlColor, const QString &message)
{
    QDateTime dateTime = QDateTime::currentDateTime();
    return QString("%1 [<font color=%2><b>%3</b></font>]: %4").arg(dateTime.time().toString(), htmlColor, messageType, message);
}
