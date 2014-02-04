#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <QObject>
#include <QThread>
#include "HttpServer.h"
#include "udpbroadcaster.h"

class ConnectionManager : public QObject
{
	Q_OBJECT

public:
	ConnectionManager(QObject *parent);
	~ConnectionManager();

	void start();
	void stop();

public slots:
	void errorString(QString err);

private:
	QThread * httpThread;
	QThread * udpThread;
	HttpServer * listener;
	UdpBroadcaster * braodcaster;
};

#endif // CONNECTIONMANAGER_H
