#ifndef GENERALCONTROLLER_H
#define GENERALCONTROLLER_H

#include <QObject>
#include <QMap>

#include "../AbstractFigure.h"

class GeneralController : public QObject
{
	Q_OBJECT
	
public:
	GeneralController(QMap<qint8, QImage *> &blocks);
	virtual ~GeneralController();
	void setPoints(quint32 points);
	quint32 getPoints() const;
	const QMap<qint16, QImage *> &getGrid() const;
	
public slots:
	void moveRight();
	void moveLeft();
	void rotate();
	void moveDown();
	
	void setThirdFigure(qint8 figure);
	
	void newTick();
	void restart();
	void stop();
	void start();
	void deleteController();
	
signals:
	void update(QMap<qint16, QImage *> &);
	
	void moveRightSignal();
	void moveLeftSignal();
	void rotateSignal();
	void moveDownSignal();
	void defeatSignal();
	void newPointsSignal(quint32 points);
	void newLevelSignal(quint16 level);
	void newFigureSignal(AbstractFigure *&secondFigure);
	
private:
	void figureFall();
	void getNextFigure();
	bool isRowFull(qint8 rowNumber) const;
	void deleteRow(qint8 rowNumber);
	void shiftRows(qint8 bottomRow, qint8 count);
	bool isObstacle(const QList<qint16> &cells) const;
	bool isLayerOverflow(const QList<qint16> &cells) const;
	void addFigure(const QList<qint16> &cells);
	void deleteFigure(const QList<qint16> &cells);
	void checkRows(const QList<qint16> &cells, qint8 &topRow_out, qint8 &rowCount_out);
	void addPoints(quint32 count);
	bool isNegativeCoords(const QList<qint16> &cells) const;
	
	QMap<qint8, QImage *> m_blocks;
	
	QMap<qint16, QImage *> grid;
	AbstractFigure *figure;
	AbstractFigure *secondFigure;
	qint8 thirdFigure = 0;
	quint32 m_points = 0;
	quint16 level = 1;
	
	bool m_stop = false;
	
	const quint16 POINTS[4] = {100, 300, 700, 1500};
	const quint16 NEW_LEVEL = 3000;
};

#endif // GENERALCONTROLLER_H
