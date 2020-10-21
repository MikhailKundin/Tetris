#include "generalcontroller.h"

#include <QRandomGenerator>
#include <QTime>
#include <QTimer>
#include <QtMath>

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

void GeneralController::moveRight()
{
	if (figure->moveRight())
	{
		emit moveRightSignal();
		emit update();
	}
}

void GeneralController::moveLeft()
{
	if (figure->moveLeft())
	{
		emit moveLeftSignal();
		emit update();
	}
}

void GeneralController::rotate()
{
	if (figure->rotate())
	{
		emit rotateSignal();
		emit update();
	}
}

void GeneralController::moveDown()
{
	if (figure->moveDown())
	{
		emit moveDownSignal();
		emit update();
	}
}

void GeneralController::tick()
{
	QList<qint16> coords = figure->getCoords();
	if (!checkPosition(coords))
	{
		moveDown();
		emit tickSignal();
		return;
	}
	
	qint16 shift = 0;
	foreach (qint16 coord, coords)
	{
		if (checkRow(getPairCoord(coord+shift).second))
		{
			deleteRow(coord+shift);
			shift += COLUMN_COUNT;
		}
	}
	m_points += POINTS[shift / COLUMN_COUNT];
	level = static_cast<qint16>(m_points / NEW_LEVEL);
	qint32 interval = static_cast<qint32>(START_INTERVAL / qPow(INTERVAL_DIV, level));
	timer->setInterval(interval);
	
	figure = nextFigure;
	getNextFigure();
	
	
}

QPair<qint16, qint16> GeneralController::getPairCoord(qint16 singleCoord)
{
	qint16 x = singleCoord % COLUMN_COUNT;
	qint16 y = singleCoord / COLUMN_COUNT;
	
	return {x, y};
}

qint16 GeneralController::getSingleCoord(QPair<qint16, qint16> pairCoord)
{
	qint16 x = pairCoord.first;
	qint16 y = pairCoord.second;
	
	return y*COLUMN_COUNT + x;
}

void GeneralController::getNextFigure()
{
	qint8 value = random.generate() % 7;
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

bool GeneralController::checkRow(qint16 y)
{
	for (qint16 x = 0; x < COLUMN_COUNT; x++)
	{
		qint16 coord = getSingleCoord({x, y});
		if (!map.contains(coord))
		{
			return false;
		}
	}
	return true;
}

void GeneralController::deleteRow(qint16 y)
{
	for (qint16 x = 0; x < COLUMN_COUNT; x++)
	{
		qint16 coord = getSingleCoord({x, y});
		map.remove(coord);
	}
	
	y--;
	while (y >= 0)
	{
		for (qint16 x = 0; x < COLUMN_COUNT; x++)
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

bool GeneralController::checkDefeat(QList<qint16> coords)
{
	
}
