#ifndef RECORDTABLE_H
#define RECORDTABLE_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

class RecordTablePnl : public QWidget
{
public:
	RecordTablePnl(QSize s, QWidget *parent = nullptr);
	~RecordTablePnl();
	
	void test(qint8 bs);
	
private:
	std::unique_ptr<QGridLayout> gBox;
	QList<QLabel *> names;
	QList<QLabel *> points;
	std::unique_ptr<QLabel> topSpaceLbl;
	std::unique_ptr<QLabel> bottomSpaceLbl;
	std::unique_ptr<QLabel> backLbl;
	
	const qint16 TOP_SPACE = 30;
	const qint16 BOTTOM_SPACE = 30;
	const qint16 CELL_HEIGHT = 30;
};

#endif // RECORDTABLE_H
