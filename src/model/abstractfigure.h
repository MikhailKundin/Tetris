#ifndef ABSTARCTFIGURE_H
#define ABSTARCTFIGURE_H

#include "block.h"

class AbstractFigure
{
	
public:
	AbstractFigure(qint8 row, qint8 column);
	virtual ~AbstractFigure() = default;
	
	virtual bool moveRight();
	virtual bool moveLeft();
	virtual bool moveDown();
	virtual bool moveUp();
	virtual bool rotate();
	virtual bool backRotate();
	
	QList<Block> &getBlocks();
	QList<qint16> getCoords();
	QImage *getImage();
	
protected:
	virtual QList<QPair<qint8, qint8> > rotateUpRight(qint8 mult) = 0;
	virtual QList<QPair<qint8, qint8> > rotateRightDown(qint8 mult) = 0;
	virtual QList<QPair<qint8, qint8> > rotateDownLeft(qint8 mult) = 0;
	virtual QList<QPair<qint8, qint8> > rotateLeftUp(qint8 mult) = 0;
	
	QPair<qint8, qint8> getPairCoord(qint16 singleCoord);
	qint16 getSingleCoord(QPair<qint8, qint8> pairCoord);
	void updateCoords(QList<QPair<qint8, qint8> > pairCoords);
	bool isOutOfBounds(QList<QPair<qint8, qint8> > coords);
	
	QList<Block> blocks;
	
	enum Rotation {up, down, left, right};
	Rotation rotation = up;
	
	const qint8 ROW_COUNT;
	const qint8 COLUMN_COUNT;
};

class IFigure : public AbstractFigure
{
public:
	IFigure(qint8 row, qint8 column, QImage *image);
	
private:
	QList<QPair<qint8, qint8> > rotateUpRight(qint8 mult) override;
	QList<QPair<qint8, qint8> > rotateRightDown(qint8 mult) override;
	QList<QPair<qint8, qint8> > rotateDownLeft(qint8 mult) override;
	QList<QPair<qint8, qint8> > rotateLeftUp(qint8 mult) override;
};

#endif // ABSTARCTFIGURE_H
