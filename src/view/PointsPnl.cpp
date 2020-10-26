#include "PointsPnl.h"
#include "ui_pointswgt.h"

#include <QDebug>

PointsPnl::PointsPnl(QSize s, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PointsWgt)
{
	ui->setupUi(this);
	
	resize(s);
	
	QPixmap img(":Images/Backgrounds/PointsBackground.png");
	ui->backLbl->setPixmap(img.scaled(s));
	ui->backLbl->resize(size());
	ui->backLbl->move(0, 0);
	setLayout(ui->gridLayout);
}

PointsPnl::~PointsPnl()
{
	delete ui;
}

void PointsPnl::update(qint32 points)
{
	ui->pointsLbl->setText(QString::number(points));
}
