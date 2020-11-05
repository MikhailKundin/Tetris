#ifndef TIMERCONTROLLER_H
#define TIMERCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QRandomGenerator>

class OfflineController : public QObject
{
	Q_OBJECT
	
public:
	OfflineController();
	
public slots:
	void tick();
	void newLevel(qint16 level);
	void stop();
	void restart();
	void deleteController();
	void getNewFigure();
	void pause();
	void resume();
	
signals:
	void tickSignal();
	void newFigureSignal(quint8 figure);
	
private:
	std::unique_ptr<QTimer> timer;
	
	const quint16 START_INTERVAL = 1000;
	const qreal INTERVAL_DIV = 2;
	const quint16 MIN_INTERVAL = 1;
	
	quint16 resumeInterval = 0;
	quint16 currentInterval = START_INTERVAL;
	
	QRandomGenerator random;
};

#endif // TIMERCONTROLLER_H
