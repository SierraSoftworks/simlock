#include "simlockservice.h"

SIMLockService::SIMLockService()
{
    //Initialize();
}

SIMLockService::~SIMLockService()
{
    //Dispose();
}

void SIMLockService::Initialize()
{
    dbInterface = new DatabaseInterface();
    dbInterface->SetDatabaseFile(QFileInfo("/opt/simlock/validSIMs.db"));
    dbInterface->Connect();
    qDebug() << "Connected to DB";

    SIMInterface = new QDBusInterface("com.nokia.phone.SIM","/com/nokia/phone/SIM","Phone.Sim",QDBusConnection::systemBus(),this);
    LockInterface = new QDBusInterface("com.nokia.system_ui","/com/nokia/system_ui/request","com.nokia.system_ui.request", QDBusConnection::systemBus(), this);
    //LockInterface = new QDBusInterface(MCE_SERVICE,MCE_REQUEST_PATH,MCE_REQUEST_IF, QDBusConnection::systemBus(),this);

    LockInterface->connection().connect(MCE_SERVICE,MCE_SIGNAL_PATH, MCE_SIGNAL_IF, MCE_DEVLOCK_MODE_SIG,this,SLOT(DeviceLockModeChanged(QString)));

    if(!SIMInterface->isValid())
	qDebug() << "SIMInterface unavailable";
    if(!LockInterface->isValid())
	qDebug() << "SIMInterface unavailable";
}

void SIMLockService::Dispose()
{
    dbInterface->Close();
}

QString SIMLockService::GetIMSI()
{
    //dbus-send --system --type=method_call --print-reply --dest=com.nokia.phone.SIM /com/nokia/phone/SIM Phone.Sim.get_imsi|awk -F "\"" '/g/ {print $2}'


    QDBusReply<QString> reply = SIMInterface->call("get_imsi");
    if(!reply.isValid())
    {
	qDebug() << "Invalid reply from DBus";
	emit IMSIRetrieved("");
	return "";
    }

    qDebug() << "Current IMSI:" << reply.value();
    emit IMSIRetrieved(reply.value());
    return reply.value();
}

void SIMLockService::LockPhone()
{
    //dbus-send --system --type=method_call
    //--dest=com.nokia.system_ui /com/nokia/system_ui/request com.nokia.system_ui.request.devlock_open
    //string:"com.nokia.mce"
    //string:"/com/nokia/mce/request"
    //string:"com.nokia.mce.request"
    //string:"devlock_callback"
    //uint32:'3'


	QDBusMessage reply = LockInterface->call("devlock_open",
						 "com.nokia.mce",
						 "/com/nokia/mce/request",
						 "com.nokia.mce.request",
						 "devlock_callback", (quint32)3);



	if(reply.type() == QDBusMessage::ErrorMessage)
	    qDebug() << "Failed to lock phone:" << reply.errorName() << reply.errorMessage();

	if(reply.arguments()[0].toBool() == true)
	    qDebug() << "Phone locked";
	else
	    qDebug() << "Phone failed to lock";

}

void SIMLockService::MakeOffline()
{

    ///*
    LockInterface->asyncCall(MCE_DEVICE_MODE_CHANGE_REQ,MCE_FLIGHT_MODE);
    //*/
}

void SIMLockService::MakeOnline()
{

    ///*
    LockInterface->asyncCall(MCE_DEVICE_MODE_CHANGE_REQ,MCE_NORMAL_MODE);
    //*/
}

bool SIMLockService::IsValidIMSI(QString imsi)
{
    if(dbInterface->CheckIMSI(imsi))
    {
	emit ValidIMSI();
	return true;
    }
    else
    {
	emit InvalidIMSI();
	return false;
    }
}

bool SIMLockService::HasValidIMSI()
{
    dbInterface->CreateDatabase();
    return dbInterface->HasRecords();
}

void SIMLockService::AddValidIMSI(QString imsi)
{
    dbInterface->AddIMSI(imsi.trimmed());
}

void SIMLockService::DeviceLockModeChanged(QString mode)
{
    qDebug() << "Device Lock Mode Changed";
    if(mode == MCE_DEVICE_UNLOCKED)
	emit DeviceUnlocked();
}

bool SIMLockService::IsLocked()
{
    QDBusReply<QString> reply = LockInterface->call(MCE_DEVLOCK_MODE_GET);
    if(!reply.isValid())
	return false;
    return reply.value() == MCE_DEVICE_LOCKED;
}

bool SIMLockService::ClearDatabase()
{
    dbInterface->ClearDB();
    return true;
}

QList<QVariant> SIMLockService::GetValidIMSIs()
{
    return dbInterface->GetRecords();
}
