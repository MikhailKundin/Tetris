#ifndef SINGLEWGT_H
#define SINGLEWGT_H

#include <QWidget>

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
};

#endif // SINGLEWGT_H
