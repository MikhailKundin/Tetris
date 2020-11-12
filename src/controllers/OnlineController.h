#ifndef ONLINECONTROLLER_H
#define ONLINECONTROLLER_H

#include <QObject>
#include <QTcpSocket>

class OnlineController : public QObject
{
	Q_OBJECT
	
public:
	OnlineController();
	~OnlineController();
	
signals:
	void moveRightSignal();
	void moveLeftSignal();
	void moveDownSignal();
	void rotateSignal();
	void newFigureSignal(quint8 figure);
	void readySignal();
	
	void connectedSignal();
	void startSignal();
	void disconnectSignal();
	void cannotConnectSignal();
	
	void deleteServerSignal();
	void deleteClientSignal();
	void deleteTimer();
	
public slots:
	void moveRight();
	void moveLeft();
	void moveDown();
	void rotate();
	void newFigure(quint8 figure);
	void ready();
	void disconnectSocket();
	
	void makeServer();
	void makeClient(const QString &ip);
	void deleteServer();
	void deleteSocket();
	
private slots:
	void readSocket();
	void connectedToServer();
	void onDisconnected();
	void clientConnected();
	void connectionTimeout();
	
private:
	enum Code : qint8
	{
		IFigure, TFigure, OFigure, LFigure, JFigure, SFigure, ZFigure, 
		MoveRight, MoveLeft, MoveDown, Rotate, Ready
	};
	
	void writeSocket(const Code code);
	
	QTcpSocket *socket = nullptr;
	
	const quint16 PORT = 28128;
};

#endif // ONLINECONTROLLER_H
