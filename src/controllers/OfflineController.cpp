#include "OfflineController.h"

#include <QtMath>
#include <QTime>

#include <QDebug>

OfflineController::OfflineController()
{
	timer = std::make_unique<QTimer>(this);
	connect(timer.get(), &QTimer::timeout, this, &OfflineController::tick);
	random.seed(static_cast<quint32>(QTime::currentTime().msecsSinceStartOfDay()));
}

void OfflineController::tick()
{
	timer->setInterval(currentInterval);
	emit tickSignal();
}

void OfflineController::newLevel(quint16 level)
{
	quint16 interval = static_cast<quint16>(START_INTERVAL / qPow(INTERVAL_DIV, level-1));
	if (interval < MIN_INTERVAL)
	{
		interval = MIN_INTERVAL;
	}
	currentInterval = interval;
	timer->setInterval(currentInterval);
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

void OfflineController::getNewFigure()
{
	quint8 figure = random.generate() % 7;
	emit newFigureSignal(figure);
}

void OfflineController::pause()
{
	resumeInterval = static_cast<quint16>(timer->remainingTime());
	timer->setInterval(resumeInterval);
	timer->stop();
}

void OfflineController::resume()
{
	timer->start();
}
