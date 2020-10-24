#include "generalcontroller.h"

#include <QRandomGenerator>
#include <QTime>
#include <QTimer>
#include <QtMath>

#include <QDebug>

GeneralController::GeneralController(qint8 row, qint8 column, QMap<qint8, QImage *> &blocks)
	: m_blocks(blocks), ROW_COUNT(row), COLUMN_COUNT(column)
{
	random.seed(static_cast<quint32>(QTime::currentTime().msecsSinceStartOfDay()));
	
	timer = std::make_unique<QTimer>();
	connect(timer.get(), &QTimer::timeout, this, &GeneralController::tick);
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
	delete figure;
	delete nextFigure;
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

QPair<qint8, qint8> GeneralController::getCoord(qint16 cell)
{
	qint8 x = cell % COLUMN_COUNT;
	qint8 y = static_cast<qint8>(cell / COLUMN_COUNT);
	
	return {x, y};
}

qint16 GeneralController::getCell(QPair<qint8, qint8> coord)
{
	qint16 x = coord.first;
	qint16 y = coord.second;
	
	return y*COLUMN_COUNT + x;
}

void GeneralController::getNextFigure()
{
	qint8 value = thirdFigure;
	thirdFigure = random.generate() % 7;
	emit newFigureSignal(thirdFigure);
	value = 0; // -------------------------------DEBUG-----------------------------------------------
	switch (value)
	{
	case Figures::I:
		nextFigure = new IFigure(ROW_COUNT, COLUMN_COUNT, m_blocks.value(Figures::I));
		break;
	case Figures::O:
		//nextFigure = new OFigure(ROW_COUNT, COLUMN_COUNT, m_blocks.value(Figures::O));
		break;
	case Figures::T:
		//nextFigure = new TFigure(ROW_COUNT, COLUMN_COUNT, m_blocks.value(Figures::T));
		break;
	case Figures::L:
		//nextFigure = new LFigure(ROW_COUNT, COLUMN_COUNT, m_blocks.value(Figures::L));
		break;
	case Figures::J:
		//nextFigure = new JFigure(ROW_COUNT, COLUMN_COUNT, m_blocks.value(Figures::J));
		break;
	case Figures::S:
		//nextFigure = new SFigure(ROW_COUNT, COLUMN_COUNT, m_blocks.value(Figures::S));
		break;
	case Figures::Z:
		//nextFigure = new ZFigure(ROW_COUNT, COLUMN_COUNT, m_blocks.value(Figures::Z));
		break;
	}
}

bool GeneralController::isRowFull(qint8 rowNumber)
{
	qint16 cell = getCell({0, rowNumber});
	for (qint8 i = 0; i < COLUMN_COUNT; i++, cell++)
	{
		if (!grid.contains(cell))
		{
			return false;
		}
	}
	return true;
}

void GeneralController::deleteRow(qint8 rowNumber)
{
	qint16 cell = getCell({0, rowNumber});
	QMap<qint16, QImage *>::iterator it = grid.find(cell);
	for (qint8 i = 0; i < COLUMN_COUNT; i++)
	{
		it = grid.erase(it);
	}
}

void GeneralController::shiftRows(qint8 bottomRow, qint8 count)
{
	QList<qint16> cells;
	qint16 cell = getCell({COLUMN_COUNT-1, bottomRow});
	QMap<qint16, QImage *>::iterator it = grid.end();
	while (it != grid.begin())
	{
		it--;
		qint16 key = it.key();
		if (key <= cell)
		{
			cells.append(key);
		}
	}
	foreach (cell, cells)
	{
		grid.insert(cell + COLUMN_COUNT*count, grid.value(cell));
		grid.remove(cell);
	}
}

bool GeneralController::isObstacle(QList<qint16> cells)
{
	foreach (qint16 cell, cells)
	{
		bool res = true;
		qint16 downCoord = cell + COLUMN_COUNT;
		if (grid.contains(downCoord))
		{
			foreach(qint16 secondCoord, cells)
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

bool GeneralController::isLayerOverflow(QList<qint16> cells)
{
	foreach (qint16 cell, cells)
	{
		if (grid.contains(cell))
		{
			return true;
		}
	}
	return false;
}

void GeneralController::addFigure(QList<qint16> cells)
{
	if (isLayerOverflow(cells))
	{
		timer->stop();
		emit defeatSignal(this);
		return;
	}
	foreach (qint16 cell, cells)
	{
		grid.insert(cell, figure->getImage());
	}
}

void GeneralController::deleteFigure(QList<qint16> cells)
{
	foreach (qint16 cell, cells)
	{
		grid.remove(cell);
	}
}

void GeneralController::checkRows(QList<qint16> cells)
{
	qint8 rowCount = 0;
	qint8 topRow = ROW_COUNT;
	foreach (qint16 cell, cells)
	{
		QPair<qint8, qint8> pairCoord = getCoord(cell);
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
		shiftRows(topRow, rowCount);
		addPoints(POINTS[rowCount-1]);
	}
}

void GeneralController::addPoints(qint32 count)
{
	m_points += count;
	emit newPointsSignal(m_points);
	
	qint16 newLevel = static_cast<qint16>(m_points / NEW_LEVEL) + 1;
	if (level != newLevel)
	{
		level = newLevel;
		setTimerInterval();
		emit newLevelSignal(level);
	}
}

void GeneralController::setTimerInterval()
{
	qint32 interval = static_cast<qint32>(START_INTERVAL / qPow(INTERVAL_DIV, level-1));
	if (interval < MIN_INTERVAL)
	{
		interval = MIN_INTERVAL;
	}
	timer->setInterval(interval);
}

bool GeneralController::isNegativeCoords(QList<qint16> cells)
{
	foreach (qint16 cell, cells)
	{
		if (cell < 0)
		{
			return true;
		}
	}
	return false;
}
