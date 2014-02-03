#ifndef HTTPLISTENER_H
#define HTTPLISTENER_H

#include <QObject>
#inclucde <QDebug>
#include <QTcpServer>
#include <QTcpSocket>


class HttpListener : public QObject
{
	Q_OBJECT

public:
	explicit HttpListener(QObject *parent);
	
signals:


public slots:
	void newConnection();


private:
	QTcpServer * server;
};

#endif // HTTPLISTENER_H
