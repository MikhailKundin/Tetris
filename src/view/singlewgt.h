#ifndef SINGLEWGT_H
#define SINGLEWGT_H

#include <QWidget>

#include "PlaygroundPnl.h"
#include "PointsPnl.h"
#include "RecordTablePnl.h"
#include "LevelFigurePnl.h"

namespace Ui {
class SingleWgt;
}

class SingleWgt : public QWidget
{
	Q_OBJECT
	
public:
	explicit SingleWgt(qint8 blockSize, QWidget *parent = nullptr);
	~SingleWgt() override;
	
public slots:
	void updateGrid(const QMap<qint16, QImage *> &grid) const;
	void updatePoints(qint32 points);
	void updateLevel(qint16 level);
	void updateFigure(AbstractFigure *&figure);
	
private:
	
	Ui::SingleWgt *ui;
	
	std::unique_ptr<PlaygroundPnl> pg;
	std::unique_ptr<PointsPnl> pointsPnl;
	std::unique_ptr<RecordTablePnl> rtPnl;
	std::unique_ptr<LevelFigurePnl> lfPnl;
	
	std::unique_ptr<QLabel> rightTopLbl;
	
	const qint32 POINTS_HEIGHT = 50;
	const qint32 RECORD_WIDTH = 150;
	const qint8 BLOCK_SIZE;
};

#endif // SINGLEWGT_H
