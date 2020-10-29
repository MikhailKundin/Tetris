#ifndef LEVELFIGUREPNL_H
#define LEVELFIGUREPNL_H

#include <QWidget>

#include "LevelPnl.h"
#include "NextFigurePnl.h"

namespace Ui {
class LevelFigurePnl;
}

class LevelFigurePnl : public QWidget
{
	Q_OBJECT
	
public:
	explicit LevelFigurePnl(qint16 pointsHeight, qint8 blockSize, QWidget *parent = nullptr);
	~LevelFigurePnl() override;
	
	void setLevel(qint16 level);
	void setFigure(AbstractFigure *&figure);
	
private:
	Ui::LevelFigurePnl *ui;
	
	void paintEvent(QPaintEvent *e) override;
	
	std::unique_ptr<NextFigurePnl> nextFigurePnl;
	std::unique_ptr<LevelPnl> levelPnl;
	std::unique_ptr<QPixmap> img;
	std::unique_ptr<QLabel> yellowLbl;
};

#endif // LEVELFIGUREPNL_H
