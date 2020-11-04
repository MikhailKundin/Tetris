#ifndef SINGLEEXITWGT_H
#define SINGLEEXITWGT_H

#include <QWidget>

class PushLabel;

namespace Ui {
class SingleExitWgt;
}

class SingleExitWgt : public QWidget
{
	Q_OBJECT
	
public:
	explicit SingleExitWgt(QPair<QPixmap *, QPixmap *> buttonImg, qreal mult, QWidget *parent = nullptr);
	~SingleExitWgt();
	
public slots:
	void activate(bool state);
	
private slots:
	void restartBtnPush();
	void exitBtnPush();
	
signals:
	void restartSignal();
	void exitSignal();
	
private:
	Ui::SingleExitWgt *ui;
	
	std::unique_ptr<PushLabel> restartBtn;
	std::unique_ptr<PushLabel> exitBtn;
	
	quint16 ELEMENT_HEIGHT;
	quint16 ELEMENT_WIDTH;
	quint16 BORDER;
	
	const quint16 BASE_HEIGHT = 100;
	const quint16 BASE_WEIGHT = 200;
	const quint16 BASE_ELEMENT_HEIGHT = 30;
	const quint16 BASE_ELEMENT_WIDTH = 180;
	const quint16 BASE_BORDER = 10;
	const quint8 BASE_FONT = 20;
	const qreal MULT;
};

#endif // SINGLEEXITWGT_H
