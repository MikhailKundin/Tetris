#include "timercontroller.h"

#include <QtMath>

#include <QDebug>

TimerController::TimerController()
{
	timer = std::make_unique<QTimer>();
	connect(timer.get(), &QTimer::timeout, this, &TimerController::tick);
	timer->setInterval(START_INTERVAL);
	timer->start();
}

void TimerController::tick()
{
	qDebug() << timer->interval();
	emit tickSignal();
}

void TimerController::newLevel(qint16 level)
{
	qint32 interval = static_cast<qint32>(START_INTERVAL / qPow(INTERVAL_DIV, level-1));
	if (interval < MIN_INTERVAL)
	{
		interval = MIN_INTERVAL;
	}
	timer->setInterval(interval);
	timer->start();
}

void TimerController::stop()
{
	timer->stop();
}

void TimerController::restart()
{
	timer->setInterval(START_INTERVAL);
	timer->start();
}

void TimerController::deleteController()
{
	delete this;
}
