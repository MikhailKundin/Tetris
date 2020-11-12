#include "GeneralController.h"

#include "../TetrisInfo.h"

#include <QtMath>

#include <QDebug>

GeneralController::GeneralController(QMap<qint8, QImage *> &blocks)
	: m_blocks(blocks)
{	
	
}

GeneralController::~GeneralController()
{
	delete figure;
	delete secondFigure;
}

void GeneralController::setPoints(quint32 points)
{
	m_points = points;
}

quint32 GeneralController::getPoints() const
{
	return m_points;
}

const QMap<qint16, QImage *> &GeneralController::getGrid() const
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
	if (figure->moveRight())
	{
		deleteFigure(oldCells);
		QList<qint16> newCells = figure->getCells();
		if (!isLayerOverflow(newCells))
		{
			addFigure(newCells);
			emit moveRightSignal();
			emit update(grid);
		}
		else
		{
			figure->moveLeft();
			addFigure(oldCells);
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
	if (figure->moveLeft())
	{
		deleteFigure(oldCells);
		QList<qint16> newCells = figure->getCells();
		if (!isLayerOverflow(newCells))
		{
			addFigure(newCells);
			emit moveLeftSignal();
			emit update(grid);
		}
		else
		{
			figure->moveRight();
			addFigure(oldCells);
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
	if (figure->rotate())
	{
		deleteFigure(oldCells);
		QList<qint16> newCells = figure->getCells();
		if (!isLayerOverflow(newCells))
		{
			addFigure(newCells);
			emit rotateSignal();
			emit update(grid);
		}
		else
		{
			figure->backRotate();
			addFigure(oldCells);
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
	if (figure->moveDown())
	{
		deleteFigure(oldCells);
		QList<qint16> newCells = figure->getCells();
		if (!isLayerOverflow(newCells))
		{
			addFigure(newCells);
			emit moveDownSignal();
			emit update(grid);
		}
		else
		{
			figure->moveUp();
			addFigure(oldCells);
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
		//qDebug() << "Defeat:" << grid << figure->getCells();
	}
	else
	{
		figureFall();
	}
}

void GeneralController::restart()
{
	//if (objectName() != "Online") qDebug() << 1;
	isReadyToStart = false;
	grid.clear();
	m_stop = false;
	if (figure != nullptr && objectName() != "Online")
	{
		delete figure;
		figure = nullptr;
	}
	if (secondFigure != nullptr && objectName() != "Online")
	{
		delete secondFigure;
		secondFigure = nullptr;
	}
	emit getNewFigureSignal();
	emit getNewFigureSignal();
}

void GeneralController::stop()
{
	m_stop = true;
}

void GeneralController::start()
{
	m_stop = false;
}

void GeneralController::clearFigure()
{
	if (figure != nullptr)
	{
		delete figure;
		figure = nullptr;
	}
	if (secondFigure != nullptr)
	{
		delete secondFigure;
		secondFigure = nullptr;
	}
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
	
	emit getNewFigureSignal();
}

void GeneralController::getNextFigure(quint8 newFigure)
{
	figure = secondFigure;
	switch (newFigure)
	{
	case TetrisInfo::Figures::I:
		secondFigure = new IFigure(m_blocks.value(TetrisInfo::Figures::I));
		break;
	case TetrisInfo::Figures::O:
		secondFigure = new OFigure(m_blocks.value(TetrisInfo::Figures::O));
		break;
	case TetrisInfo::Figures::T:
		secondFigure = new TFigure(m_blocks.value(TetrisInfo::Figures::T));
		break;
	case TetrisInfo::Figures::L:
		secondFigure = new LFigure(m_blocks.value(TetrisInfo::Figures::L));
		break;
	case TetrisInfo::Figures::J:
		secondFigure = new JFigure(m_blocks.value(TetrisInfo::Figures::J));
		break;
	case TetrisInfo::Figures::S:
		secondFigure = new SFigure(m_blocks.value(TetrisInfo::Figures::S));
		break;
	case TetrisInfo::Figures::Z:
		secondFigure = new ZFigure(m_blocks.value(TetrisInfo::Figures::Z));
		break;
	}
	emit newFigureSignal(secondFigure);
	
	if (isReadyToStart)
	{
		newTick();
	}
	else if (!isReadyToStart && figure != nullptr)
	{
		isReadyToStart = true;
		startGame();
	}
}

bool GeneralController::isRowFull(qint8 rowNumber) const
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

bool GeneralController::isObstacle(const QList<qint16> &cells) const
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

bool GeneralController::isLayerOverflow(const QList<qint16> &cells) const
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

void GeneralController::addFigure(const QList<qint16> &cells)
{
	foreach (qint16 cell, cells)
	{
		grid.insert(cell, figure->getImage());
	}
}

void GeneralController::deleteFigure(const QList<qint16> &cells)
{
	foreach (qint16 cell, cells)
	{
		grid.remove(cell);
	}
}

void GeneralController::checkRows(const QList<qint16> &cells, qint8 &topRow_out, qint8 &rowCount_out)
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

void GeneralController::addPoints(quint32 count)
{
	m_points += count;
	emit newPointsSignal(m_points);
	
	quint16 newLevel = static_cast<quint16>(m_points / NEW_LEVEL) + 1;
	if (level != newLevel)
	{
		level = newLevel;
		emit newLevelSignal(level);
	}
}

bool GeneralController::isNegativeCoords(const QList<qint16> &cells) const
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

void GeneralController::startGame()
{
	addFigure(figure->getCells());
	emit update(grid);
	m_points = 0;
	emit newPointsSignal(m_points);
	level = 1;
	emit newLevelSignal(level);
}
