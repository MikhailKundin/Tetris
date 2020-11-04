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
class SaveResultsWgt;

namespace Ui {
class SingleWgt;
}

class SingleWgt : public WidgetInfo
{
	Q_OBJECT
	
public:
	explicit SingleWgt(QPair<QPixmap *, QPixmap *> buttonImg, QWidget *parent = nullptr);
	~SingleWgt() override;
	
signals:
	void savedSignal();
	
public slots:
	void updateGrid(const QMap<qint16, QImage *> &grid) const;
	void updatePoints(quint32 points);
	void updateLevel(quint16 level);
	void updateFigure(AbstractFigure *&figure);
	void saveResult();
	void restart();
	
private slots:
	void saveBtnPush(QString name);
	
private:
	void resizeEvent(QResizeEvent *e) override;
	void moveSaveResults();
	
	QSize screenSize;
	
	Ui::SingleWgt *ui;
	
	std::unique_ptr<PlaygroundPnl> pg;
	std::unique_ptr<PointsPnl> pointsPnl;
	std::unique_ptr<RecordTablePnl> rtPnl;
	std::unique_ptr<LevelFigurePnl> lfPnl;
	
	std::unique_ptr<SaveResultsWgt> saveResultsWgt;
	
	std::unique_ptr<QLabel> rightTopLbl;
};

#endif // SINGLEWGT_H
