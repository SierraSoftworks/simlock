#ifndef SIMLOCKSERVICE_H
#define SIMLOCKSERVICE_H

#include <QtDBus>
#include <QObject>
#include <QtCore>
#include "databaseinterface.h"
#include <mce/dbus-names.h>
#include <mce/mode-names.h>

class SIMLockService :public QObject
{
    Q_OBJECT

public:
    SIMLockService();
    ~SIMLockService();
    void Initialize();
    void Dispose();
    void LockPhone();
    void MakeOffline();
    void MakeOnline();
    QString GetIMSI();
    bool IsValidIMSI(QString imsi);
    void AddValidIMSI(QString imsi);
    void CheckCurrentIMSI();
    bool HasValidIMSI();
    bool IsLocked();
    bool ClearDatabase();
    QList<QVariant> GetValidIMSIs();

private:
    QDBusInterface *SIMInterface;
    QDBusInterface *LockInterface;
    DatabaseInterface *dbInterface;

private slots:
    void DeviceLockModeChanged(QString mode);

signals:
    void IMSIRetrieved(QString imsi);
    void ValidIMSI();
    void InvalidIMSI();
    void DeviceUnlocked();
};

#endif // SIMLOCKSERVICE_H
