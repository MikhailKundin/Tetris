#ifndef TIMERCONTROLLER_H
#define TIMERCONTROLLER_H

#include <QObject>
#include <QTimer>

class TimerController : public QObject
{
	Q_OBJECT
	
public:
	TimerController();
	
public slots:
	void tick();
	void newLevel(qint16 level);
	void stop();
	void restart();
	void deleteController();
	
signals:
	void tickSignal();
	
private:
	std::unique_ptr<QTimer> timer;
	
	const qint16 START_INTERVAL = 1000;
	const qreal INTERVAL_DIV = 2;
	const qint16 MIN_INTERVAL = 1;
};

#endif // TIMERCONTROLLER_H
