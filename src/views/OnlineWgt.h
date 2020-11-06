#ifndef ONLINEWGT_H
#define ONLINEWGT_H

#include "WidgetInfo.h"

class PlaygroundPnl;
class PointsPnl;
class RecordTablePnl;
class LevelFigurePnl;
class AbstractFigure;
class QLabel;
class SaveResultsWgt;
class SingleExitWgt;

namespace Ui {
class OnlineWgt;
}

class OnlineWgt : public WidgetInfo
{
	Q_OBJECT
	
public:
	explicit OnlineWgt(QPair<QPixmap *, QPixmap *> buttonImg, QWidget *parent = nullptr);
	~OnlineWgt();
	
public slots:
	void ofUpdateGrid(const QMap<qint16, QImage *> &grid) const;
	void ofUpdatePoints(quint32 points);
	void ofUpdateLevel(quint16 level);
	void ofUpdateFigure(AbstractFigure *&figure);
	
	void onUpdateGrid(const QMap<qint16, QImage *> &grid) const;
	void onUpdatePoints(quint32 points);
	void onUpdateLevel(quint16 level);
	void onUpdateFigure(AbstractFigure *&figure);
	
private:
	Ui::OnlineWgt *ui;
	
	std::unique_ptr<PlaygroundPnl> ofPg;
	std::unique_ptr<PointsPnl> ofPoints;
	std::unique_ptr<LevelFigurePnl> ofLevelFigure;
	
	std::unique_ptr<PlaygroundPnl> onPg;
	std::unique_ptr<PointsPnl> onPoints;
	std::unique_ptr<LevelFigurePnl> onLevelFigure;
	
	std::unique_ptr<QLabel> yellow;
	std::unique_ptr<QLabel> topYellow;
	
	const quint16 BASE_YELLOW_WIDTH = 100;
};

#endif // ONLINEWGT_H
