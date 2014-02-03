#include "StdAfx.h"
#include "HttpListener.h"

HttpListener::HttpListener(QObject *parent)
	: QObject(parent)
{
	server = new QTcpServer(this);

	connect(server,SIGNAL(newConnection()), this, SLOT(newConnection()));

	if(!server->(QHostAddress::Any, 15000)
	{
		qDebug() << "Server could not start!";
	}
	else
	{
		qDebug() << "Server could not start!";
	}
}

void HttpListener::newConnection()
{
	QTcpSocket *socket = server->nextPendingConnection();

	socket->write("");
	socket->flush();

	socket->close();
}