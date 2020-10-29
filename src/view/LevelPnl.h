#ifndef LEVELPNL_H
#define LEVELPNL_H

#include <QWidget>

class QLabel;

namespace Ui {
class LevelPnl;
}

class LevelPnl : public QWidget
{
	Q_OBJECT
	
public:
	explicit LevelPnl(qint16 nextFigureWidth, qint16 pointsHeight, qreal mult, QWidget *parent = nullptr);
	~LevelPnl();
	void setLevel(qint16 level);
	
private:
	Ui::LevelPnl *ui;
	
	std::unique_ptr<QLabel> back;
	
	const quint8 BASE_FONT_SIZE = 20;
};

#endif // LEVELPNL_H
