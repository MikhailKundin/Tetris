#include "PointsPnl.h"
#include "ui_PointsPnl.h"

#include <QDebug>

PointsPnl::PointsPnl(quint16 width, qreal mult, QWidget *parent) : QWidget(parent), ui(new Ui::PointsWgt)
{
	ui->setupUi(this);
	
	resize(width, static_cast<qint32>(HEIGHT*mult));
	
	QPixmap img(":Images/Backgrounds/PointsBackground.png");
	ui->backLbl->move(0, 0);
	ui->backLbl->resize(size());
	ui->backLbl->setPixmap(img.scaled(size()));
	
	QFont font = ui->pointsLbl->font();
	font.setPixelSize(static_cast<qint32>(BASE_FONT_SIZE*mult));
	ui->pointsLbl->setFont(font);
	
	setLayout(ui->gridLayout);
}

PointsPnl::~PointsPnl()
{
	delete ui;
}

void PointsPnl::update(quint32 points)
{
	ui->pointsLbl->setText(QString::number(points));
}

quint32 PointsPnl::getPoints() const
{
	return ui->pointsLbl->text().toUInt();
}
