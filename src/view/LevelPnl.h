#ifndef LEVELPNL_H
#define LEVELPNL_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class LevelPnl;
}

class LevelPnl : public QWidget
{
	Q_OBJECT
	
public:
	explicit LevelPnl(qint16 nextFigureWidth, qint16 pointsHeight, QWidget *parent = nullptr);
	~LevelPnl();
	void setLevel(qint16 level);
	
private:
	Ui::LevelPnl *ui;
	
	std::unique_ptr<QLabel> back;
};

#endif // LEVELPNL_H
