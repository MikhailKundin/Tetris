#ifndef ONLINECONTROLLER_H
#define ONLINECONTROLLER_H

#include <QObject>
#include <QTcpSocket>

class OnlineController : public QObject
{
	Q_OBJECT
	
public:
	OnlineController();
	void makeServer();
	void makeClient(const QString &ip);
	
signals:
	void moveRightSignal();
	void moveLeftSignal();
	void moveDownSignal();
	void rotateSignal();
	void newFigureSignal(quint8 figure);
	
	void connectedSignal();
	void startSignal();
	void disconnectSignal();
	void readySignal();
	
public slots:
	void moveRight();
	void moveLeft();
	void moveDown();
	void rotate();
	void newFigure(quint8 figure);
	
private slots:
	void readSocket();
	void onConnected();
	void onDisconnected();
	
private:
	enum Code : quint8
	{
		IFigure, TFigure, OFigure, LFigure, JFigure, SFigure, ZFigure, 
		MoveRight, MoveLeft, MoveDown, Rotate, Ready
	};
	
	void writeSocket(const Code code);
	
	bool connected = false;
	std::unique_ptr<QTcpSocket> socket;
	
	const quint16 PORT = 28128;
};

#endif // ONLINECONTROLLER_H
