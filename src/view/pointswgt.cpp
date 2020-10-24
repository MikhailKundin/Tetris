#include "pointswgt.h"
#include "ui_pointswgt.h"

#include <QDebug>

PointsWgt::PointsWgt(QSize s, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PointsWgt)
{
	ui->setupUi(this);
	
	//setMinimumSize(width, height);
	//setMaximumSize(width, height);
	resize(s);
	
	QPixmap img(":Images/Backgrounds/NextFigureBackground.png");
	img = img.scaled(s);
	ui->backLbl->setPixmap(img);
	ui->backLbl->resize(size());
	ui->backLbl->move(0, 0);
	setLayout(ui->gridLayout);
}

PointsWgt::~PointsWgt()
{
	delete ui;
}
