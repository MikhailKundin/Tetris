#include "abstractfigure.h"

AbstractFigure::AbstractFigure(qint8 row, qint8 column) : ROW_COUNT(row), COLUMN_COUNT(column)
{
	
}

bool AbstractFigure::moveRight()
{
	foreach (Block block, blocks)
	{
		block.setCoord(block.getCoord() + 1);
	}
	if (!checkPosition())
	{
		moveLeft();
		return false;
	}
	return true;
}

bool AbstractFigure::moveLeft()
{
	foreach (Block block, blocks)
	{
		block.setCoord(block.getCoord() - 1);
	}
	if (!checkPosition())
	{
		moveRight();
		return false;
	}
	return true;
}

bool AbstractFigure::moveDown()
{
	foreach (Block block, blocks)
	{
		block.setCoord(block.getCoord() + COLUMN_COUNT);
	}
	if (!checkPosition())
	{
		moveUp();
		return false;
	}
	return true;
}

bool AbstractFigure::moveUp()
{
	foreach (Block block, blocks)
	{
		block.setCoord(block.getCoord() - COLUMN_COUNT);
	}
	if (!checkPosition())
	{
		moveDown();
		return false;
	}
	return true;
}

QList<Block> AbstractFigure::getBlocks()
{
	return blocks;
}

QPair<qint16, qint16> AbstractFigure::getPairCoord(qint16 singleCoord)
{
	qint16 x = singleCoord % COLUMN_COUNT;
	qint16 y = singleCoord / COLUMN_COUNT;
	
	return {x, y};
}

qint16 AbstractFigure::getSingleCoord(QPair<qint16, qint16> pairCoord)
{
	qint16 x = pairCoord.first;
	qint16 y = pairCoord.second;
	
	return y*COLUMN_COUNT + x;
}

bool AbstractFigure::checkPosition()
{
	foreach (Block block, blocks)
	{
		QPair<qint16, qint16> pairCoord = getPairCoord(block.getCoord());
		qint16 x = pairCoord.first;
		qint16 y = pairCoord.second;
		
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
	qint16 x, y, coord;
	qint16 middle = COLUMN_COUNT / 2;
	
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
	QPair<qint16, qint16> pairCoord;
	qint16 x, y;
	Block block;
	
	switch (rotation)
	{
	case up:
	case down:
		block = blocks[0];
		pairCoord = getPairCoord(block.getCoord());
		x = pairCoord.first;
		y = pairCoord.second;
		block.setCoord(getSingleCoord({x+2, y-2}));
		blocks.replace(0, block);
		
		block = blocks[1];
		pairCoord = getPairCoord(block.getCoord());
		x = pairCoord.first;
		y = pairCoord.second;
		block.setCoord(getSingleCoord({x+1, y-1}));
		blocks.replace(1, block);
		
		block = blocks[3];
		pairCoord = getPairCoord(block.getCoord());
		x = pairCoord.first;
		y = pairCoord.second;
		block.setCoord(getSingleCoord({x-1, y+1}));
		blocks.replace(3, block);
		
		rotation = right;
		if (!checkPosition())
		{
			backRotate();
			return false;
		}
		return true;
	case right:
	case left:
		backRotate();
		if (!checkPosition())
		{
			rotate();
			return false;
		}
		return true;
	}
	return false;
}

bool IFigure::backRotate()
{
	QPair<qint16, qint16> pairCoord;
	qint16 x, y;
	Block block;
	
	switch (rotation)
	{
	case up:
	case down:
		rotate();
		if (!checkPosition())
		{
			backRotate();
			return false;
		}
		return true;
	case right:
	case left:
		block = blocks[0];
		pairCoord = getPairCoord(block.getCoord());
		x = pairCoord.first;
		y = pairCoord.second;
		block.setCoord(getSingleCoord({x-2, y+2}));
		blocks.replace(0, block);
		
		block = blocks[1];
		pairCoord = getPairCoord(block.getCoord());
		x = pairCoord.first;
		y = pairCoord.second;
		block.setCoord(getSingleCoord({x-1, y+1}));
		blocks.replace(1, block);
		
		block = blocks[3];
		pairCoord = getPairCoord(block.getCoord());
		x = pairCoord.first;
		y = pairCoord.second;
		block.setCoord(getSingleCoord({x+1, y-1}));
		blocks.replace(3, block);
		
		rotation = up;
		if (!checkPosition())
		{
			rotate();
			return false;
		}
		return true;
	}
	return false;
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
