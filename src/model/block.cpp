#include "Block.h"

Block::Block()
{
	
}

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

void Block::setImage(QImage *image)
{
	m_image = image;
}

QImage *Block::getImage() const
{
	return m_image;
}

QPair<qint16, QImage *> Block::getBlock() const
{
	return {m_cell, m_image};
}
