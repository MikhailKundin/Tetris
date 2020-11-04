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
	explicit PointsPnl(quint16 width, qreal mult, QWidget *parent = nullptr);
	~PointsPnl();
	
	void update(quint32 points);
	quint32 getPoints() const;
	
private:
	Ui::PointsWgt *ui;
	
	const quint8 HEIGHT = 50;
	const quint8 BASE_FONT_SIZE = 20;
};

#endif // POINTSWGT_H
