#ifndef POINTSWGT_H
#define POINTSWGT_H

#include <QWidget>

namespace Ui {
class PointsWgt;
}

class PointsWgt : public QWidget
{
	Q_OBJECT
	
public:
	explicit PointsWgt(QSize s, QWidget *parent = nullptr);
	~PointsWgt();
	
	void update(qint32 points);
	
private:
	Ui::PointsWgt *ui;
};

#endif // POINTSWGT_H
