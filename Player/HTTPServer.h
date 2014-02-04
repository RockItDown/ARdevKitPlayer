#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QTcpServer>

class HttpServer : public QTcpServer
{
	Q_OBJECT

public:
	HttpServer(QObject *parent);
	~HttpServer();
	

public slots:
	void listenTo(quint16 port);
	void readClient();

signals:
	void newProject();
	void stopBroadcast();

protected:
	void incomingConnection(int handle);

private:
	
};

#endif // HTTPSERVER_H
