#ifndef GENERALCONTROLLER_H
#define GENERALCONTROLLER_H

#include <QObject>
#include <QMap>

#include "../model/abstractfigure.h"

class GeneralController
{
	Q_OBJECT
public:
	GeneralController();
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
	
private:
	const QImage *IBlock;
	const QImage *OBlock;
	const QImage *TBlock;
	const QImage *LBlock;
	const QImage *JBlock;
	const QImage *SBlock;
	const QImage *ZBlock;
	
	QTimer *timer;
	
	QMap<qint16, QImage *> map;
};

#endif // GENERALCONTROLLER_H
