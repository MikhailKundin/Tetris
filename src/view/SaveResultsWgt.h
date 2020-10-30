#ifndef SAVERESULTSWGT_H
#define SAVERESULTSWGT_H

#include <QWidget>

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
	
	const quint16 BASE_HEIGHT = 200;
	const quint16 BASE_WEIGHT = 200;
};

#endif // SAVERESULTSWGT_H
