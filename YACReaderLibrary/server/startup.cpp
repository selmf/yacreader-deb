/**
  @file
  @author Stefan Frings
*/

#include "static.h"
#include "startup.h"
#include "dualfilelogger.h"
#include "httplistener.h"
#include "requestmapper.h"
#include "staticfilecontroller.h"

#include "yacreader_global.h"

#include <QDir>
#include <QCoreApplication>

/** Name of this application */
#define APPNAME "YACReaderLibrary"

/** Publisher of this application */
#define ORGANISATION "YACReader"

/** Short description of this application */
#define DESCRIPTION "Comic reader and organizer"

void Startup::start() {
	// Initialize the core application
    QCoreApplication* app = QCoreApplication::instance();

	QString configFileName=YACReader::getSettingsPath()+"/"+QCoreApplication::applicationName()+".ini";

	// Configure logging into files
	QSettings* mainLogSettings=new QSettings(configFileName,QSettings::IniFormat,app);
	mainLogSettings->beginGroup("mainLogFile");
    //QSettings* debugLogSettings=new QSettings(configFileName,QSettings::IniFormat,app);
    //debugLogSettings->beginGroup("debugLogFile");
    Logger* logger=new FileLogger(mainLogSettings,10000,app);
    logger->installMsgHandler();

	// Configure template loader and cache
	QSettings* templateSettings=new QSettings(configFileName,QSettings::IniFormat,app);
	templateSettings->beginGroup("templates");
	Static::templateLoader=new TemplateCache(templateSettings,app);

	// Configure session store
	QSettings* sessionSettings=new QSettings(configFileName,QSettings::IniFormat,app);
	sessionSettings->beginGroup("sessions");
	Static::sessionStore=new HttpSessionStore(sessionSettings,app);

	// Configure static file controller
	QSettings* fileSettings=new QSettings(configFileName,QSettings::IniFormat,app);
	fileSettings->beginGroup("docroot");
	Static::staticFileController=new StaticFileController(fileSettings,app);

	// Configure and start the TCP listener
	qDebug("ServiceHelper: Starting service");
	QSettings* listenerSettings=new QSettings(configFileName,QSettings::IniFormat,app);
	listenerSettings->beginGroup("listener");
	listener = new HttpListener(listenerSettings,new RequestMapper(app),app);

	qDebug("ServiceHelper: Service has started");
}


void Startup::stop() {
    qDebug("ServiceHelper: Service has been stopped");
    // QCoreApplication destroys all objects that have been created in start().
    if(listener!=nullptr)
    {
        listener->close();
        delete listener;
        listener = nullptr;
    }
}


Startup::Startup()
{

}

QString Startup::getPort()
{
	return QString("%1").arg(listener->serverPort());
}


