#ifndef LEVELPNL_H
#define LEVELPNL_H

#include <QWidget>

class QLabel;

namespace Ui {
class LevelPnl;
}

class LevelPnl : public QWidget
{
public:
	explicit LevelPnl(quint16 nextFigureWidth, quint16 pointsHeight, qreal mult, QWidget *parent = nullptr);
	~LevelPnl();
	void setLevel(quint16 level);
	
private:
	Ui::LevelPnl *ui;
	
	std::unique_ptr<QLabel> back;
	
	const quint8 BASE_FONT_SIZE = 20;
};

#endif // LEVELPNL_H
