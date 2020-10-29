#include "OfflineController.h"

#include <QtMath>
#include <QTime>

#include <QDebug>

OfflineController::OfflineController()
{
	timer = std::make_unique<QTimer>();
	connect(timer.get(), &QTimer::timeout, this, &OfflineController::tick);
	random.seed(static_cast<quint32>(QTime::currentTime().msecsSinceStartOfDay()));
}

void OfflineController::tick()
{
	timer->start();
	emit tickSignal();
}

void OfflineController::newLevel(qint16 level)
{
	qint32 interval = static_cast<qint32>(START_INTERVAL / qPow(INTERVAL_DIV, level-1));
	if (interval < MIN_INTERVAL)
	{
		interval = MIN_INTERVAL;
	}
	timer->setInterval(interval);
	timer->start();
}

void OfflineController::stop()
{
	timer->stop();
}

void OfflineController::restart()
{
	timer->setInterval(START_INTERVAL);
	timer->start();
}

void OfflineController::deleteController()
{
	delete this;
}

void OfflineController::getNewFigure()
{
	qint8 figure = random.generate() % 7;
	emit newFigureSignal(figure);
}

void OfflineController::pause()
{
	timer->setInterval(timer->remainingTime());
	timer->stop();
}

void OfflineController::resume()
{
	timer->start();
}
