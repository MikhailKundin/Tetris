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
	virtual bool rotate() = 0;
	virtual bool backRotate() = 0;
	
	QList<QPair<qint16, QImage *> > getBlocks();
	
protected:
	QPair<qint16, qint16> getPairCoord(qint16 singleCoord);
	qint16 getSingleCoord(QPair<qint16, qint16> pairCoord);
	bool checkPosition();
	
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
	
	virtual bool rotate() override;
	virtual bool backRotate() override;
};

class OFigure : public AbstractFigure
{
public:
	OFigure(qint8 row, qint8 column, QImage *image);
	
	virtual bool rotate() override;
	virtual bool backRotate() override;
};

class TFigure : public AbstractFigure
{
public:
	TFigure(qint8 row, qint8 column, QImage *image);
	
	virtual bool rotate() override;
	virtual bool backRotate() override;
};

class LFigure : public AbstractFigure
{
public:
	LFigure(qint8 row, qint8 column, QImage *image);
	
	virtual bool rotate() override;
	virtual bool backRotate() override;
};

class JFigure : public AbstractFigure
{
public:
	JFigure(qint8 row, qint8 column, QImage *image);
	
	virtual bool rotate() override;
	virtual bool backRotate() override;
};

class SFigure : public AbstractFigure
{
public:
	SFigure(qint8 row, qint8 column, QImage *image);
	
	virtual bool rotate() override;
	virtual bool backRotate() override;
};

class ZFigure : public AbstractFigure
{
public:
	ZFigure(qint8 row, qint8 column, QImage *image);
	
	virtual bool rotate() override;
	virtual bool backRotate() override;
};

#endif // ABSTARCTFIGURE_H
