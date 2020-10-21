#include "abstractfigure.h"

AbstractFigure::AbstractFigure(qint16 row, qint16 column) : ROW_COUNT(row), COLUMN_COUNT(column)
{
	
}

void AbstractFigure::moveRight()
{
	foreach (Block block, blocks)
	{
		block.setCoord(block.getCoord() + 1);
	}
}

void AbstractFigure::moveLeft()
{
	foreach (Block block, blocks)
	{
		block.setCoord(block.getCoord() - 1);
	}
}

void AbstractFigure::moveDown()
{
	foreach (Block block, blocks)
	{
		block.setCoord(block.getCoord() + COLUMN_COUNT);
	}
}

void AbstractFigure::moveUp()
{
	foreach (Block block, blocks)
	{
		block.setCoord(block.getCoord() - COLUMN_COUNT);
	}
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

IFigure::IFigure(qint16 row, qint16 column, QImage *image) : AbstractFigure(row, column)
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

void IFigure::rotate()
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
		break;
	case right:
	case left:
		backRotate();
		break;
	}
}

void IFigure::backRotate()
{
	QPair<qint16, qint16> pairCoord;
	qint16 x, y;
	Block block;
	
	switch (rotation)
	{
	case up:
	case down:
		rotate();
		break;
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
		break;
	}
}
