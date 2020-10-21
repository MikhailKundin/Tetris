#ifndef BLOCK_H
#define BLOCK_H

#include <QImage>

class Block
{
public:
	Block();
	Block(qint16 coord, QImage *image);
	~Block();
	
	void setCoord(qint16 coord);
	qint16 getCoord() const;
	
	void setImage(QImage *image);
	QImage *getImage() const;
	
	QPair<qint16, QImage *> getBlock() const;
	
private:
	qint16 m_coord;
	QImage *m_image;
};

#endif // BLOCK_H
