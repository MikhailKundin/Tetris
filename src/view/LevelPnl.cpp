#include "LevelPnl.h"
#include "ui_LevelPnl.h"

#include <QLabel>

LevelPnl::LevelPnl(quint16 nextFigureWidth, quint16 pointsHeight, qreal mult, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::LevelPnl)
{
	ui->setupUi(this);
	
	resize(nextFigureWidth, pointsHeight);
	
	QPixmap img(":/Images/Backgrounds/LevelBackground.png");
	back = std::make_unique<QLabel>(this);
	back->move(0, 0);
	back->resize(size());
	back->setPixmap(img.scaled(back->size()));
	
	QFont font = ui->levelLbl->font();
	font.setPixelSize(static_cast<qint32>(BASE_FONT_SIZE*mult));
	ui->levelLbl->setFont(font);
}

LevelPnl::~LevelPnl()
{
	delete ui;
}

void LevelPnl::setLevel(quint16 level)
{
	ui->levelLbl->setText(QString::number(level));
}
