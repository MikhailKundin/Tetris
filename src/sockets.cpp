#include "sockets.h"

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
	
}

void Sockets::setServerBtnPush()
{
	
}

void Sockets::setClientBtnPush()
{
	
}

void Sockets::connectBtnPush()
{
	
}

void Sockets::sendMessageBtnPush()
{
	
}
