#ifndef SAVERESULTSWGT_H
#define SAVERESULTSWGT_H

#include <QWidget>

class QLabel;

namespace Ui {
class SaveResultsWgt;
}

class SaveResultsWgt : public QWidget
{
	Q_OBJECT
	
public:
	explicit SaveResultsWgt(qreal mult, QWidget *parent = nullptr);
	~SaveResultsWgt();
	
signals:
	void saveResult(QString name);
	
public slots:
	void activate();
	
private slots:
	void cancelBtnPush();
	void saveBtnPush();
	
private:
	Ui::SaveResultsWgt *ui;
	
	quint16 ELEMENT_HEIGHT;
	quint16 ELEMENT_WIDTH;
	quint16 BORDER;
	
	const quint16 BASE_HEIGHT = 200;
	const quint16 BASE_WEIGHT = 200;
	const quint16 BASE_ELEMENT_HEIGHT = 30;
	const quint16 BASE_ELEMENT_WIDTH = 180;
	const quint16 BASE_BORDER = 10;
	const quint8 BASE_FONT = 20;
};

#endif // SAVERESULTSWGT_H
