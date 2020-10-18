#include "recordtable.h"
#include "ui_recordtable.h"

RecordTable::RecordTable(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::RecordTable)
{
	ui->setupUi(this);
}

RecordTable::~RecordTable()
{
	delete ui;
}
