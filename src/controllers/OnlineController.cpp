#include "OnlineController.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

#include "../TetrisInfo.h"

OnlineController::OnlineController()
{
	
}

OnlineController::~OnlineController()
{
	
}

void OnlineController::makeServer()
{
	QTcpServer *server = new QTcpServer(this);
	connected = false;
	server->listen(QHostAddress::Any, PORT);
	connect(server, &QTcpServer::newConnection, this, &OnlineController::connectedToServer);
	connect(this, &OnlineController::deleteServerSignal, server, &QTcpServer::deleteLater);
}

void OnlineController::makeClient(const QString &ip)
{
	socket = new QTcpSocket(this);
	QTimer *timer = new QTimer(this);
	timer->setSingleShot(true);
	timer->setInterval(3000);
	
	socket->connectToHost(ip, PORT);
	timer->start();
	
	connect(socket, &QTcpSocket::connected, this, &OnlineController::clientConnected);
	connect(socket, &QTcpSocket::connected, timer, &QTimer::deleteLater);
	connect(socket, &QTcpSocket::errorOccurred, this, &OnlineController::connectionTimeout);
	connect(this, &OnlineController::deleteClientSignal, socket, &QTcpSocket::deleteLater);
	connect(socket, &QTcpSocket::errorOccurred, timer, &QTimer::deleteLater);
	connect(timer, &QTimer::timeout, this, &OnlineController::connectionTimeout);
	connect(timer, &QTimer::timeout, timer, &QTimer::deleteLater);
	connect(this, &OnlineController::deleteTimer, timer, &QTimer::deleteLater);
}

void OnlineController::deleteServer()
{
	emit deleteServerSignal();
}

void OnlineController::deleteSocket()
{
	emit deleteTimer();
	emit deleteClientSignal();
	socket = nullptr;
}

void OnlineController::stop()
{
	m_stop = true;
}

void OnlineController::start()
{
	m_stop = false;
}

void OnlineController::moveRight()
{
	writeSocket(Code::MoveRight);
}

void OnlineController::moveLeft()
{
	writeSocket(Code::MoveLeft);
}

void OnlineController::moveDown()
{
	writeSocket(Code::MoveDown);
}

void OnlineController::rotate()
{
	writeSocket(Code::Rotate);
}

void OnlineController::newFigure(quint8 figure)
{
	switch(figure)
	{
	case TetrisInfo::Figures::I:
		writeSocket(Code::IFigure);
		break;
	case TetrisInfo::Figures::O:
		writeSocket(Code::OFigure);
		break;
	case TetrisInfo::Figures::T:
		writeSocket(Code::TFigure);
		break;
	case TetrisInfo::Figures::L:
		writeSocket(Code::LFigure);
		break;
	case TetrisInfo::Figures::J:
		writeSocket(Code::JFigure);
		break;
	case TetrisInfo::Figures::S:
		writeSocket(Code::SFigure);
		break;
	case TetrisInfo::Figures::Z:
		writeSocket(Code::ZFigure);
		break;
	}
}

void OnlineController::ready()
{
	writeSocket(Code::Ready);
}

void OnlineController::disconnectSocket()
{
	disconnect(socket, &QTcpSocket::disconnected, this, &OnlineController::onDisconnected);
	
	deleteServer();
	deleteSocket();
}

void OnlineController::defeat()
{
	writeSocket(Code::Defeat);
}

void OnlineController::readSocket()
{
	QByteArray bytes = socket->readAll();
	for (quint8 i = 0; i < bytes.size(); i++)
	{
		Code code = static_cast<Code>(bytes.at(i));
		switch (code)
		{
		case Code::IFigure:
			emit newFigureSignal(TetrisInfo::Figures::I);
			break;
		case Code::OFigure:
			emit newFigureSignal(TetrisInfo::Figures::O);
			break;
		case Code::TFigure:
			emit newFigureSignal(TetrisInfo::Figures::T);
			break;
		case Code::LFigure:
			emit newFigureSignal(TetrisInfo::Figures::L);
			break;
		case Code::JFigure:
			emit newFigureSignal(TetrisInfo::Figures::J);
			break;
		case Code::SFigure:
			emit newFigureSignal(TetrisInfo::Figures::S);
			break;
		case Code::ZFigure:
			emit newFigureSignal(TetrisInfo::Figures::Z);
			break;
		case Code::MoveRight:
			emit moveRightSignal();
			break;
		case Code::MoveLeft:
			emit moveLeftSignal();
			break;
		case Code::MoveDown:
			emit moveDownSignal();
			break;
		case Code::Rotate:
			emit rotateSignal();
			break;
		case Code::Ready:
			emit readySignal();
			break;
		case Code::Defeat:
			emit defeatSignal();
			break;
		}
	}
}

void OnlineController::connectedToServer()
{
	QTcpServer *server = qobject_cast<QTcpServer *>(sender());
	if (!connected)
	{
		connected = true;
		socket = server->nextPendingConnection();
		emit connectedSignal();
		start();
		connect(socket, &QTcpSocket::readyRead, this, &OnlineController::readSocket);
		connect(socket, &QTcpSocket::disconnected, this, &OnlineController::onDisconnected);
		connect(this, &OnlineController::deleteClientSignal, socket, &QTcpSocket::deleteLater);
	}
	else
	{
		server->nextPendingConnection()->close();
	}
}

void OnlineController::onDisconnected()
{
	emit disconnectSignal();
	disconnectSocket();
}

void OnlineController::clientConnected()
{
	emit connectedSignal();
	start();
	connect(socket, &QTcpSocket::readyRead, this, &OnlineController::readSocket);
	connect(socket, &QTcpSocket::disconnected, this, &OnlineController::onDisconnected);
}

void OnlineController::connectionTimeout()
{
	emit deleteClientSignal();
	emit cannotConnectSignal();
}

void OnlineController::writeSocket(const OnlineController::Code code)
{
	if (m_stop && code != Code::Ready && code != Code::Defeat)
	{
		return;
	}
	
	if (socket != nullptr)
	{
		QByteArray data;
		data.append(code);
		socket->write(data);
		socket->waitForBytesWritten();
		socket->flush();
	}
}
