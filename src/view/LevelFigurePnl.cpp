#include "LevelFigurePnl.h"
#include "ui_LevelFigurePnl.h"

#include <QLabel>

#include "LevelPnl.h"
#include "NextFigurePnl.h"
#include "../TetrisInfo.h"

#include <QDebug>

LevelFigurePnl::LevelFigurePnl(qint16 pointsHeight, qint8 blockSize, qreal mult, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::LevelFigurePnl)
{
	ui->setupUi(this);
	
	nextFigurePnl = std::make_unique<NextFigurePnl>(blockSize, mult, this);
	nextFigurePnl->setFixedSize(nextFigurePnl->size());
	
	levelPnl = std::make_unique<LevelPnl>(nextFigurePnl->width(), pointsHeight, mult, this);
	levelPnl->setFixedSize(levelPnl->size());
	
	quint16 height = static_cast<quint16>(pointsHeight + blockSize*mult*TetrisInfo::ROW_COUNT);
	resize(nextFigurePnl->width(), height);
	
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
