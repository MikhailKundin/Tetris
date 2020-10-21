#ifndef ABSTARCTFIGURE_H
#define ABSTARCTFIGURE_H

#include "block.h"

class AbstractFigure
{
	
public:
	AbstractFigure(qint16 row, qint16 column);
	virtual ~AbstractFigure() = default;
	
	virtual void moveRight();
	virtual void moveLeft();
	virtual void moveDown();
	virtual void moveUp();
	virtual void rotate() = 0;
	virtual void backRotate() = 0;
	
	QList<Block> getBlocks();
	
protected:
	QPair<qint16, qint16> getPairCoord(qint16 singleCoord);
	qint16 getSingleCoord(QPair<qint16, qint16> pairCoord);
	
	QList<Block> blocks;
	
	enum Rotation {up, down, left, right};
	Rotation rotation = up;
	
	qint16 ROW_COUNT;
	qint16 COLUMN_COUNT;
};

class IFigure : public AbstractFigure
{
public:
	IFigure(qint16 row, qint16 column, QImage *image);
	
	virtual void rotate();
	virtual void backRotate();
};

class OFigure : public AbstractFigure
{
public:
	OFigure(qint16 row, qint16 column, QImage *image);
	
	virtual void rotate();
	virtual void backRotate();
};

class TFigure : public AbstractFigure
{
public:
	TFigure(qint16 row, qint16 column, QImage *image);
	
	virtual void rotate();
	virtual void backRotate();
};

class LFigure : public AbstractFigure
{
public:
	LFigure(qint16 row, qint16 column, QImage *image);
	
	virtual void rotate();
	virtual void backRotate();
};

class JFigure : public AbstractFigure
{
public:
	JFigure(qint16 row, qint16 column, QImage *image);
	
	virtual void rotate();
	virtual void backRotate();
};

class SFigure : public AbstractFigure
{
public:
	SFigure(qint16 row, qint16 column, QImage *image);
	
	virtual void rotate();
	virtual void backRotate();
};

class ZFigure : public AbstractFigure
{
public:
	ZFigure(qint16 row, qint16 column, QImage *image);
	
	virtual void rotate();
	virtual void backRotate();
};

#endif // ABSTARCTFIGURE_H
