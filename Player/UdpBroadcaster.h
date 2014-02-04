#ifndef UDPBROADCASTER_H
#define UDPBROADCASTER_H

#include <QObject>
#include <QUdpSocket>

class UdpBroadcaster : public QObject
{
	Q_OBJECT

public:
	UdpBroadcaster(bool running, QObject *parent);
	~UdpBroadcaster();

public slots:
	void startBroadcasting(quint16 port);
	void pauseBroadcasting(int secs);

signals:
	void error(QString err);

private:
	bool running;
};

#endif // UDPBROADCASTER_H
