#ifndef GENERALCONTROLLER_H
#define GENERALCONTROLLER_H

#include <QObject>
#include <QMap>
#include <QRandomGenerator>

#include "../model/abstractfigure.h"

class GeneralController : public QObject
{
	Q_OBJECT
public:
	GeneralController(qint8 row, qint8 column);
	virtual ~GeneralController();
	
public slots:
	void moveRight();
	void moveLeft();
	void rotate();
	void moveDown();
	
private slots:
	void tick();
	
signals:
	void update();
	
	void moveRightSignal();
	void moveLeftSignal();
	void rotateSignal();
	void moveDownSignal();
	
private:
	void getNextFigure();
	
	QImage *IBlock;
	QImage *OBlock;
	QImage *TBlock;
	QImage *LBlock;
	QImage *JBlock;
	QImage *SBlock;
	QImage *ZBlock;
	
	QTimer *timer;
	QMap<qint16, QImage *> map;
	AbstractFigure *figure;
	AbstractFigure *nextFigure;
	qint32 points = 0;
	qint16 level = 1;
	QRandomGenerator random;
	
	const qint8 ROW_COUNT;
	const qint8 COLUMN_COUNT;
};

#endif // GENERALCONTROLLER_H
