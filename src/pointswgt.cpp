#include "pointswgt.h"
#include "ui_pointswgt.h"

PointsWgt::PointsWgt(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PointsWgt)
{
	ui->setupUi(this);
}

PointsWgt::~PointsWgt()
{
	delete ui;
}
