#include "OnlineController.h"

#include <QTcpServer>

#include "../TetrisInfo.h"

#include <QDebug>

OnlineController::OnlineController()
{
	
}

void OnlineController::makeServer()
{
	QTcpServer *server = new QTcpServer(this);
	server->listen(QHostAddress::Any, PORT);
	connect(server, &QTcpServer::newConnection, this, &OnlineController::onConnected);
	connect(server, &QTcpServer::newConnection, server, &QTcpServer::deleteLater); //--------?????-----------
}

void OnlineController::makeClient(const QString &ip)
{
	socket = std::make_unique<QTcpSocket>(new QTcpSocket(this));
	socket->connectToHost(ip, PORT);
	if (!socket->waitForConnected(3000))
	{
		socket->deleteLater();
		emit disconnectSignal();
	}
	else
	{
		connect(socket.get(), &QTcpSocket::readyRead, this, &OnlineController::readSocket);
		connect(socket.get(), &QTcpSocket::disconnected, this, &OnlineController::onDisconnected);
	}
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

void OnlineController::readSocket()
{
	Code code = static_cast<Code>(socket->readAll().toUInt());
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
	}
}

void OnlineController::onConnected()
{
	QTcpServer *server = qobject_cast<QTcpServer *>(sender());
	disconnect(server, &QTcpServer::newConnection, this, &OnlineController::onConnected);
	connected = true;
	socket = std::make_unique<QTcpSocket>(server->nextPendingConnection());
	connect(socket.get(), &QTcpSocket::readyRead, this, &OnlineController::readSocket);
	connect(socket.get(), &QTcpSocket::disconnected, this, &OnlineController::onDisconnected);
	qDebug() << 1;
}

void OnlineController::onDisconnected()
{
	emit disconnectSignal();
	sender()->deleteLater();
}

void OnlineController::writeSocket(const OnlineController::Code code)
{
	socket->write(QByteArray::number(code));
	socket->flush();
}
