#ifndef ONLINECONTROLLER_H
#define ONLINECONTROLLER_H

#include <QObject>

class OnlineController : public QObject
{
	Q_OBJECT
	
public:
	OnlineController();
	
signals:
	void moveRightSignal();
	void moveLeftSignal();
	void moveDownSignal();
	void RotateSignal();
	void newFigureSignal();
};

#endif // ONLINECONTROLLER_H
