#include "simlock.h"

SIMLock::SIMLock()
{
    simlock.Initialize();
}


SIMLock::~SIMLock()
{
    simlock.Dispose();
}

void SIMLock::Run()
{
    qDebug() << "Getting IMSI number";
    QString imsi = simlock.GetIMSI();

    if(!simlock.HasValidIMSI())
    {
	qDebug() << "Database doesn't contain any IMSI numbers, adding the current one";
	QString imsi = simlock.GetIMSI();
	if(!imsi.isEmpty() && !imsi.isNull())
	{
	    simlock.AddValidIMSI(imsi);
	    Notifications::ShowBanner("<b>SIMLock</b> has added this SIM card to the list of allowed SIMs");
	}
    }

    if(!simlock.IsValidIMSI(imsi))
    {
	qDebug() << "IMSI is Invalid, locking phone";
	Notifications::ShowBanner("<b>SIMLock</b> has locked this phone because the SIM card appears to have been changed");
	simlock.LockPhone();
	simlock.MakeOffline();

	while(simlock.IsLocked())
	    sleep(5);

	qDebug() << "Device Unlocked";
	QString imsi = simlock.GetIMSI();
	if(!imsi.isEmpty() && !imsi.isNull())
	{
	    simlock.AddValidIMSI(imsi);
	    Notifications::ShowBanner("<b>SIMLock</b> has added this SIM card to the list of allowed SIMs");
	}
	simlock.MakeOnline();
    }
    else
    {
	qDebug() << "IMSI is Valid";
    }
}
