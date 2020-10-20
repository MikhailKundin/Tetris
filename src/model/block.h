#ifndef BLOCK_H
#define BLOCK_H

#include <QImage>

class Block
{
public:
	Block();
	Block(qint16 coord, QImage *image);
	
	void setCoord(qint16 coord);
	qint16 getCoord();
	
	void setImage(QImage *image);
	QImage *getImage();
	
	QPair<qint16, QImage *> getBlock();
	
private:
	qint16 m_coord;
	std::unique_ptr<QImage> m_image;
};

#endif // BLOCK_H
