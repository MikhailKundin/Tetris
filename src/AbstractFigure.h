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
	
	virtual qint8 getType() const;
	
	const QList<Block> &getBlocks() const;
	QList<qint16> getCells() const;
	QImage *getImage();
	
protected:
	virtual QList<QPair<qint8, qint8> > rotateUpLeft(qint8 mult) const = 0;
	virtual QList<QPair<qint8, qint8> > rotateLeftDown(qint8 mult) const = 0;
	virtual QList<QPair<qint8, qint8> > rotateDownRight(qint8 mult) const = 0;
	virtual QList<QPair<qint8, qint8> > rotateRightUp(qint8 mult) const = 0;
	
	void updateCoords(const QList<QPair<qint8, qint8> > &coords);
	bool isOutOfBounds(const QList<QPair<qint8, qint8> > &coords) const;
	
	enum Rotation {up, down, left, right};
	enum Direction : qint8 {forward = 1, backward = -1};
	
	QList<Block> blocks;
	qint8 rotation = up;
	qint8 type;
};

class IFigure : public AbstractFigure
{
public:
	IFigure(QImage *image);
	
private:
	QList<QPair<qint8, qint8> > rotateUpLeft(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateLeftDown(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateDownRight(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateRightUp(qint8 mult) const override;
};

class OFigure : public AbstractFigure
{
public:
	OFigure(QImage *image);
	
private:
	QList<QPair<qint8, qint8> > rotateUpLeft(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateLeftDown(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateDownRight(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateRightUp(qint8 mult) const override;
};

class TFigure : public AbstractFigure
{
public:
	TFigure(QImage *image);
	
private:
	QList<QPair<qint8, qint8> > rotateUpLeft(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateLeftDown(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateDownRight(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateRightUp(qint8 mult) const override;
};

class LFigure : public AbstractFigure
{
public:
	LFigure(QImage *image);
	
private:
	QList<QPair<qint8, qint8> > rotateUpLeft(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateLeftDown(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateDownRight(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateRightUp(qint8 mult) const override;
};

class JFigure : public AbstractFigure
{
public:
	JFigure(QImage *image);
	
private:
	QList<QPair<qint8, qint8> > rotateUpLeft(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateLeftDown(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateDownRight(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateRightUp(qint8 mult) const override;
};

class SFigure : public AbstractFigure
{
public:
	SFigure(QImage *image);
	
private:
	QList<QPair<qint8, qint8> > rotateUpLeft(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateLeftDown(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateDownRight(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateRightUp(qint8 mult) const override;
};

class ZFigure : public AbstractFigure
{
public:
	ZFigure(QImage *image);
	
private:
	QList<QPair<qint8, qint8> > rotateUpLeft(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateLeftDown(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateDownRight(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateRightUp(qint8 mult) const override;
};

#endif // ABSTARCTFIGURE_H
