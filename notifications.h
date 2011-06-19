#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QtCore>
#include <QtDBus>

class Notifications
{
public slots:
    static void ShowBanner(QString message);
    static void ShowDialog(QString message, quint32 timeout);
};

#endif // NOTIFICATIONS_H
