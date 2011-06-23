/*
*******************************************************
**                 Sierra Softworks                  **
**              Benjamin Pannell - 2011              **
*******************************************************

This application's source code is licenced under a
GNU GPL licence. As such you are free to modify,
redistribute, use and copy the code contained within
provided you stay within the limits of this licence.

More information on the GNU GPL can be found at:
http://www.gnu.org/licenses/gpl.html

Please also leave this header intact on all source
files and provide credit on any about pages if code
from this file is directly copied or reused.

*/

#ifndef DATABASEINTERFACE_H
#define DATABASEINTERFACE_H

#include <Qt/qobject.h>
#include <Qt/qsqldatabase.h>
#include <Qt/qsqlquery.h>
#include <Qt/qsqlerror.h>
#include <Qt/qsqlresult.h>
#include <Qt/qsqlrecord.h>
#include <Qt/qdebug.h>
#include <Qt/qsqldriver.h>
#include <Qt/qfileinfo.h>
#include <Qt/qdir.h>

class DatabaseInterface : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseInterface();
    virtual ~DatabaseInterface();
    QFileInfo GetDatabaseFile();
    void SetDatabaseFile(QFileInfo file);
    void CreateDatabase();
    void ClearDB();
    bool AddIMSI(QString imsi);
    bool CheckIMSI(QString imsi);
    bool RemoveIMSI(QString imsi);
    bool HasRecords();
    QList<QVariant> GetRecords();

private:
    static QFileInfo databaseFile;
    QSqlDatabase dbConnection;

public slots:
    bool Connect();
    void Close();

signals:
    void Connected();
    void ConnectionFailed(QString error);
    void ValidIMSI();
    void InvalidIMSI();
    void IMSIAdded();

};

#endif // DATABASEINTERFACE_H
