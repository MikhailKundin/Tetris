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
	addFigure(figure->getCoords());
	emit update(grid);
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

QMap<qint16, QImage *> &GeneralController::getGrid()
{
	return grid;
}

void GeneralController::moveRight()
{
	QList<qint16> oldCoords = figure->getCoords();
	QList<qint16> newCoords = oldCoords;
	if (figure->moveRight())
	{
		deleteFigure(oldCoords);
		QList<qint16> coords = figure->getCoords();
		if (!isLayerOverflow(coords))
		{
			newCoords = coords;
			addFigure(newCoords);
			emit moveRightSignal();
			emit update(grid);
		}
		else
		{
			addFigure(newCoords);
			figure->moveLeft();
		}
	}
}

void GeneralController::moveLeft()
{
	QList<qint16> oldCoords = figure->getCoords();
	QList<qint16> newCoords = oldCoords;
	if (figure->moveLeft())
	{
		deleteFigure(oldCoords);
		QList<qint16> coords = figure->getCoords();
		if (!isLayerOverflow(coords))
		{
			newCoords = coords;
			addFigure(newCoords);
			emit moveLeftSignal();
			emit update(grid);
		}
		else
		{
			addFigure(newCoords);
			figure->moveRight();
		}
	}
}

void GeneralController::rotate()
{
	QList<qint16> oldCoords = figure->getCoords();
	QList<qint16> newCoords = oldCoords;
	if (figure->rotate())
	{
		deleteFigure(oldCoords);
		QList<qint16> coords = figure->getCoords();
		if (!isLayerOverflow(coords))
		{
			newCoords = coords;
			addFigure(newCoords);
			emit rotateSignal();
			emit update(grid);
		}
		else
		{
			addFigure(newCoords);
			figure->backRotate();
		}
	}
}

void GeneralController::moveDown()
{
	QList<qint16> oldCoords = figure->getCoords();
	QList<qint16> newCoords = oldCoords;
	if (figure->moveDown())
	{
		deleteFigure(oldCoords);
		QList<qint16> coords = figure->getCoords();
		if (!isLayerOverflow(coords))
		{
			newCoords = coords;
			addFigure(newCoords);
			emit moveDownSignal();
			emit update(grid);
		}
		else
		{
			addFigure(newCoords);
			figure->moveUp();
		}
	}
	else
	{
		checkRows(oldCoords);
		figure = nextFigure;
		getNextFigure();
		emit tickSignal();
		emit update(grid);
		tick();
	}
}

void GeneralController::tick()
{
	QList<qint16> coords = figure->getCoords();
	if (!isObstacle(coords))
	{
		moveDown();
		emit tickSignal();
		return;
	}
	else if (isNegativeCoords(coords))
	{
		timer->stop();
		emit defeatSignal(this);
		return;
	}
	else
	{
		checkRows(coords);
		figure = nextFigure;
		getNextFigure();
		emit tickSignal();
		emit update(grid);
		tick();
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
		//nextFigure = new OFigure(ROW_COUNT, COLUMN_COUNT, OBlock);
		break;
	case 2:
		//nextFigure = new TFigure(ROW_COUNT, COLUMN_COUNT, TBlock);
		break;
	case 3:
		//nextFigure = new LFigure(ROW_COUNT, COLUMN_COUNT, LBlock);
		break;
	case 4:
		//nextFigure = new JFigure(ROW_COUNT, COLUMN_COUNT, JBlock);
		break;
	case 5:
		//nextFigure = new SFigure(ROW_COUNT, COLUMN_COUNT, SBlock);
		break;
	case 6:
		//nextFigure = new ZFigure(ROW_COUNT, COLUMN_COUNT, ZBlock);
		break;
	}
}

bool GeneralController::isRowFull(qint8 y)
{
	qint16 coord = getSingleCoord({0, y});
	for (qint8 i = 0; i < COLUMN_COUNT; i++, coord++)
	{
		if (!grid.contains(coord))
		{
			return false;
		}
	}
	return true;
}

void GeneralController::deleteRow(qint8 y)
{
	qint16 coord = getSingleCoord({0, y});
	QMap<qint16, QImage *>::iterator it = grid.find(coord);
	for (qint8 i = 0; i < COLUMN_COUNT; i++)
	{
		it = grid.erase(it);
	}
}

void GeneralController::shiftRows(qint8 firstRow, qint8 count)
{
	QList<qint16> coordList;
	qint16 coord = getSingleCoord({COLUMN_COUNT-1, firstRow});
	QMap<qint16, QImage *>::iterator it = grid.end();
	while (it != grid.begin())
	{
		it--;
		qint16 key = it.key();
		if (key <= coord)
		{
			coordList.append(key);
		}
	}
	foreach (coord, coordList)
	{
		grid.insert(coord + COLUMN_COUNT*count, grid.value(coord));
		grid.remove(coord);
	}
}

bool GeneralController::isObstacle(QList<qint16> coords)
{
	foreach (qint16 coord, coords)
	{
		bool res = true;
		qint16 downCoord = coord + COLUMN_COUNT;
		if (grid.contains(downCoord))
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

bool GeneralController::isLayerOverflow(QList<qint16> coords)
{
	foreach (qint16 coord, coords)
	{
		if (grid.contains(coord))
		{
			return true;
		}
	}
	return false;
}

void GeneralController::addFigure(QList<qint16> coords)
{
	if (isLayerOverflow(coords))
	{
		timer->stop();
		emit defeatSignal(this);
		return;
	}
	foreach (qint16 coord, coords)
	{
		grid.insert(coord, figure->getImage());
	}
}

void GeneralController::deleteFigure(QList<qint16> coords)
{
	foreach (qint16 coord, coords)
	{
		grid.remove(coord);
	}
}

void GeneralController::checkRows(QList<qint16> coords)
{
	qint8 rowCount = 0;
	qint8 topRow = ROW_COUNT;
	foreach (qint16 coord, coords)
	{
		QPair<qint8, qint8> pairCoord = getPairCoord(coord);
		if (isRowFull(pairCoord.second))
		{
			if (pairCoord.second < topRow)
			{
				topRow = pairCoord.second;
			}
			deleteRow(pairCoord.second);
			rowCount++;
		}
	}
	if (rowCount != 0)
	{
		shiftRows(topRow+1, rowCount);
		addPoints(POINTS[rowCount-1]);
	}
}

void GeneralController::addPoints(qint32 count)
{
	m_points += count;
	emit newPointsSignal(m_points);
	
	qint32 newLevel = static_cast<qint16>(m_points / NEW_LEVEL);
	if (level != newLevel)
	{
		setTimerInterval();
		emit newLevelSignal(level);
	}
}

void GeneralController::setTimerInterval()
{
	qint32 interval = static_cast<qint32>(START_INTERVAL / qPow(INTERVAL_DIV, level));
	if (interval < MIN_INTERVAL)
	{
		interval = MIN_INTERVAL;
	}
	timer->setInterval(interval);
}

bool GeneralController::isNegativeCoords(QList<qint16> coords)
{
	foreach (qint16 coord, coords)
	{
		if (coord < 0)
		{
			return true;
		}
	}
	return false;
}
