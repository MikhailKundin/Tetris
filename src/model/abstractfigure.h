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
	virtual QList<QPair<qint8, qint8> > rotateUpRight(qint8 mult) const = 0;
	virtual QList<QPair<qint8, qint8> > rotateRightDown(qint8 mult) const = 0;
	virtual QList<QPair<qint8, qint8> > rotateDownLeft(qint8 mult) const = 0;
	virtual QList<QPair<qint8, qint8> > rotateLeftUp(qint8 mult) const = 0;
	
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
	QList<QPair<qint8, qint8> > rotateUpRight(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateRightDown(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateDownLeft(qint8 mult) const override;
	QList<QPair<qint8, qint8> > rotateLeftUp(qint8 mult) const override;
};

#endif // ABSTARCTFIGURE_H
