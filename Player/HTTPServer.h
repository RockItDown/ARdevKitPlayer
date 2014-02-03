#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QTcpServer>

class HttpServer : public QTcpServer
{
	Q_OBJECT

public:
	HttpServer(QObject *parent);
	~HttpServer();
	void listenTo(quint16 port);

public slots:
	void readClient();

protected:

	void incomingConnection(int handle);

private:
	
};

#endif // HTTPSERVER_H
