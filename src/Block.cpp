#include "Block.h"

Block::Block(qint16 cell, QImage *image) : m_cell(cell), m_image(image)
{
	
}

void Block::setCell(qint16 cell)
{
	m_cell = cell;
}

qint16 Block::getCell() const
{
	return m_cell;
}

QImage *Block::getImage() const
{
	return m_image;
}
