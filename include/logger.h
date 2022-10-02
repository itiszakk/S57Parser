#ifndef LOGGER_H
#define LOGGER_H

#include <QWidget>
#include <QTextBrowser>
#include <QDateTime>
#include <QString>
#include <QColor>

class Logger
{

public:
    Logger(QTextBrowser *logBrowser);

    void debug(const QString &message);
    void info(const QString &message);
    void warning(const QString &message);
    void error(const QString &message);

private:
    QTextBrowser *logBrowser;

    const QString DEBUG_MESSAGE_TYPE = "DEBUG";
    const QString INFORMATION_MESSAGE_TYPE = "INFO";
    const QString WARNING_MESSAGE_TYPE = "WARNING";
    const QString ERROR_MESSAGE_TYPE = "ERROR";

    /* HTML color names */
    const QString DEBUG_COLOR = "DodgerBlue";
    const QString INFORMATION_COLOR = "ForestGreen";
    const QString WARNING_COLOR = "Orange";
    const QString ERROR_COLOR = "Firebrick";

    QString getFormatedString(const QString &messageType, const QString &htmlColor, const QString &message);
};

#endif // LOGGER_H
