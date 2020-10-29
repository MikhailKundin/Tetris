#include "LevelFigurePnl.h"
#include "ui_LevelFigurePnl.h"

#include <QDebug>

LevelFigurePnl::LevelFigurePnl(qint16 pointsHeight, qint8 blockSize, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::LevelFigurePnl)
{
	ui->setupUi(this);
	
	nextFigurePnl = std::make_unique<NextFigurePnl>(blockSize, this);
	levelPnl = std::make_unique<LevelPnl>(nextFigurePnl->width(), pointsHeight, this);
	
	setFixedWidth(nextFigurePnl->width());
	
	yellowLbl = std::make_unique<QLabel>(this);
	img = std::make_unique<QPixmap>(":Images/Backgrounds/YellowBackground.png");
	yellowLbl->setPixmap(img->scaled(yellowLbl->size()));
	
	ui->vBox->addWidget(levelPnl.get());
	ui->vBox->addWidget(nextFigurePnl.get());
	ui->vBox->addWidget(yellowLbl.get());
}

LevelFigurePnl::~LevelFigurePnl()
{
	delete ui;
}

void LevelFigurePnl::setLevel(qint16 level)
{
	levelPnl->setLevel(level);
}

void LevelFigurePnl::setFigure(AbstractFigure *&figure)
{
	nextFigurePnl->update(figure);
}

void LevelFigurePnl::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e)
	
	yellowLbl->setPixmap(img->scaled(yellowLbl->size()));
}
