#include "generalcontroller.h"

#include "../tetrisinfo.h"

#include <QRandomGenerator>
#include <QTime>
#include <QtMath>

#include <QDebug>

GeneralController::GeneralController(QMap<qint8, QImage *> &blocks)
	: m_blocks(blocks)
{
	random.seed(static_cast<quint32>(QTime::currentTime().msecsSinceStartOfDay()));
	
	restart();
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
	if (m_stop)
	{
		return;
	}
	
	QList<qint16> oldCells = figure->getCells();
	QList<qint16> newCells = oldCells;
	if (figure->moveRight())
	{
		deleteFigure(oldCells);
		QList<qint16> cells = figure->getCells();
		if (!isLayerOverflow(cells))
		{
			newCells = cells;
			addFigure(newCells);
			emit moveRightSignal();
			emit update(grid);
		}
		else
		{
			addFigure(newCells);
			figure->moveLeft();
		}
	}
}

void GeneralController::moveLeft()
{
	if (m_stop)
	{
		return;
	}
	
	QList<qint16> oldCells = figure->getCells();
	QList<qint16> newCells = oldCells;
	if (figure->moveLeft())
	{
		deleteFigure(oldCells);
		QList<qint16> cells = figure->getCells();
		if (!isLayerOverflow(cells))
		{
			newCells = cells;
			addFigure(newCells);
			emit moveLeftSignal();
			emit update(grid);
		}
		else
		{
			addFigure(newCells);
			figure->moveRight();
		}
	}
}

void GeneralController::rotate()
{
	if (m_stop)
	{
		return;
	}
	
	QList<qint16> oldCells = figure->getCells();
	QList<qint16> newCells = oldCells;
	if (figure->rotate())
	{
		deleteFigure(oldCells);
		QList<qint16> cells = figure->getCells();
		if (!isLayerOverflow(cells))
		{
			newCells = cells;
			addFigure(newCells);
			emit rotateSignal();
			emit update(grid);
		}
		else
		{
			addFigure(newCells);
			figure->backRotate();
		}
	}
}

void GeneralController::moveDown()
{
	if (m_stop)
	{
		return;
	}
	
	QList<qint16> oldCells = figure->getCells();
	QList<qint16> newCells = oldCells;
	if (figure->moveDown())
	{
		deleteFigure(oldCells);
		QList<qint16> cells = figure->getCells();
		if (!isLayerOverflow(cells))
		{
			newCells = cells;
			addFigure(newCells);//---------------------?????-----------------------
			emit moveDownSignal();
			emit update(grid);
		}
		else
		{
			addFigure(newCells);
			figure->moveUp();
		}
	}
	else
	{
		figureFall();
	}
}

void GeneralController::newTick()
{
	if (m_stop)
	{
		return;
	}
	
	QList<qint16> cells = figure->getCells();
	if (!isObstacle(cells))
	{
		moveDown();
	}
	else if (isNegativeCoords(cells))
	{
		emit defeatSignal();
	}
	else
	{
		figureFall();
	}
}

void GeneralController::restart()
{
	m_stop = false;
	getNextFigure();
	figure = nextFigure;
	getNextFigure();
	addFigure(figure->getCells());
	emit update(grid);
	m_points = 0;
	emit newPointsSignal(m_points);
	level = 1;
	emit newLevelSignal(level);
}

void GeneralController::stop()
{
	m_stop = true;
}

void GeneralController::deleteController()
{
	delete this;
}

void GeneralController::figureFall()
{
	QList<qint16> cells = figure->getCells();
	
	qint8 topRow = 0;
	qint8 rowCount = 0;
	checkRows(cells, topRow, rowCount);
	if (rowCount > 0)
	{
		{
			shiftRows(topRow, rowCount);
			addPoints(POINTS[rowCount-1]);
		}
	}
	
	figure = nextFigure;
	getNextFigure();
	emit newFigureSignal(thirdFigure);
	newTick();
}

void GeneralController::getNextFigure()
{
	qint8 value = thirdFigure;
	thirdFigure = random.generate() % 7;
	value = 0; // -------------------------------DEBUG-----------------------------------------------
	switch (value)
	{
	case TetrisInfo::Figures::I:
		nextFigure = new IFigure(m_blocks.value(TetrisInfo::Figures::I));
		break;
	case TetrisInfo::Figures::O:
		//nextFigure = new OFigure(m_blocks.value(Figures::O));
		break;
	case TetrisInfo::Figures::T:
		//nextFigure = new TFigure(m_blocks.value(Figures::T));
		break;
	case TetrisInfo::Figures::L:
		//nextFigure = new LFigure(m_blocks.value(Figures::L));
		break;
	case TetrisInfo::Figures::J:
		//nextFigure = new JFigure(m_blocks.value(Figures::J));
		break;
	case TetrisInfo::Figures::S:
		//nextFigure = new SFigure(m_blocks.value(Figures::S));
		break;
	case TetrisInfo::Figures::Z:
		//nextFigure = new ZFigure(m_blocks.value(Figures::Z));
		break;
	}
}

bool GeneralController::isRowFull(qint8 rowNumber)
{
	qint16 cell = TetrisInfo::getCell({0, rowNumber});
	for (qint8 i = 0; i < TetrisInfo::COLUMN_COUNT; i++, cell++)
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
	qint16 cell = TetrisInfo::getCell({0, rowNumber});
	QMap<qint16, QImage *>::iterator it = grid.find(cell);
	for (qint8 i = 0; i < TetrisInfo::COLUMN_COUNT; i++)
	{
		it = grid.erase(it);
	}
}

void GeneralController::shiftRows(qint8 bottomRow, qint8 count)
{
	QList<qint16> cells;
	qint16 cell = TetrisInfo::getCell({TetrisInfo::COLUMN_COUNT-1, bottomRow});
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
		grid.insert(cell + TetrisInfo::COLUMN_COUNT*count, grid.value(cell));
		grid.remove(cell);
	}
}

bool GeneralController::isObstacle(QList<qint16> cells)
{
	foreach (qint16 cell, cells)
	{
		bool res = true;
		qint16 downCoord = cell + TetrisInfo::COLUMN_COUNT;
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
	if (isLayerOverflow(cells))//-----------------------------?????--------------------------
	{
		emit defeatSignal();
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

void GeneralController::checkRows(QList<qint16> cells, qint8 &topRow_out, qint8 &rowCount_out)
{
	rowCount_out = 0;
	topRow_out = TetrisInfo::ROW_COUNT;
	foreach (qint16 cell, cells)
	{
		QPair<qint8, qint8> pairCoord = TetrisInfo::getCoord(cell);
		if (isRowFull(pairCoord.second))
		{
			if (pairCoord.second < topRow_out)
			{
				topRow_out = pairCoord.second;
			}
			deleteRow(pairCoord.second);
			rowCount_out++;
		}
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
		emit newLevelSignal(level);
	}
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
