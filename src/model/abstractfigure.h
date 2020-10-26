#ifndef ABSTARCTFIGURE_H
#define ABSTARCTFIGURE_H

#include "Block.h"

class AbstractFigure
{
	
public:
	virtual ~AbstractFigure() = default;
	
	virtual bool moveRight();
	virtual bool moveLeft();
	virtual bool moveDown();
	virtual bool moveUp();
	virtual bool rotate();
	virtual bool backRotate();
	
	QList<Block> &getBlocks();
	QList<qint16> getCells();
	QImage *getImage();
	
protected:
	virtual QList<QPair<qint8, qint8> > rotateUpRight(qint8 mult) = 0;
	virtual QList<QPair<qint8, qint8> > rotateRightDown(qint8 mult) = 0;
	virtual QList<QPair<qint8, qint8> > rotateDownLeft(qint8 mult) = 0;
	virtual QList<QPair<qint8, qint8> > rotateLeftUp(qint8 mult) = 0;
	
	void updateCoords(QList<QPair<qint8, qint8> > coords);
	bool isOutOfBounds(QList<QPair<qint8, qint8> > coords);
	
	QList<Block> blocks;
	
	enum Rotation {up, down, left, right};
	enum Direction : qint8 {forward = 1, backward = -1};
	
	qint8 rotation = up;
};

class IFigure : public AbstractFigure
{
public:
	IFigure(QImage *image);
	
private:
	QList<QPair<qint8, qint8> > rotateUpRight(qint8 mult) override;
	QList<QPair<qint8, qint8> > rotateRightDown(qint8 mult) override;
	QList<QPair<qint8, qint8> > rotateDownLeft(qint8 mult) override;
	QList<QPair<qint8, qint8> > rotateLeftUp(qint8 mult) override;
};

#endif // ABSTARCTFIGURE_H
