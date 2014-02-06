#include "StdAfx.h"
#include "UdpBroadcaster.h"
#include <QNetworkInterface>
#include <Qtime>
#include <QCoreApplication>

UdpBroadcaster::UdpBroadcaster(bool readyForStart, QObject *parent)
	: QObject(parent)
{
	running = readyForStart;
}

UdpBroadcaster::~UdpBroadcaster()
{
	running = false;
}

void UdpBroadcaster::startBroadcasting()
{
	QUdpSocket * broadcaster = new QUdpSocket(this);
	QString IpAddress = "";
	for each(const QHostAddress &address in QNetworkInterface::allAddresses()) {
    if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
          IpAddress = address.toString();
	}
	QByteArray conInfo;
	conInfo.append(IpAddress.append(":").append(15000));
	while(true)
	{
		broadcaster->writeDatagram(conInfo, QHostAddress::Broadcast, 15001);
		pauseBroadcasting(2);
	}
}

void UdpBroadcaster::pauseBroadcasting(int secs)
{
	QTime dieTime= QTime::currentTime().addSecs(secs);
	while( QTime::currentTime() < dieTime )
	QCoreApplication::processEvents(QEventLoop::AllEvents, 1000);
}