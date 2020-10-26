#ifndef SINGLEWGT_H
#define SINGLEWGT_H

#include <QWidget>

#include "PlaygroundPnl.h"
#include "PointsPnl.h"
#include "RecordTablePnl.h"

namespace Ui {
class SingleWgt;
}

class SingleWgt : public QWidget
{
	Q_OBJECT
	
public:
	explicit SingleWgt(QWidget *parent = nullptr);
	~SingleWgt() override;
	
public slots:
	void updateGrid(const QMap<qint16, QImage *> &grid) const;
	void updatePoints(qint32 points);
	
private:
	
	Ui::SingleWgt *ui;
	
	std::unique_ptr<PlaygroundPnl> pg;
	std::unique_ptr<PointsPnl> pointsWgt;
	std::unique_ptr<RecordTablePnl> rtWgt;
	
	std::unique_ptr<QLabel> rightTopLbl;
	
	const qint32 POINTS_HEIGHT = 50;
	const qint32 RECORD_WIDTH = 150;
};

#endif // SINGLEWGT_H
