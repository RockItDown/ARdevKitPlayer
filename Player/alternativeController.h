#ifndef ALTERNATIVECONTROLLER_H
#define ALTERNATIVECONTROLLER_H

#include <QObject>
#include <qthread.h>
#include <qudpsocket.h>
#include <qtcpserver.h>


class alternativeController : public QObject
{
	Q_OBJECT

public:
	alternativeController(QObject *parent);
	~alternativeController();

public slots:
	void incomingBroadcast();
	void newConnection();

public signals:
	newProject();

private:
	QThread t;
	QUdpSocket * udpSocket;
	QTcpServer  * tcpServer;
};

#endif // ALTERNATIVECONTROLLER_H
