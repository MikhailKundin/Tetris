#include "AbstractFigure.h"

#include "../TetrisInfo.h"

#include <QDebug>

bool AbstractFigure::moveRight()
{
	QList<QPair<qint8, qint8> > coords;
	QList<qint16> cells;
	bool negative = false;
	foreach (Block block, blocks)
	{
		qint16 cell = block.getCell();
		cells.append(cell);
		if (cell < 0)
		{
			negative = true;
		}
	}
	if (!negative)
	{
		for (qint8 i = 0; i < blocks.length(); i++)
		{
			QPair<qint8, qint8> coord = TetrisInfo::getCoord(blocks.at(i).getCell());
			coord.first += 1;
			coords.append(coord);
		}
		if (isOutOfBounds(coords))
		{
			return false;
		}
	}
	else
	{
		if (!isNegativeMoveRight(cells))
		{
			return false;
		}
	}
	
	for (qint8 i = 0; i < blocks.length(); i++)
	{
		blocks[i].setCell(cells.at(i)+1);
	}
	return true;
}

bool AbstractFigure::moveLeft()
{
	QList<QPair<qint8, qint8> > coords;
	QList<qint16> cells;
	bool negative = false;
	foreach (Block block, blocks)
	{
		qint16 cell = block.getCell();
		cells.append(cell);
		if (cell < 0)
		{
			negative = true;
		}
	}
	if (!negative)
	{
		for (qint8 i = 0; i < blocks.length(); i++)
		{
			QPair<qint8, qint8> coord = TetrisInfo::getCoord(blocks.at(i).getCell());
			coord.first -= 1;
			coords.append(coord);
		}
		if (isOutOfBounds(coords))
		{
			return false;
		}
	}
	else
	{
		if (!isNegativeMoveLeft(cells))
		{
			return false;
		}
	}
	
	for (qint8 i = 0; i < blocks.length(); i++)
	{
		blocks[i].setCell(cells.at(i)-1);
	}
	return true;
}

bool AbstractFigure::moveDown()
{
	QList<QPair<qint8, qint8> > coords;
	QList<qint16> cells;
	bool negative = false;
	foreach (Block block, blocks)
	{
		qint16 cell = block.getCell();
		cells.append(cell);
		if (cell < 0)
		{
			negative = true;
		}
	}
	if (!negative)
	{
		for (qint8 i = 0; i < blocks.length(); i++)
		{
			QPair<qint8, qint8> coord = TetrisInfo::getCoord(blocks.at(i).getCell());
			coord.second += 1;
			coords.append(coord);
		}
	}
	
	if (!negative)
	{
		if (isOutOfBounds(coords))
		{
			return false;
		}
	}
	for (qint8 i = 0; i < blocks.length(); i++)
	{
		blocks[i].setCell(cells.at(i)+TetrisInfo::COLUMN_COUNT);
	}
	return true;
}

bool AbstractFigure::moveUp()
{
	QList<QPair<qint8, qint8> > coords;
	QList<qint16> cells;
	bool negative = false;
	foreach (Block block, blocks)
	{
		qint16 cell = block.getCell();
		cells.append(cell);
		if (cell < 0)
		{
			negative = true;
		}
	}
	if (!negative)
	{
		for (qint8 i = 0; i < blocks.length(); i++)
		{
			QPair<qint8, qint8> coord = TetrisInfo::getCoord(blocks.at(i).getCell());
			coord.second -= 1;
			coords.append(coord);
		}
	}
	
	if (!negative)
	{
		if (isOutOfBounds(coords))
		{
			return false;
		}
	}
	for (qint8 i = 0; i < blocks.length(); i++)
	{
		blocks[i].setCell(cells.at(i)-TetrisInfo::COLUMN_COUNT);
	}
	return true;
}

bool AbstractFigure::rotate()
{
	QList<QPair<qint8, qint8> > coords;
	switch (rotation)
	{
	case Rotation::up:
		coords = rotateUpLeft(Direction::forward);
		if (!isOutOfBounds(coords))
		{
			updateCoords(coords);
			rotation = Rotation::left;
			return true;
		}
		else
		{
			return false;
		}
	case Rotation::left:
		coords = rotateLeftDown(Direction::forward);
		if (!isOutOfBounds(coords))
		{
			updateCoords(coords);
			rotation = Rotation::down;
			return true;
		}
		else
		{
			return false;
		}
	case Rotation::down:		
		coords = rotateDownRight(Direction::forward);
		if (!isOutOfBounds(coords))
		{
			updateCoords(coords);
			rotation = Rotation::right;
			return true;
		}
		else
		{
			return false;
		}
	case Rotation::right:
		coords = rotateRightUp(Direction::forward);
		if (!isOutOfBounds(coords))
		{
			updateCoords(coords);
			rotation = Rotation::up;
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool AbstractFigure::backRotate()
{
	QList<QPair<qint8, qint8> > coords;
	switch (rotation)
	{
	case Rotation::up:
		coords = rotateRightUp(Direction::backward);
		if (!isOutOfBounds(coords))
		{
			updateCoords(coords);
			rotation = Rotation::right;
			return true;
		}
		else
		{
			return false;
		}
	case Rotation::left:
		coords = rotateUpLeft(Direction::backward);
		if (!isOutOfBounds(coords))
		{
			updateCoords(coords);
			rotation = Rotation::up;
			return true;
		}
		else
		{
			return false;
		}
	case Rotation::down:		
		coords = rotateLeftDown(Direction::backward);
		if (!isOutOfBounds(coords))
		{
			updateCoords(coords);
			rotation = Rotation::left;
			return true;
		}
		else
		{
			return false;
		}
	case Rotation::right:
		coords = rotateDownRight(Direction::backward);
		if (!isOutOfBounds(coords))
		{
			updateCoords(coords);
			rotation = Rotation::down;
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

qint8 AbstractFigure::getType() const
{
	return type;
}

const QList<Block> &AbstractFigure::getBlocks() const
{
	return blocks;
}

QList<qint16> AbstractFigure::getCells() const
{
	QList<qint16> res;
	foreach (Block block, blocks)
	{
		res.append(block.getCell());
	}
	return res;
}

QImage *AbstractFigure::getImage()
{
	return blocks.at(0).getImage();
}

void AbstractFigure::updateCoords(const QList<QPair<qint8, qint8> > &coords)
{
	for (qint8 i = 0; i < blocks.length(); i++)
	{
		blocks[i].setCell(TetrisInfo::getCell(coords.at(i)));
	}
}

bool AbstractFigure::isOutOfBounds(const QList<QPair<qint8, qint8> > &coords) const
{
	for (qint8 i = 0; i < coords.length(); i++)
	{
		QPair<qint8, qint8> coord = coords.at(i);
		qint8 x = coord.first;
		qint8 y = coord.second;
		
		if (x < 0 || x >= TetrisInfo::COLUMN_COUNT)
		{
			return true;
		}
		
		if (y >= TetrisInfo::ROW_COUNT)
		{
			return true;
		}
	}
	return false;
}

bool AbstractFigure::isNegativeMoveRight(const QList<qint16> &cells) const
{
	QList<QPair<qint8, qint8> > positiveCoords;
	foreach (qint16 cell, cells)
	{
		if (cell > 0)
		{
			QPair<qint8, qint8> positiveCoord = TetrisInfo::getCoord(cell);
			positiveCoord.first += 1;
			positiveCoords.append(positiveCoord);
		}
		if (cell % TetrisInfo::ROW_COUNT == -1)
		{
			return false;
		}
	}
	if (isOutOfBounds(positiveCoords))
	{
		return false;
	}
	return true;
}

bool AbstractFigure::isNegativeMoveLeft(const QList<qint16> &cells) const
{
	QList<QPair<qint8, qint8> > positiveCoords;
	foreach (qint16 cell, cells)
	{
		if (cell > 0)
		{
			QPair<qint8, qint8> positiveCoord = TetrisInfo::getCoord(cell);
			positiveCoord.first -= 1;
			positiveCoords.append(positiveCoord);
		}
		if (cell % TetrisInfo::ROW_COUNT == 0)
		{
			return false;
		}
	}
	if (isOutOfBounds(positiveCoords))
	{
		return false;
	}
	return true;
}

IFigure::IFigure(QImage *image)
{
	qint8 x, y;
	qint16 cell;
	qint8 middle = TetrisInfo::COLUMN_COUNT / 2;
	
	x = middle - 2;
	y = -1;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
	x = middle - 1;
	y = -1;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
	x = middle;
	y = -1;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
	x = middle + 1;
	y = -1;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
	type = TetrisInfo::Figures::I;
}

QList<QPair<qint8, qint8> > IFigure::rotateUpLeft(qint8 mult) const
{
	QList<QPair<qint8, qint8> > coords;
	QPair<qint8, qint8> coord;
	
	coord = TetrisInfo::getCoord(blocks.at(0).getCell());
	coord.first += 2*mult;
	coord.second += 2*mult;
	coords.append(coord);
	
	coord = TetrisInfo::getCoord(blocks.at(1).getCell());
	coord.first += 1*mult;
	coord.second += 1*mult;
	coords.append(coord);
	
	coord = TetrisInfo::getCoord(blocks.at(2).getCell());
	coords.append(coord);
	
	coord = TetrisInfo::getCoord(blocks.at(3).getCell());
	coord.first -= 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	return coords;
}

QList<QPair<qint8, qint8> > IFigure::rotateLeftDown(qint8 mult) const
{
	return rotateUpLeft(-1*mult);
}

QList<QPair<qint8, qint8> > IFigure::rotateDownRight(qint8 mult) const
{
	return rotateUpLeft(mult);
}

QList<QPair<qint8, qint8> > IFigure::rotateRightUp(qint8 mult) const
{
	return rotateUpLeft(-1*mult);
}

OFigure::OFigure(QImage *image)
{
	qint8 x, y;
	qint16 cell;
	qint8 middle = TetrisInfo::COLUMN_COUNT / 2;
	
	x = middle - 1;
	y = -2;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
	x = middle;
	y = -2;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
	x = middle - 1;
	y = -1;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
	x = middle;
	y = -1;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
	type = TetrisInfo::Figures::O;
}

QList<QPair<qint8, qint8> > OFigure::rotateUpLeft(qint8 mult) const
{
	Q_UNUSED(mult)
	
	QList<QPair<qint8, qint8> > coords;
	QPair<qint8, qint8> coord;
	
	for (qint8 i = 0; i < 4; i++)
	{
		coord = TetrisInfo::getCoord(blocks.at(i).getCell());
		coords.append(coord);
	}
	
	return coords;
}

QList<QPair<qint8, qint8> > OFigure::rotateLeftDown(qint8 mult) const
{
	return rotateUpLeft(mult);
}

QList<QPair<qint8, qint8> > OFigure::rotateDownRight(qint8 mult) const
{
	return rotateUpLeft(mult);
}

QList<QPair<qint8, qint8> > OFigure::rotateRightUp(qint8 mult) const
{
	return rotateUpLeft(mult);
}

TFigure::TFigure(QImage *image)
{
	qint8 x, y;
	qint16 cell;
	qint8 middle = TetrisInfo::COLUMN_COUNT / 2;
	
	x = middle - 1;
	y = -2;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
	x = middle;
	y = -2;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
	x = middle + 1;
	y = -2;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
	x = middle;
	y = -1;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
	type = TetrisInfo::Figures::T;
}

QList<QPair<qint8, qint8> > TFigure::rotateUpLeft(qint8 mult) const
{
	QList<QPair<qint8, qint8> > coords;
	QPair<qint8, qint8> coord;
	
	coord = TetrisInfo::getCoord(blocks.at(0).getCell());
	coord.first += 1*mult;
	coord.second += 1*mult;
	coords.append(coord);
	
	coord = TetrisInfo::getCoord(blocks.at(1).getCell());
	coords.append(coord);
	
	coord = TetrisInfo::getCoord(blocks.at(2).getCell());
	coord.first -= 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	coord = TetrisInfo::getCoord(blocks.at(3).getCell());
	coord.first += 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	return coords;
}

QList<QPair<qint8, qint8> > TFigure::rotateLeftDown(qint8 mult) const
{
	QList<QPair<qint8, qint8> > coords;
	QPair<qint8, qint8> coord;
	
	coord = TetrisInfo::getCoord(blocks.at(0).getCell());
	coord.first += 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	coord = TetrisInfo::getCoord(blocks.at(1).getCell());
	coords.append(coord);
	
	coord = TetrisInfo::getCoord(blocks.at(2).getCell());
	coord.first -= 1*mult;
	coord.second += 1*mult;
	coords.append(coord);
	
	coord = TetrisInfo::getCoord(blocks.at(3).getCell());
	coord.first -= 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	return coords;
}

QList<QPair<qint8, qint8> > TFigure::rotateDownRight(qint8 mult) const
{
	QList<QPair<qint8, qint8> > coords;
	QPair<qint8, qint8> coord;
	
	coord = TetrisInfo::getCoord(blocks.at(0).getCell());
	coord.first -= 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	coord = TetrisInfo::getCoord(blocks.at(1).getCell());
	coords.append(coord);
	
	coord = TetrisInfo::getCoord(blocks.at(2).getCell());
	coord.first += 1*mult;
	coord.second += 1*mult;
	coords.append(coord);
	
	coord = TetrisInfo::getCoord(blocks.at(3).getCell());
	coord.first -= 1*mult;
	coord.second += 1*mult;
	coords.append(coord);
	
	return coords;
}

QList<QPair<qint8, qint8> > TFigure::rotateRightUp(qint8 mult) const
{
	QList<QPair<qint8, qint8> > coords;
	QPair<qint8, qint8> coord;
	
	coord = TetrisInfo::getCoord(blocks.at(0).getCell());
	coord.first -= 1*mult;
	coord.second += 1*mult;
	coords.append(coord);
	
	coord = TetrisInfo::getCoord(blocks.at(1).getCell());
	coords.append(coord);
	
	coord = TetrisInfo::getCoord(blocks.at(2).getCell());
	coord.first += 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	coord = TetrisInfo::getCoord(blocks.at(3).getCell());
	coord.first += 1*mult;
	coord.second += 1*mult;
	coords.append(coord);
	
	return coords;
}
