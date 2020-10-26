#ifndef BLOCK_H
#define BLOCK_H

#include <QImage>

class Block
{
public:
	Block(qint16 cell, QImage *image);
	
	void setCell(qint16 cell);
	qint16 getCell() const;
	
	QImage *getImage() const;
	
private:
	qint16 m_cell;
	QImage *m_image;
};

#endif // BLOCK_H
