#include "generalcontroller.h"

#include <QRandomGenerator>
#include <QTime>
#include <QTimer>
#include <QtMath>

#include <QDebug>

GeneralController::GeneralController(qint8 row, qint8 column) : ROW_COUNT(row), COLUMN_COUNT(column)
{
	IBlock = new QImage(":Images/Blocks/IBlockOriginal.png");
	OBlock = new QImage(":Images/Blocks/OBlockOriginal.png");
	TBlock = new QImage(":Images/Blocks/TBlockOriginal.png");
	LBlock = new QImage(":Images/Blocks/LBlockOriginal.png");
	JBlock = new QImage(":Images/Blocks/JBlockOriginal.png");
	SBlock = new QImage(":Images/Blocks/SBlockOriginal.png");
	ZBlock = new QImage(":Images/Blocks/ZBlockOriginal.png");
	
	random.seed(static_cast<quint32>(QTime::currentTime().msecsSinceStartOfDay()));
	
	timer = new QTimer;
	connect(timer, &QTimer::timeout, this, &GeneralController::tick);
	timer->setInterval(START_INTERVAL);
	getNextFigure();
	figure = nextFigure;
	getNextFigure();
	setGrid(figure->getCoords());
	emit update(map);
	timer->start();
}

GeneralController::~GeneralController()
{
	delete IBlock;
	delete OBlock;
	delete TBlock;
	delete LBlock;
	delete JBlock;
	delete SBlock;
	delete ZBlock;
}

void GeneralController::setPoints(qint32 points)
{
	m_points = points;
}

qint32 GeneralController::getPoints()
{
	return m_points;
}

QMap<qint16, QImage *> &GeneralController::getMap()
{
	return map;
}

void GeneralController::moveRight()
{
	QList<qint16> oldCoords = figure->getCoords();
	if (figure->moveRight())
	{
		QList<qint16> coords = figure->getCoords();
		if (checkLayer(coords))
		{
			deleteFigure(oldCoords);
			setGrid(coords);
			emit moveRightSignal();
			emit update(map);
		}
		else
		{
			figure->moveLeft();
		}
	}
}

void GeneralController::moveLeft()
{
	QList<qint16> oldCoords = figure->getCoords();
	if (figure->moveLeft())
	{
		QList<qint16> coords = figure->getCoords();
		if (checkLayer(coords))
		{
			deleteFigure(oldCoords);
			setGrid(coords);
			emit moveLeftSignal();
			emit update(map);
		}
		else
		{
			figure->moveRight();
		}
	}
}

void GeneralController::rotate()
{
	QList<qint16> oldCoords = figure->getCoords();
	if (figure->rotate())
	{
		QList<qint16> coords = figure->getCoords();
		if (checkLayer(coords))
		{
			deleteFigure(oldCoords);
			setGrid(coords);
			emit rotateSignal();
			emit update(map);
		}
		else
		{
			figure->backRotate();
		}
	}
}

void GeneralController::moveDown()
{
	QList<qint16> oldCoords = figure->getCoords();
	if (figure->moveDown())
	{
		QList<qint16> coords = figure->getCoords();
		if (checkLayer(coords))
		{
			deleteFigure(oldCoords);
			setGrid(coords);
			emit moveDownSignal();
			emit update(map);
		}
		else
		{
			figure->moveUp();
		}
	}
	else
	{
		spawnNextFigure(oldCoords);
	}
}

void GeneralController::tick()
{
	qDebug() << map;
	QList<qint16> coords = figure->getCoords();
	if (!checkPosition(coords))
	{
		timer->start();
		moveDown();
		emit tickSignal();
		return;
	}
	else if (!checkLayer(coords))
	{
		timer->stop();
		emit defeatSignal(this);
		return;
	}
	else
	{
		spawnNextFigure(coords);
	}
}

QPair<qint8, qint8> GeneralController::getPairCoord(qint16 singleCoord)
{
	qint8 x = singleCoord % COLUMN_COUNT;
	qint8 y = static_cast<qint8>(singleCoord / COLUMN_COUNT);
	
	return {x, y};
}

qint16 GeneralController::getSingleCoord(QPair<qint8, qint8> pairCoord)
{
	qint16 x = pairCoord.first;
	qint16 y = pairCoord.second;
	
	return y*COLUMN_COUNT + x;
}

void GeneralController::getNextFigure()
{
	qint8 value = random.generate() % 7;
	value = 0; //-------------------------------DEBUG-----------------------------------------------
	switch (value)
	{
	case 0:
		nextFigure = new IFigure(ROW_COUNT, COLUMN_COUNT, IBlock);
		break;
	case 1:
		nextFigure = new OFigure(ROW_COUNT, COLUMN_COUNT, OBlock);
		break;
	case 2:
		nextFigure = new TFigure(ROW_COUNT, COLUMN_COUNT, TBlock);
		break;
	case 3:
		nextFigure = new LFigure(ROW_COUNT, COLUMN_COUNT, LBlock);
		break;
	case 4:
		nextFigure = new JFigure(ROW_COUNT, COLUMN_COUNT, JBlock);
		break;
	case 5:
		nextFigure = new SFigure(ROW_COUNT, COLUMN_COUNT, SBlock);
		break;
	case 6:
		nextFigure = new ZFigure(ROW_COUNT, COLUMN_COUNT, ZBlock);
		break;
	}
}

bool GeneralController::checkRow(qint8 y)
{
	for (qint8 x = 0; x < COLUMN_COUNT; x++)
	{
		qint16 coord = getSingleCoord({x, y});
		if (!map.contains(coord))
		{
			return false;
		}
	}
	return true;
}

void GeneralController::deleteRow(qint8 y)
{
	for (qint8 x = 0; x < COLUMN_COUNT; x++)
	{
		qint16 coord = getSingleCoord({x, y});
		map.remove(coord);
	}
	
	y--;
	while (y >= 0)
	{
		for (qint8 x = 0; x < COLUMN_COUNT; x++)
		{
			qint16 oldCoord = getSingleCoord({x, y});
			qint16 newCoord = getSingleCoord({x, y+1});
			QMap<qint16, QImage *>::iterator it = map.find(oldCoord);
			map.insert(newCoord, it.value());
			map.remove(oldCoord);
		}
	}
}

bool GeneralController::checkPosition(QList<qint16> coords)
{
	foreach (qint16 coord, coords)
	{
		bool res = true;
		qint16 downCoord = coord + COLUMN_COUNT;
		if (map.contains(downCoord))
		{
			foreach(qint16 secondCoord, coords)
			{
				if (downCoord == secondCoord)
				{
					res = false;
					break;
				}
			}
			if (res)
			{
				return true;
			}
		}
	}
	return false;
}

bool GeneralController::checkLayer(QList<qint16> coords)
{
	foreach (qint16 coord, coords)
	{
		if (map.contains(coord))
		{
			return false;
		}
	}
	return true;
}

void GeneralController::setGrid(QList<qint16> coords)
{
	foreach (qint16 coord, coords)
	{
		map.insert(coord, figure->getImage());
	}
}

void GeneralController::deleteFigure(QList<qint16> coords)
{
	foreach (qint16 coord, coords)
	{
		map.remove(coord);
	}
}

void GeneralController::spawnNextFigure(QList<qint16> coords)
{
	qint16 shift = 0;
	foreach (qint16 coord, coords)
	{
		QPair<qint8, qint8> pairCoord = getPairCoord(coord+shift);
		if (checkRow(pairCoord.second))
		{
			deleteRow(pairCoord.second);
			shift += COLUMN_COUNT;
		}
	}
	m_points += POINTS[shift / COLUMN_COUNT];
	level = static_cast<qint16>(m_points / NEW_LEVEL);
	qint32 interval = static_cast<qint32>(START_INTERVAL / qPow(INTERVAL_DIV, level));
	if (interval < MIN_INTERVAL)
	{
		interval = MIN_INTERVAL;
	}
	timer->setInterval(interval);
	timer->start();
	
	figure = nextFigure;
	getNextFigure();
	emit tickSignal();
	emit update(map);
	//tick();
}
