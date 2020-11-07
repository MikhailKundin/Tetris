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
class ButtonPanel;

namespace Ui {
class SingleWgt;
}

class SingleWgt : public WidgetInfo
{
	Q_OBJECT
	
public:
	explicit SingleWgt(QWidget *parent = nullptr);
	~SingleWgt() override;
	
signals:
	void exitSignal();
	void restartSignal();
	void pauseSignal();
	void resumeSignal();
	
	void wgtResize();
	
public slots:
	void updateGrid(const QMap<qint16, QImage *> &grid) const;
	void updatePoints(quint32 points);
	void updateLevel(quint16 level);
	void updateFigure(AbstractFigure *&figure);
	
	void pauseBtnPress();
	void restart();
	void defeat();
	
private slots:
	void saveBtnPush(QString name);
	void buttonsFilter(QString objName);
	
private:
	void resizeEvent(QResizeEvent *e) override;
	void createDefeatPanel();
	
	QSize screenSize;
	
	Ui::SingleWgt *ui;
	
	std::unique_ptr<PlaygroundPnl> pg;
	std::unique_ptr<PointsPnl> pointsPnl;
	std::unique_ptr<RecordTablePnl> rtPnl;
	std::unique_ptr<LevelFigurePnl> lfPnl;
	
	std::unique_ptr<ButtonPanel> pauseWgt;
	const QList<QString> pauseButtons = {"Продолжить", "Перезапуск", "Выход"};
	const QList<QString> defeatButtons = {"Перезапуск", "Выход"};
	const QString DEFEAT_NAME = "defeatPanel";
	const QString PAUSE_NAME = "pausePanel";
	bool blockPause = false;
	
	std::unique_ptr<QLabel> rightTopLbl;
};

#endif // SINGLEWGT_H
