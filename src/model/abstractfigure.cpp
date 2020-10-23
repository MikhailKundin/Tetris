#include "abstractfigure.h"

#include <QDebug>

AbstractFigure::AbstractFigure(qint8 row, qint8 column) : ROW_COUNT(row), COLUMN_COUNT(column)
{
	
}

bool AbstractFigure::moveRight()
{
	QList<QPair<qint8, qint8> > pairCoords;
	QList<qint16> singleCoords;
	bool negative = false;
	foreach (Block block, blocks)
	{
		qint16 singleCoord = block.getCoord();
		singleCoords.append(singleCoord);
		if (singleCoord < 0)
		{
			negative = true;
		}
	}
	if (!negative)
	{
		for (qint8 i = 0; i < blocks.length(); i++)
		{
			QPair<qint8, qint8> pairCoord = getPairCoord(blocks.at(i).getCoord());
			pairCoord.first += 1;
			pairCoords.append(pairCoord);
		}
	}
	
	if (!negative)
	{
		if (!checkPosition(pairCoords))
		{
			return false;
		}
	}
	for (qint8 i = 0; i < blocks.length(); i++)
	{
		blocks[i].setCoord(singleCoords.at(i)+1);
	}
	return true;
}

bool AbstractFigure::moveLeft()
{
	QList<QPair<qint8, qint8> > pairCoords;
	QList<qint16> singleCoords;
	bool negative = false;
	foreach (Block block, blocks)
	{
		qint16 singleCoord = block.getCoord();
		singleCoords.append(singleCoord);
		if (singleCoord < 0)
		{
			negative = true;
		}
	}
	if (!negative)
	{
		for (qint8 i = 0; i < blocks.length(); i++)
		{
			QPair<qint8, qint8> pairCoord = getPairCoord(blocks.at(i).getCoord());
			pairCoord.first -= 1;
			pairCoords.append(pairCoord);
		}
	}
	
	if (!negative)
	{
		if (!checkPosition(pairCoords))
		{
			return false;
		}
	}
	for (qint8 i = 0; i < blocks.length(); i++)
	{
		blocks[i].setCoord(singleCoords.at(i)-1);
	}
	return true;
}

bool AbstractFigure::moveDown()
{
	QList<QPair<qint8, qint8> > pairCoords;
	QList<qint16> singleCoords;
	bool negative = false;
	foreach (Block block, blocks)
	{
		qint16 singleCoord = block.getCoord();
		singleCoords.append(singleCoord);
		if (singleCoord < 0)
		{
			negative = true;
		}
	}
	if (!negative)
	{
		for (qint8 i = 0; i < blocks.length(); i++)
		{
			QPair<qint8, qint8> pairCoord = getPairCoord(blocks.at(i).getCoord());
			pairCoord.second += 1;
			pairCoords.append(pairCoord);
		}
	}
	
	if (!negative)
	{
		if (!checkPosition(pairCoords))
		{
			return false;
		}
	}
	for (qint8 i = 0; i < blocks.length(); i++)
	{
		blocks[i].setCoord(singleCoords.at(i)+COLUMN_COUNT);
	}
	return true;
}

bool AbstractFigure::moveUp()
{
	QList<QPair<qint8, qint8> > pairCoords;
	QList<qint16> singleCoords;
	bool negative = false;
	foreach (Block block, blocks)
	{
		qint16 singleCoord = block.getCoord();
		singleCoords.append(singleCoord);
		if (singleCoord < 0)
		{
			negative = true;
		}
	}
	if (!negative)
	{
		for (qint8 i = 0; i < blocks.length(); i++)
		{
			QPair<qint8, qint8> pairCoord = getPairCoord(blocks.at(i).getCoord());
			pairCoord.second -= 1;
			pairCoords.append(pairCoord);
		}
	}
	
	if (!negative)
	{
		if (!checkPosition(pairCoords))
		{
			return false;
		}
	}
	for (qint8 i = 0; i < blocks.length(); i++)
	{
		blocks[i].setCoord(singleCoords.at(i)-COLUMN_COUNT);
	}
	return true;
}

QList<Block> &AbstractFigure::getBlocks()
{
	return blocks;
}

QList<qint16> AbstractFigure::getCoords()
{
	QList<qint16> res;
	foreach (Block block, blocks)
	{
		res.append(block.getCoord());
	}
	return res;
}

QImage *AbstractFigure::getImage()
{
	return blocks.at(0).getImage();
}

QPair<qint8, qint8> AbstractFigure::getPairCoord(qint16 singleCoord)
{
	qint8 x = singleCoord % COLUMN_COUNT;
	qint8 y = static_cast<qint8>(singleCoord / COLUMN_COUNT);
	
	return {x, y};
}

qint16 AbstractFigure::getSingleCoord(QPair<qint8, qint8> pairCoord)
{
	qint16 x = pairCoord.first;
	qint16 y = pairCoord.second;
	
	return y*COLUMN_COUNT + x;
}

bool AbstractFigure::checkPosition(QList<QPair<qint8, qint8> > coords)
{
	for (qint8 i = 0; i < coords.length(); i++)
	{
		QPair<qint8, qint8> coord = coords.at(i);
		qint8 x = coord.first;
		qint8 y = coord.second;
		
		if (x < 0 || x >= COLUMN_COUNT)
		{
			return false;
		}
		if (y >= ROW_COUNT)
		{
			return false;
		}
	}
	return true;
}

IFigure::IFigure(qint8 row, qint8 column, QImage *image) : AbstractFigure(row, column)
{
	qint8 x, y;
	qint16 coord;
	qint8 middle = COLUMN_COUNT / 2;
	
	x = middle - 2;
	y = -1;
	coord = getSingleCoord({x, y});
	blocks.append(Block(coord, image));
	
	x = middle - 1;
	y = -1;
	coord = getSingleCoord({x, y});
	blocks.append(Block(coord, image));
	
	x = middle;
	y = -1;
	coord = getSingleCoord({x, y});
	blocks.append(Block(coord, image));
	
	x = middle + 1;
	y = -1;
	coord = getSingleCoord({x, y});
	blocks.append(Block(coord, image));
}

bool IFigure::rotate()
{
	QList<QPair<qint8, qint8> > pairCoords;
	switch (rotation)
	{
	case up:
		pairCoords = rotateUpRight(1);
		if (setCoords(pairCoords))
		{
			rotation = right;
			return true;
		}
		else
		{
			return false;
		}
	case right:
		pairCoords = rotateRightDown(1);
		if (setCoords(pairCoords))
		{
			rotation = down;
			return true;
		}
		else
		{
			return false;
		}
	case down:		
		pairCoords = rotateDownLeft(1);
		if (setCoords(pairCoords))
		{
			rotation = left;
			return true;
		}
		else
		{
			return false;
		}
	case left:
		pairCoords = rotateLeftUp(1);
		if (setCoords(pairCoords))
		{
			rotation = up;
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool IFigure::backRotate()
{
	QList<QPair<qint8, qint8> > pairCoords;
	switch (rotation)
	{
	case up:
		pairCoords = rotateLeftUp(-1);
		if (setCoords(pairCoords))
		{
			rotation = left;
			return true;
		}
		else
		{
			return false;
		}
	case right:
		pairCoords = rotateUpRight(-1);
		if (setCoords(pairCoords))
		{
			rotation = up;
			return true;
		}
		else
		{
			return false;
		}
	case down:		
		pairCoords = rotateRightDown(-1);
		if (setCoords(pairCoords))
		{
			rotation = right;
			return true;
		}
		else
		{
			return false;
		}
	case left:
		pairCoords = rotateDownLeft(-1);
		if (setCoords(pairCoords))
		{
			rotation = down;
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

QList<QPair<qint8, qint8> > IFigure::rotateUpRight(qint8 mult)
{
	QList<QPair<qint8, qint8> > pairCoords;
	QPair<qint8, qint8> pairCoord;
	
	pairCoord = getPairCoord(blocks.at(0).getCoord());
	pairCoord.first += 2*mult;
	pairCoord.second -= 2*mult;
	pairCoords.append(pairCoord);
	
	pairCoord = getPairCoord(blocks.at(1).getCoord());
	pairCoord.first += 1*mult;
	pairCoord.second -= 1*mult;
	pairCoords.append(pairCoord);
	
	pairCoord = getPairCoord(blocks.at(3).getCoord());
	pairCoord.first -= 1*mult;
	pairCoord.second += 1*mult;
	pairCoords.append(pairCoord);
	
	return pairCoords;
}

QList<QPair<qint8, qint8> > IFigure::rotateRightDown(qint8 mult)
{
	QList<QPair<qint8, qint8> > pairCoords;
	QPair<qint8, qint8> pairCoord;
	
	pairCoord = getPairCoord(blocks.at(0).getCoord());
	pairCoord.first += 2*mult;
	pairCoord.second += 2*mult;
	pairCoords.append(pairCoord);
	
	pairCoord = getPairCoord(blocks.at(1).getCoord());
	pairCoord.first += 1*mult;
	pairCoord.second += 1*mult;
	pairCoords.append(pairCoord);
	
	pairCoord = getPairCoord(blocks.at(3).getCoord());
	pairCoord.first -= 1*mult;
	pairCoord.second -= 1*mult;
	pairCoords.append(pairCoord);
	
	return pairCoords;
}

QList<QPair<qint8, qint8> > IFigure::rotateDownLeft(qint8 mult)
{
	QList<QPair<qint8, qint8> > pairCoords;
	QPair<qint8, qint8> pairCoord;
	
	pairCoord = getPairCoord(blocks.at(0).getCoord());
	pairCoord.first -= 2*mult;
	pairCoord.second += 2*mult;
	pairCoords.append(pairCoord);
	
	pairCoord = getPairCoord(blocks.at(1).getCoord());
	pairCoord.first -= 1*mult;
	pairCoord.second += 1*mult;
	pairCoords.append(pairCoord);
	
	pairCoord = getPairCoord(blocks.at(3).getCoord());
	pairCoord.first += 1*mult;
	pairCoord.second -= 1*mult;
	pairCoords.append(pairCoord);
	
	return pairCoords;
}

QList<QPair<qint8, qint8> > IFigure::rotateLeftUp(qint8 mult)
{
	QList<QPair<qint8, qint8> > pairCoords;
	QPair<qint8, qint8> pairCoord;
	
	pairCoord = getPairCoord(blocks.at(0).getCoord());
	pairCoord.first -= 2*mult;
	pairCoord.second -= 2*mult;
	pairCoords.append(pairCoord);
	
	pairCoord = getPairCoord(blocks.at(1).getCoord());
	pairCoord.first -= 1*mult;
	pairCoord.second -= 1*mult;
	pairCoords.append(pairCoord);
	
	pairCoord = getPairCoord(blocks.at(3).getCoord());
	pairCoord.first += 1*mult;
	pairCoord.second += 1*mult;
	pairCoords.append(pairCoord);
	
	return pairCoords;
}

bool IFigure::setCoords(QList<QPair<qint8, qint8> > pairCoords)
{
	if (checkPosition(pairCoords))
	{
		for (qint8 i = 0; i < blocks.length(); i++)
		{
			blocks[i].setCoord(getSingleCoord(pairCoords.at(i)));
		}
		return true;
	}
	else
	{
		return false;
	}
}

OFigure::OFigure(qint8 row, qint8 column, QImage *image) : AbstractFigure(row, column)
{
	
}

bool OFigure::rotate()
{
	return false;
}

bool OFigure::backRotate()
{
	return false;
}

TFigure::TFigure(qint8 row, qint8 column, QImage *image) : AbstractFigure(row, column)
{
	
}

bool TFigure::rotate()
{
	return false;
}

bool TFigure::backRotate()
{
	return false;
}

LFigure::LFigure(qint8 row, qint8 column, QImage *image) : AbstractFigure(row, column)
{
	
}

bool LFigure::rotate()
{
	return false;
}

bool LFigure::backRotate()
{
	return false;
}

JFigure::JFigure(qint8 row, qint8 column, QImage *image) : AbstractFigure(row, column)
{
	
}

bool JFigure::rotate()
{
	return false;
}

bool JFigure::backRotate()
{
	return false;
}

SFigure::SFigure(qint8 row, qint8 column, QImage *image) : AbstractFigure(row, column)
{
	
}

bool SFigure::rotate()
{
	return false;
}

bool SFigure::backRotate()
{
	return false;
}

ZFigure::ZFigure(qint8 row, qint8 column, QImage *image) : AbstractFigure(row, column)
{
	
}

bool ZFigure::rotate()
{
	return false;
}

bool ZFigure::backRotate()
{
	return false;
}
