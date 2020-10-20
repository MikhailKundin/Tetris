#include "block.h"

Block::Block()
{
	
}

Block::Block(qint16 coord, QImage *image) : m_coord(coord), m_image(image)
{
	
}

void Block::setCoord(qint16 coord)
{
	m_coord = coord;
}

qint16 Block::getCoord()
{
	return m_coord;
}

void Block::setImage(QImage *image)
{
	m_image = std::make_unique<QImage>(image);
}

QImage *Block::getImage()
{
	return m_image.get();
}

QPair<qint16, QImage *> Block::getBlock()
{
	return {m_coord, m_image.get()};
}
