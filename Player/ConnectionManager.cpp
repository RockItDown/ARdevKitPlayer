#include "StdAfx.h"
#include "ConnectionManager.h"

#include <QThread>
#include <QDebug>
#include "HttpServer.h"
#include "udpbroadcaster.h"

ConnectionManager::ConnectionManager(QObject *parent)
	: QObject(parent)
{
	udpThread = new QThread(this);
	braodcaster = new UdpBroadcaster(true, this);
	braodcaster->moveToThread(udpThread);

	connect(braodcaster, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
	connect(udpThread, SIGNAL(started()), braodcaster, SLOT(startBroadcasting(15000)));


	httpThread = new QThread(this);
	listener = new HttpServer(this);
	listener->moveToThread(httpThread);

	connect(listener, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
	connect(udpThread, SIGNAL(started()), listener, SLOT(listenTo(15000);));
	connect(listener, SIGNAL(stopBroadcast()), braodcaster, SLOT(pauseBroadcasting(20)));
}

ConnectionManager::~ConnectionManager()
{
	stop();
}

void ConnectionManager::start()
{
	httpThread->start();
	udpThread->start();
}

void ConnectionManager::stop()
{
	udpThread->quit();
	braodcaster->deleteLater();
	udpThread->deleteLater();

	httpThread->quit();
	listener->deleteLater();
	httpThread->deleteLater();	
}

void ConnectionManager::errorString(QString err)
{
	//qDebug(err);
}