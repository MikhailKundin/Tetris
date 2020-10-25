#ifndef BLOCK_H
#define BLOCK_H

#include <QImage>

class Block
{
public:
	Block();
	Block(qint16 cell, QImage *image);
	
	void setCell(qint16 cell);
	qint16 getCell() const;
	
	void setImage(QImage *image);
	QImage *getImage() const;
	
	QPair<qint16, QImage *> getBlock() const;
	
private:
	qint16 m_cell;
	QImage *m_image;
};

#endif // BLOCK_H
