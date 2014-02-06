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
	void listenTo();
	void readClient();

signals:
	void newProject();
	void stopBroadcast(int);
	void error(QString);

protected:
	void incomingConnection(int handle);

private:
	
};

#endif // HTTPSERVER_H
