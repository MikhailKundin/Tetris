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
	GeneralController(QMap<qint8, QImage *> &blocks);
	virtual ~GeneralController();
	void setPoints(qint32 points);
	qint32 getPoints();
	QMap<qint16, QImage *> &getGrid();
	
public slots:
	void moveRight();
	void moveLeft();
	void rotate();
	void moveDown();
	
	void newTick();
	void restart();
	void stop();
	void deleteController();
	
signals:
	void update(QMap<qint16, QImage *> &);
	
	void moveRightSignal();
	void moveLeftSignal();
	void rotateSignal();
	void moveDownSignal();
	void defeatSignal();
	void newPointsSignal(qint32 points);
	void newLevelSignal(qint16 level);
	void newFigureSignal(qint8 thirdFigure);
	
private:
	void figureFall();
	void getNextFigure();
	bool isRowFull(qint8 rowNumber);
	void deleteRow(qint8 rowNumber);
	void shiftRows(qint8 bottomRow, qint8 count);
	bool isObstacle(QList<qint16> cells);
	bool isLayerOverflow(QList<qint16> cells);
	void addFigure(QList<qint16> cells);
	void deleteFigure(QList<qint16> cells);
	void checkRows(QList<qint16> cells, qint8 &topRow_out, qint8 &rowCount_out);
	void addPoints(qint32 count);
	bool isNegativeCoords(QList<qint16> cells);
	
	QMap<qint8, QImage *> m_blocks;
	
	QMap<qint16, QImage *> grid;
	AbstractFigure *figure;
	AbstractFigure *nextFigure;
	qint8 thirdFigure;
	qint32 m_points = 0;
	qint16 level = 1;
	QRandomGenerator random;
	
	bool m_stop = false;
	
	const quint16 POINTS[4] = {100, 300, 700, 1500};
	const quint16 NEW_LEVEL = 3000;
};

#endif // GENERALCONTROLLER_H
