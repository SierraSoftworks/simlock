#include <QtCore/QCoreApplication>
#include <simlock.h>
#include <stdio.h>
using namespace std;

void showHelp()
{
    qDebug() << "SIMLock by Sierra Softworks";
    qDebug() << "http://sierrasoftworks.com/simlock";
    qDebug() << "";
    qDebug() << "simlock [OPTIONS]";
    qDebug() << "  --add -a	    [IMSI]";
    qDebug() << "    Adds the specified IMSI to the database";
    qDebug() << "  --remove -r	    [IMSI]";
    qDebug() << "    Removes the specified IMSI from the database";
    qDebug() << "  --show -s";
    qDebug() << "    Show a list of the valid SIM cards";
    qDebug() << "  --clear -c";
    qDebug() << "    Clear the valid SIM card database";
    qDebug() << "  -d";
    qDebug() << "    Run in Daemon Mode";
    qDebug() << "  --help -?";
    qDebug() << "    Show this help page";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    a.setApplicationName("SIMLock");
    a.setOrganizationName("Sierra Softworks");
    a.setOrganizationDomain("sierrasoftworks.com");

    //Check if there was any command line parameters


    for(int i = 0; i < argc; i++)
    {
	QString arg = QString(argv[i]);
	if(arg == "-d")
	{
	    SIMLock service;
	    qDebug() << "Starting SIMLock";

	    service.Run();
	    qDebug() << "SIMLock Exiting";
	    return 0;
	}
	else if(arg == "--clear" || arg == "-c")
	{
	    //Clear the SIMLock database
	    SIMLockService service;
	    service.Initialize();
	    service.ClearDatabase();
	    service.Dispose();
	    return 0;
	}
	else if(arg == "--show" || arg == "-s")
	{
	    SIMLockService service;
	    service.Initialize();

	    QList<QVariant> records = service.GetValidIMSIs();

	    service.Dispose();


	    if(records.length() > 0)
	    {
		for(int i = 0; i < records.length();i++)
		    qDebug() << "  " << records.at(i).toString();
	    }
	    else
	    {
		qDebug() << "No Valid IMSI Numbers in Database";
	    }
	    return 0;

	}
	else if(arg == "--add" || arg == "-a")
	{
	    if(i == argc)
	    {
		qDebug() << "You must provide an IMSI number";
		return 1;
	    }
	    qDebug() << "Adding IMSI Number:" << argv[i + 1];

	    SIMLockService service;
	    service.Initialize();
	    service.AddValidIMSI(QString(argv[i + 1]));
	    service.Dispose();
	    qDebug() << "IMSI Added";
	    return 0;
	}
	else if(arg == "--remove" || arg == "-r")
	{
	    if(i == argc)
	    {
		qDebug() << "You must provide an IMSI number";
		return 1;
	    }


	    SIMLockService service;
	    service.Initialize();

	    QString imsi = QString(argv[i + 1]);

	    if(!service.IsValidIMSI(imsi))
	    {
		qDebug() << "The provided IMSI is not in the database";
		delete &service;
		return 2;
	    }

	    qDebug() << "Removing IMSI from database";

	    service.RemoveIMSI(imsi);

	    service.Dispose();
	    qDebug() << "IMSI Removed";
	    return 0;
	}
	else if(arg == "--help" || arg == "-?")
	{
	    showHelp();
	    return 0;
	}
    }


    //Print the help
    showHelp();

    return 0;
}

