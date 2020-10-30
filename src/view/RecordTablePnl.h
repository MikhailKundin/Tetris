#ifndef RECORDTABLE_H
#define RECORDTABLE_H

#include <QWidget>
#include "../Database.h"

class QLabel;
class QGridLayout;

class RecordTablePnl : public QWidget
{
public:
	RecordTablePnl(quint16 height, qreal mult, QWidget *parent = nullptr);
	~RecordTablePnl();
	
	void updateRecordTable(quint32 newPoints);
	void saveResult(const QString &name);
	
private:
	std::unique_ptr<QGridLayout> gBox;
	QList<QLabel *> names;
	QList<QLabel *> points;
	std::unique_ptr<QLabel> topSpaceLbl;
	std::unique_ptr<QLabel> bottomSpaceLbl;
	std::unique_ptr<QLabel> backLbl;
	
	quint8 place = 10;
	Database db;
	
	const quint8 TOP_SPACE = 30;
	const quint8 BOTTOM_SPACE = 15;
	const quint8 BASE_FONT_SIZE = 14;
	const quint16 WIDTH = 190;
	const quint8 MARIGN = 25;
	const quint8 ROW_HEIGHT = 100;
};

#endif // RECORDTABLE_H
