#ifndef RECORDTABLE_H
#define RECORDTABLE_H

#include <QWidget>

namespace Ui {
class RecordTable;
}

class RecordTable : public QWidget
{
	Q_OBJECT
	
public:
	explicit RecordTable(QWidget *parent = nullptr);
	~RecordTable();
	
private:
	Ui::RecordTable *ui;
};

#endif // RECORDTABLE_H
