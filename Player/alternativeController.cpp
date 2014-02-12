#include "StdAfx.h"
#include "alternativeController.h"

#include <qthread.h>
#include <qudpsocket.h>
#include <qtcpserver.h>
#include <qtcpsocket.h>
#include <qnetworkinterface.h>
#include <qfile.h>
#include <QuaZip\JlCompress.h>

alternativeController::alternativeController(QObject *parent)
	: QObject(parent)
{
	udpSocket = new QUdpSocket(this);
	tcpServer = new QTcpServer(this);
	udpSocket->bind(QHostAddress::Any, 12345);
	connect(udpSocket, SIGNAL(readyRead()), this, SLOT(incomingBroadcast()));
	connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
	tcpServer->listen(QHostAddress::Any, 12345);
	moveToThread(&t);
    t.start();
}

alternativeController::~alternativeController()
{
	udpSocket->close();
	tcpServer->close();
	t.quit();
    t.wait();
}

void alternativeController::incomingBroadcast()
{
	QByteArray sendmsg = QByteArray("OK:12345");
	QByteArray buffer;
	buffer.resize(udpSocket->pendingDatagramSize());

	QHostAddress sender;
	quint16 senderPort;
	udpSocket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

	udpSocket->writeDatagram(sendmsg, sender, senderPort); 
	tcpServer->listen(sender, 12345);
}
	
void alternativeController::newConnection()
{
	QTcpSocket * socket = tcpServer->nextPendingConnection();

	QByteArray project = socket->readAll();
	QFile file("currentProject.zip");
	if(file.open(QIODevice::ReadWrite))
	{
		file.write(project);
		file.close();
	}
	//JlCompress::extractDir("currentProject.zip", "currentProject");
	emit newProject();
}
