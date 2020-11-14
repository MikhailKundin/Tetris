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
	
	void getNextFigure(quint8 figure);
	
	void newTick();
	void restart();
	void stop();
	void start();
	
	void clearFigure();
	
signals:
	void update(QMap<qint16, QImage *> &);
	
	void newPointsSignal(quint32 points);
	void newLevelSignal(quint16 level);
	void newFigureSignal(AbstractFigure *&secondFigure);
	void getNewFigureSignal();
	void readyToStart();
	void moveDownSignal();
	void defeatSignal();
	
private:
	void figureFall();
	bool isRowFull(qint8 rowNumber) const;
	void deleteRow(qint8 rowNumber);
	void shiftRow(qint8 rowNumber);
	bool isObstacle(const QList<qint16> &cells) const;
	bool isLayerOverflow(const QList<qint16> &cells) const;
	void addFigure(const QList<qint16> &cells);
	void deleteFigure(const QList<qint16> &cells);
	void checkRows(QList<qint16> &cells);
	void addPoints(quint32 count);
	bool isNegativeCoords(const QList<qint16> &cells) const;
	void startGame();
	
	QMap<qint8, QImage *> m_blocks;
	
	QMap<qint16, QImage *> grid;
	AbstractFigure *figure = nullptr;
	AbstractFigure *secondFigure = nullptr;
	quint32 m_points = 0;
	quint16 level = 1;
	
	bool m_stop = false;
	bool isReadyToStart = false;
	
	const quint16 POINTS[4] = {100, 300, 700, 1500};
	const quint16 NEW_LEVEL = 3000;
};

#endif // GENERALCONTROLLER_H
