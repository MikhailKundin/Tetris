#include "singlewgt.h"
#include "ui_singlewgt.h"

SingleWgt::SingleWgt(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SingleWgt)
{
	ui->setupUi(this);
}

SingleWgt::~SingleWgt()
{
	delete ui;
}
