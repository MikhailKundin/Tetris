#include "block.h"

Block::Block()
{
	
}

Block::Block(qint16 coord, QImage *image) : m_coord(coord), m_image(image)
{
	
}

Block::~Block()
{
	delete m_image;
}

void Block::setCoord(qint16 coord)
{
	m_coord = coord;
}

qint16 Block::getCoord() const
{
	return m_coord;
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
	return {m_coord, m_image};
}
