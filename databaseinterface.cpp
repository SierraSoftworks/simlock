#include "databaseinterface.h"
#include <QtCore/QCoreApplication>

DatabaseInterface::DatabaseInterface()
{
    databaseFile = QFileInfo(QDir::homePath() + "/.simlock/validimsi.sqlite");
}

DatabaseInterface::~DatabaseInterface()
{
    dbConnection.close();
}

QFileInfo DatabaseInterface::databaseFile;


QFileInfo DatabaseInterface::GetDatabaseFile()
{
    return databaseFile;
}

void DatabaseInterface::SetDatabaseFile(QFileInfo file)
{
    databaseFile = file;
}

bool DatabaseInterface::Connect()
{
    QDir *databaseDir = new QDir(databaseFile.absoluteDir());

    if(!databaseDir->exists())
	databaseDir->mkdir(databaseDir->absolutePath());

    dbConnection = QSqlDatabase::addDatabase("QSQLITE");
    dbConnection.setDatabaseName(GetDatabaseFile().absoluteFilePath());
    dbConnection.open();

    if(dbConnection.isOpen() && !dbConnection.isOpenError())
	emit Connected();
    else
	emit ConnectionFailed(dbConnection.lastError().text());
    return dbConnection.isOpen() && !dbConnection.isOpenError();

}

void DatabaseInterface::CreateDatabase()
{
    if(!dbConnection.isOpen())
	dbConnection.open();
    dbConnection.exec("CREATE TABLE IF NOT EXISTS imsi(imsi VARCHAR(15) primary key not null)");
}

bool DatabaseInterface::AddIMSI(QString imsi)
{
    try
    {
	dbConnection.exec("INSERT INTO `imsi` VALUES('" + imsi + "')");

	if(dbConnection.lastError().type() != QSqlError::NoError)
	    return false;

	emit IMSIAdded();
	return true;
    }
    catch(...)
    {
	return false;
    }
}

bool DatabaseInterface::CheckIMSI(QString imsi)
{
    QSqlQuery query = dbConnection.exec("SELECT count(*) FROM `imsi` WHERE `imsi`='" + imsi + "'");
    if(!query.next())
    {
	emit InvalidIMSI();
	return false;
    }
    bool valid = query.value(0).toInt() != 0;

    if(valid)
	emit ValidIMSI();
    else
	emit InvalidIMSI();

    return valid;
}


void DatabaseInterface::ClearDB()
{
    if(!dbConnection.isOpen())
	dbConnection.open();
    dbConnection.exec("DELETE FROM `imsi`");
}

void DatabaseInterface::Close()
{
    QSqlDatabase().close();
}

bool DatabaseInterface::HasRecords()
{
    if(!dbConnection.isOpen())
	return false;

    QSqlQuery query = dbConnection.exec("SELECT count(*) from `imsi`");
    if(!query.next())
	return false;

    if(query.value(0).toInt() != 0)
	return true;
    return false;
}

QList<QVariant> DatabaseInterface::GetRecords()
{
    QSqlQuery query = dbConnection.exec("SELECT * FROM `imsi`");

    QList<QVariant> results;

    while(query.next())
    {
	results << query.value(0);
    }
    return results;

}
