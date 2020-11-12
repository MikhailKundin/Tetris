#ifndef LEVELFIGUREPNL_H
#define LEVELFIGUREPNL_H

#include <QWidget>

class LevelPnl;
class NextFigurePnl;
class AbstractFigure;
class QLabel;

namespace Ui {
class LevelFigurePnl;
}

class LevelFigurePnl : public QWidget
{
	Q_OBJECT
	
public:
	explicit LevelFigurePnl(quint16 pointsHeight, quint8 blockSize, qreal mult, QWidget *parent = nullptr);
	~LevelFigurePnl() override;
	
	void setLevel(quint16 level);
	void setFigure(AbstractFigure *&figure);
	void clearFigure();
	
private:
	Ui::LevelFigurePnl *ui;
	
	void resizeEvent(QResizeEvent *e) override;
	
	std::unique_ptr<NextFigurePnl> nextFigurePnl;
	std::unique_ptr<LevelPnl> levelPnl;
	std::unique_ptr<QPixmap> img;
	std::unique_ptr<QLabel> yellowLbl;
};

#endif // LEVELFIGUREPNL_H
