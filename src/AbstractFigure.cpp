#include "AbstractFigure.h"

#include "TetrisInfo.h"

#include <QDebug>

bool AbstractFigure::moveRight()
{
	QList<QPair<qint8, qint8> > coords;
	foreach (Block block, blocks)
	{
		qint16 cell = block.getCell();
		QPair<qint8, qint8> coord = TetrisInfo::getCoord(cell);
		if (cell < 0)
		{
			getNegativeCoord(coord);
		}
		coord.first += 1;
		coords.append(coord);
	}
	if (isOutOfBounds(coords))
	{
		return false;
	}
	
	updateCoords(coords);
	return true;
}

bool AbstractFigure::moveLeft()
{
	QList<QPair<qint8, qint8> > coords;
	foreach (Block block, blocks)
	{
		qint16 cell = block.getCell();
		QPair<qint8, qint8> coord = TetrisInfo::getCoord(cell);
		if (cell < 0)
		{
			getNegativeCoord(coord);
		}
		coord.first -= 1;
		coords.append(coord);
	}
	if (isOutOfBounds(coords))
	{
		return false;
	}
	
	updateCoords(coords);
	return true;
}

bool AbstractFigure::moveDown()
{
	QList<QPair<qint8, qint8> > coords;
	foreach (Block block, blocks)
	{
		qint16 cell = block.getCell();
		QPair<qint8, qint8> coord = TetrisInfo::getCoord(cell);
		if (cell < 0)
		{
			getNegativeCoord(coord);
		}
		coord.second += 1;
		coords.append(coord);
	}
	if (isOutOfBounds(coords))
	{
		return false;
	}
	
	updateCoords(coords);
	return true;
}

bool AbstractFigure::moveUp()
{
	QList<QPair<qint8, qint8> > coords;
	foreach (Block block, blocks)
	{
		qint16 cell = block.getCell();
		QPair<qint8, qint8> coord = TetrisInfo::getCoord(cell);
		if (cell < 0)
		{
			getNegativeCoord(coord);
		}
		coord.second -= 1;
		coords.append(coord);
	}
	if (isOutOfBounds(coords))
	{
		return false;
	}
	
	updateCoords(coords);
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

void AbstractFigure::getNegativeCoord(QPair<qint8, qint8> &coord) const
{
	if (coord.first != 0)
	{
		coord.first += TetrisInfo::COLUMN_COUNT;
		coord.second = coord.second - 1;
	}
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
	qint16 cell;
	
	cell = blocks.at(0).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first += 2*mult;
	coord.second += 2*mult;
	coords.append(coord);
	
	cell = blocks.at(1).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first += 1*mult;
	coord.second += 1*mult;
	coords.append(coord);
	
	cell = blocks.at(2).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coords.append(coord);
	
	cell = blocks.at(3).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
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
	qint16 cell;
	
	cell = blocks.at(0).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first += 1*mult;
	coord.second += 1*mult;
	coords.append(coord);
	
	cell = blocks.at(1).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coords.append(coord);
	
	cell = blocks.at(2).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first -= 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	cell = blocks.at(3).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first += 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	return coords;
}

QList<QPair<qint8, qint8> > TFigure::rotateLeftDown(qint8 mult) const
{
	QList<QPair<qint8, qint8> > coords;
	QPair<qint8, qint8> coord;
	qint16 cell;
	
	cell = blocks.at(0).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first += 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	cell = blocks.at(1).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coords.append(coord);
	
	cell = blocks.at(2).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first -= 1*mult;
	coord.second += 1*mult;
	coords.append(coord);
	
	cell = blocks.at(3).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first -= 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	return coords;
}

QList<QPair<qint8, qint8> > TFigure::rotateDownRight(qint8 mult) const
{
	return rotateUpLeft(-1*mult);
}

QList<QPair<qint8, qint8> > TFigure::rotateRightUp(qint8 mult) const
{
	return rotateLeftDown(-1*mult);
}

LFigure::LFigure(QImage *image)
{
	qint8 x, y;
	qint16 cell;
	qint8 middle = TetrisInfo::COLUMN_COUNT / 2;
	
	x = middle - 1;
	y = -1;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
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
	
	type = TetrisInfo::Figures::L;
}

QList<QPair<qint8, qint8> > LFigure::rotateUpLeft(qint8 mult) const
{
	QList<QPair<qint8, qint8> > coords;
	QPair<qint8, qint8> coord;
	qint16 cell;
	
	cell = blocks.at(0).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first += 2*mult;
	coords.append(coord);
	
	cell = blocks.at(1).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first += 1*mult;
	coord.second += 1*mult;
	coords.append(coord);
	
	cell = blocks.at(2).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coords.append(coord);
	
	cell = blocks.at(3).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first -= 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	return coords;
}

QList<QPair<qint8, qint8> > LFigure::rotateLeftDown(qint8 mult) const
{
	QList<QPair<qint8, qint8> > coords;
	QPair<qint8, qint8> coord;
	qint16 cell;
	
	cell = blocks.at(0).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.second -= 2*mult;
	coords.append(coord);
	
	cell = blocks.at(1).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first += 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	cell = blocks.at(2).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coords.append(coord);
	
	cell = blocks.at(3).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first -= 1*mult;
	coord.second += 1*mult;
	coords.append(coord);
	
	return coords;
}

QList<QPair<qint8, qint8> > LFigure::rotateDownRight(qint8 mult) const
{
	return rotateUpLeft(-1*mult);
}

QList<QPair<qint8, qint8> > LFigure::rotateRightUp(qint8 mult) const
{
	return rotateLeftDown(-1*mult);
}

JFigure::JFigure(QImage *image)
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
	
	x = middle + 1;
	y = -1;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
	type = TetrisInfo::Figures::J;
}

QList<QPair<qint8, qint8> > JFigure::rotateUpLeft(qint8 mult) const
{
	QList<QPair<qint8, qint8> > coords;
	QPair<qint8, qint8> coord;
	qint16 cell;
	
	cell = blocks.at(0).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first += 1*mult;
	coord.second += 1*mult;
	coords.append(coord);
	
	cell = blocks.at(1).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coords.append(coord);
	
	cell = blocks.at(2).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first -= 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	cell = blocks.at(3).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.second -= 2*mult;
	coords.append(coord);
	
	return coords;
}

QList<QPair<qint8, qint8> > JFigure::rotateLeftDown(qint8 mult) const
{
	QList<QPair<qint8, qint8> > coords;
	QPair<qint8, qint8> coord;
	qint16 cell;
	
	cell = blocks.at(0).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first += 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	cell = blocks.at(1).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coords.append(coord);
	
	cell = blocks.at(2).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first -= 1*mult;
	coord.second += 1*mult;
	coords.append(coord);
	
	cell = blocks.at(3).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first -= 2*mult;
	coords.append(coord);
	
	return coords;
}

QList<QPair<qint8, qint8> > JFigure::rotateDownRight(qint8 mult) const
{
	return rotateUpLeft(-1*mult);
}

QList<QPair<qint8, qint8> > JFigure::rotateRightUp(qint8 mult) const
{
	return rotateLeftDown(-1*mult);
}

SFigure::SFigure(QImage *image)
{
	qint8 x, y;
	qint16 cell;
	qint8 middle = TetrisInfo::COLUMN_COUNT / 2;
	
	x = middle - 1;
	y = -1;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
	x = middle;
	y = -1;
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
	
	type = TetrisInfo::Figures::S;
}

QList<QPair<qint8, qint8> > SFigure::rotateUpLeft(qint8 mult) const
{
	QList<QPair<qint8, qint8> > coords;
	QPair<qint8, qint8> coord;
	qint16 cell;
	
	cell = blocks.at(0).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first += 2*mult;
	coords.append(coord);
	
	cell = blocks.at(1).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first += 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	cell = blocks.at(2).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coords.append(coord);
	
	cell = blocks.at(3).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first -= 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	return coords;
}

QList<QPair<qint8, qint8> > SFigure::rotateLeftDown(qint8 mult) const
{
	return rotateUpLeft(-1*mult);
}

QList<QPair<qint8, qint8> > SFigure::rotateDownRight(qint8 mult) const
{
	return rotateUpLeft(mult);
}

QList<QPair<qint8, qint8> > SFigure::rotateRightUp(qint8 mult) const
{
	return rotateUpLeft(-1*mult);
}

ZFigure::ZFigure(QImage *image)
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
	
	x = middle;
	y = -1;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
	x = middle + 1;
	y = -1;
	cell = TetrisInfo::getCell({x, y});
	blocks.append(Block(cell, image));
	
	type = TetrisInfo::Figures::Z;
}

QList<QPair<qint8, qint8> > ZFigure::rotateUpLeft(qint8 mult) const
{
	QList<QPair<qint8, qint8> > coords;
	QPair<qint8, qint8> coord;
	qint16 cell;
	
	cell = blocks.at(0).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first += 1*mult;
	coord.second += 1*mult;
	coords.append(coord);
	
	cell = blocks.at(1).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coords.append(coord);
	
	cell = blocks.at(2).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.first += 1*mult;
	coord.second -= 1*mult;
	coords.append(coord);
	
	cell = blocks.at(3).getCell();
	coord = TetrisInfo::getCoord(cell);
	if (cell < 0)
	{
		getNegativeCoord(coord);
	}
	coord.second -= 2*mult;
	coords.append(coord);
	
	return coords;
}

QList<QPair<qint8, qint8> > ZFigure::rotateLeftDown(qint8 mult) const
{
	return rotateUpLeft(-1*mult);
}

QList<QPair<qint8, qint8> > ZFigure::rotateDownRight(qint8 mult) const
{
	return rotateUpLeft(mult);
}

QList<QPair<qint8, qint8> > ZFigure::rotateRightUp(qint8 mult) const
{
	return rotateUpLeft(-1*mult);
}
