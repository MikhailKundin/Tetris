#ifndef SINGLEWGT_H
#define SINGLEWGT_H

#include <QWidget>

#include "playground.h"
#include "pointswgt.h"
#include "recordtable.h"

namespace Ui {
class SingleWgt;
}

class SingleWgt : public QWidget
{
	Q_OBJECT
	
public:
	explicit SingleWgt(QWidget *parent = nullptr);
	~SingleWgt();
	
private:
	Ui::SingleWgt *ui;
	
	std::unique_ptr<Playground> pg;
	std::unique_ptr<PointsWgt> pointsWgt;
	std::unique_ptr<RecordTable> rtWgt;
};

#endif // SINGLEWGT_H
