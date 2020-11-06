#ifndef ONLINEWGT_H
#define ONLINEWGT_H

#include <QWidget>

namespace Ui {
class OnlineWgt;
}

class OnlineWgt : public QWidget
{
	Q_OBJECT
	
public:
	explicit OnlineWgt(QWidget *parent = nullptr);
	~OnlineWgt();
	
private:
	Ui::OnlineWgt *ui;
};

#endif // ONLINEWGT_H
