#include "StdAfx.h"
#include "HttpServer.h"

#include <QTcpSocket>
#include <QRegExp>
#include <QDateTime>
#include <QStringlist>
#include <QDebug>
#include "QuaZip\JlCompress.h"
#include <QFile>

HttpServer::HttpServer(QObject *parent)
	: QTcpServer(parent)
{

}

HttpServer::~HttpServer()
{

}

void HttpServer::listenTo(quint16 port)
{
	if(listen(QHostAddress::Any, port))
	{
		 new QDebug(new QString("Server started!"));
	}
	else
	{
		new QDebug(new QString("Server not started!"));
	}
}

void HttpServer::incomingConnection(int socket)
{
	QTcpSocket * s = new QTcpSocket(this);
	connect(s, SIGNAL(readyRead()), this, SLOT(readClient()));
	connect(s, SIGNAL(disconnected()), this, SLOT(discardClient()));
	s->setSocketDescriptor(socket);
}

void HttpServer::readClient()
	{
		QTcpSocket* socket = (QTcpSocket*)sender();
		if (socket->canReadLine()) 
		{
			QStringList tokens = QString(socket->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));
			if (tokens[0] == "GET") 
			{
				QTextStream os(socket);
				os.setAutoDetectUnicode(true);
				os <<  "HTTP/1.0 200 Ok\r\n"
					"Content-Type: text/html; charset=\"utf-8\"\r\n"
					"\r\n"
					"<h1>OK</h1>\n"
					<< QDateTime::currentDateTime().toString() << "\n";
				socket->close();

				if (socket->state() == QTcpSocket::UnconnectedState) 
				{
					delete socket;
				}
			}
			if(tokens[0] == "PUT")
			{
				QByteArray data = socket->readAll();
				QFile file("currentProject.zip");
				if(file.open(QIODevice::ReadWrite))
				{
					file.write(data);
					file.close();
				}

				//JlCompress::extractDir("currentProject.zip", "currentProject");
				emit newProject();
				if (socket->state() == QTcpSocket::UnconnectedState) 
				{
					delete socket;
				}
			}
			
			if(tokens[0] == "POST")
			{
				emit stopBroadcast();	
			}
		}
	}


