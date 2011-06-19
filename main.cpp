#include <QtCore/QCoreApplication>
#include <simlock.h>
#include <stdio.h>
using namespace std;

void showHelp()
{
    qDebug() << "SIMLock by Sierra Softworks\n";
    qDebug() << "simlock [OPTIONS]\n";
    qDebug() << "  -d      | Run in Daemon Mode\n";
    qDebug() << "  --clear | Clear the valid SIM card database\n";
    qDebug() << "  --help  | Show this help page\n";
    qDebug() << "  --show  | Show a list of the valid SIM cards";
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
	    qDebug() << "Starting SIMLockD";

	    service.Run();

	    qDebug() << "SIMLockD Exiting";
	    return 0;
	}
	else if(arg == "--clear")
	{
	    //Clear the SIMLock database
	    SIMLockService service;
	    service.Initialize();
	    service.ClearDatabase();
	    service.Dispose();
	    return 0;
	}
	else if(arg == "--show")
	{
	    qDebug() << "Creating Service Instace";
	    SIMLockService service;
	    service.Initialize();

	    qDebug() << "Getting IMSI numbers";
	    QList<QVariant> records = service.GetValidIMSIs();

	    service.Dispose();

	    qDebug() << "Printing IMSI numbers";

	    if(records.length() > 0)
	    {
		qDebug() << "Valid IMSI Numbers:";
		for(int i = 0; i < records.length();i++)
		    qDebug() << "  " << records.at(i).toString();
	    }
	    else
	    {
		qDebug() << "No Valid IMSI Numbers in Database";
	    }
	    return 0;

	}
	else if(arg == "--help" || arg == "-?" || arg == "/?")
	{
	    showHelp();
	    return 0;
	}
    }


    //Print the help
    showHelp();

    return 0;
}

