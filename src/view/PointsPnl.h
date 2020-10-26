#ifndef POINTSWGT_H
#define POINTSWGT_H

#include <QWidget>

namespace Ui {
class PointsWgt;
}

class PointsPnl : public QWidget
{
	Q_OBJECT
	
public:
	explicit PointsPnl(QSize s, QWidget *parent = nullptr);
	~PointsPnl();
	
	void update(qint32 points);
	
private:
	Ui::PointsWgt *ui;
};

#endif // POINTSWGT_H
