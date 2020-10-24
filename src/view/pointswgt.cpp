#include "pointswgt.h"
#include "ui_pointswgt.h"

#include <QDebug>

PointsWgt::PointsWgt(QSize s, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PointsWgt)
{
	ui->setupUi(this);
	
	resize(s);
	
	QPixmap img(":Images/Backgrounds/NextFigureBackground.png");
	ui->backLbl->setPixmap(img.scaled(s));
	ui->backLbl->resize(size());
	ui->backLbl->move(0, 0);
	setLayout(ui->gridLayout);
}

PointsWgt::~PointsWgt()
{
	delete ui;
}

void PointsWgt::update(qint32 points)
{
	ui->pointsLbl->setText(QString::number(points));
}
