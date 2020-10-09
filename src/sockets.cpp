#include "sockets.h"

#include <QDebug>
#include <QHostAddress>

Sockets::Sockets(QWidget *parent) : QWidget(parent)
{
	hBox = std::make_unique<QHBoxLayout>();
	vBox = std::make_unique<QVBoxLayout>(this);
	
	setServerBtn = std::make_unique<QPushButton>("Создать сервер", this);
	setClientBtn = std::make_unique<QPushButton>("Создать клиент", this);
	connectBtn = std::make_unique<QPushButton>("Присоединиться", this);
	sendMessageBtn = std::make_unique<QPushButton>("Отправить сообщение", this);
	
	console = std::make_unique<QTextEdit>(this);
	
	hBox->addWidget(setServerBtn.get());
	hBox->addWidget(setClientBtn.get());
	hBox->addWidget(connectBtn.get());
	hBox->addWidget(sendMessageBtn.get());
	
	vBox->addWidget(console.get());
	vBox->addLayout(hBox.get());
	
	connect(setServerBtn.get(), &QPushButton::pressed, this, &Sockets::setServerBtnPush);
	connect(setClientBtn.get(), &QPushButton::pressed, this, &Sockets::setClientBtnPush);
	connect(connectBtn.get(), &QPushButton::pressed, this, &Sockets::connectBtnPush);
	connect(sendMessageBtn.get(), &QPushButton::pressed, this, &Sockets::sendMessageBtnPush);
	
	socket = std::make_unique<QTcpSocket>(this);
}

void Sockets::setServerBtnPush()
{
	consoleAdd("Сервер");
}

void Sockets::setClientBtnPush()
{
	consoleAdd("Клиент");
}

void Sockets::connectBtnPush()
{
	socket->bind(QHostAddress::LocalHost, 12345);
	socket->connectToHost(QHostAddress::LocalHost, 12345);
	connect(socket.get(), &QTcpSocket::connected, this, &Sockets::socketStateChanged);
	
}

void Sockets::sendMessageBtnPush()
{
	socket->write("Hello!");
}

void Sockets::readMessage()
{
	consoleAdd(socket->readAll());
}

void Sockets::socketStateChanged()
{
	qDebug() << socket->state();
	consoleAdd("State changed");
}

void Sockets::consoleAdd(const QString &str) const
{
	console->append(str);
	console->repaint();
}
