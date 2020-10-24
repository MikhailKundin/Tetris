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
	GeneralController(qint8 row, qint8 column, QMap<qint8, QImage *> &blocks);
	virtual ~GeneralController();
	void setPoints(qint32 points);
	qint32 getPoints();
	QMap<qint16, QImage *> &getGrid();
	
	enum Figures {I, O, T, L, J, S, Z};
	
public slots:
	void moveRight();
	void moveLeft();
	void rotate();
	void moveDown();
	
private slots:
	void tick();
	
signals:
	void update(QMap<qint16, QImage *> &);
	
	void moveRightSignal();
	void moveLeftSignal();
	void rotateSignal();
	void moveDownSignal();
	void tickSignal();
	void defeatSignal(GeneralController *controller);
	void newPointsSignal(qint32 points);
	void newLevelSignal(qint16 level);
	void newFigureSignal(qint8 thirdFigure);
	
private:
	QPair<qint8, qint8> getCoord(qint16 cell);
	qint16 getCell(QPair<qint8, qint8> coord);
	
	void getNextFigure();
	bool isRowFull(qint8 rowNumber);
	void deleteRow(qint8 rowNumber);
	void shiftRows(qint8 bottomRow, qint8 count);
	bool isObstacle(QList<qint16> cells);
	bool isLayerOverflow(QList<qint16> cells);
	void addFigure(QList<qint16> cells);
	void deleteFigure(QList<qint16> cells);
	void checkRows(QList<qint16> cells);
	void addPoints(qint32 count);
	void setTimerInterval();
	bool isNegativeCoords(QList<qint16> cells);
	
	QMap<qint8, QImage *> m_blocks;
	
	std::unique_ptr<QTimer> timer;
	QMap<qint16, QImage *> grid;
	AbstractFigure *figure;
	AbstractFigure *nextFigure;
	qint8 thirdFigure;
	qint32 m_points = 0;
	qint16 level = 1;
	QRandomGenerator random;
	
	const qint8 ROW_COUNT;
	const qint8 COLUMN_COUNT;
	const quint16 POINTS[4] = {100, 300, 700, 1500};
	const quint16 NEW_LEVEL = 3000;
	const qint16 START_INTERVAL = 1000;
	const qreal INTERVAL_DIV = 2;
	const qint16 MIN_INTERVAL = 1;
};

#endif // GENERALCONTROLLER_H
