#include "OfflineController.h"

#include <QtMath>
#include <QTime>
#include <QTimer>

OfflineController::OfflineController()
{
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &OfflineController::tick);
	random.seed(static_cast<quint32>(QTime::currentTime().msecsSinceStartOfDay()));
	updatePool();
}

OfflineController::~OfflineController()
{
	timer->deleteLater();
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
	updatePool();
}

void OfflineController::restart()
{
	currentInterval = START_INTERVAL;
	timer->setInterval(currentInterval);
	timer->start();
}

void OfflineController::getNewFigure()
{
	quint8 figure = pool.takeAt(random.generate() % 35);
	emit newFigureSignal(figure);
	
	qint16 maxVal = 0;
	quint8 count = 0;
	for (quint8 i = 0; i < 7; i++)
	{
		if (i == figure)
		{
			figureStat[i] = 0;
			continue;
		}
		
		figureStat[i]++;
		qint16 val = figureStat.at(i);
		if (val > maxVal)
		{
			maxVal = val;
			count = 1;
		}
		else if (val == maxVal)
		{
			count++;
		}
	}
	
	if (count == 1)
	{
		pool.append(static_cast<quint8>(figureStat.indexOf(maxVal)));
	}
	else
	{
		quint8 newFigureIndex = random.generate() % count;
		for (quint8 i = 0; i < 7; i++)
		{
			if (figureStat.at(i) == maxVal)
			{
				if (newFigureIndex == 0)
				{
					pool.append(i);
					break;
				}
				else
				{
					newFigureIndex--;
				}
			}
		}
	}
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

void OfflineController::updatePool()
{
	pool.clear();
	pool.reserve(35);
	figureStat.clear();
	figureStat.reserve(7);
	for (quint8 i = 0; i < 5; i++)
	{
		for (quint8 j = 0; j < 7; j++)
		{
			pool.append(j);
		}
	}
	for (qint16 i = 0; i < 7; i++)
	{
		figureStat.append(0);
	}
}
