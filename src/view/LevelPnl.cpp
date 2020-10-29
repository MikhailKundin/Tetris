#include "LevelPnl.h"
#include "ui_LevelPnl.h"

LevelPnl::LevelPnl(qint16 nextFigureWidth, qint16 pointsHeight, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::LevelPnl)
{
	ui->setupUi(this);
	
	setFixedSize(nextFigureWidth, pointsHeight);
	
	QPixmap img(":/Images/Backgrounds/LevelBackground.png");
	back = std::make_unique<QLabel>(this);
	back->move(0, 0);
	back->resize(size());
	back->setPixmap(img.scaled(back->size()));
}

LevelPnl::~LevelPnl()
{
	delete ui;
}

void LevelPnl::setLevel(qint16 level)
{
	ui->levelLbl->setText(QString::number(level));
}
