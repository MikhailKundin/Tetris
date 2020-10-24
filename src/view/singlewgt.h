#ifndef SINGLEWGT_H
#define SINGLEWGT_H

#include <QWidget>

#include "playground.h"
#include "pointswgt.h"
#include "recordtable.h"

namespace Ui {
class SingleWgt;
}

class SingleWgt : public QWidget
{
	Q_OBJECT
	
public:
	explicit SingleWgt(qint8 row, qint8 column, QWidget *parent = nullptr);
	~SingleWgt() override;
	
public slots:
	void update(const QMap<qint16, QImage *> &grid) const;
	
private:
	
	Ui::SingleWgt *ui;
	
	std::unique_ptr<Playground> pg;
	std::unique_ptr<PointsWgt> pointsWgt;
	std::unique_ptr<RecordTable> rtWgt;
	
	const qint32 POINTS_HEIGHT = 50;
};

#endif // SINGLEWGT_H
