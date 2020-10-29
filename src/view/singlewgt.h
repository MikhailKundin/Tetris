#ifndef SINGLEWGT_H
#define SINGLEWGT_H

#include <QWidget>

#include "WidgetInfo.h"

class PlaygroundPnl;
class PointsPnl;
class RecordTablePnl;
class LevelFigurePnl;
class AbstractFigure;
class QLabel;

namespace Ui {
class SingleWgt;
}

class SingleWgt : public WidgetInfo
{
	Q_OBJECT
	
public:
	explicit SingleWgt(QWidget *parent = nullptr);
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
};

#endif // SINGLEWGT_H
