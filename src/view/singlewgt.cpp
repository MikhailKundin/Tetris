#include "SingleWgt.h"
#include "ui_singlewgt.h"

#include "../TetrisInfo.h"

#include <QDebug>

SingleWgt::SingleWgt(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SingleWgt)
{
	ui->setupUi(this);
	
	setLayout(ui->gBox);
	
	pg = std::make_unique<PlaygroundPnl>(BLOCK_SIZE, ui->playgroundPlace);
	ui->playgroundPlace->setMinimumSize(pg->size());
	
	rtPnl = std::make_unique<RecordTablePnl>(QSize(RECORD_WIDTH, pg->height()), ui->recordTablePlace);
	ui->recordTablePlace->setMinimumSize(rtPnl->size());
	
	pointsPnl = std::make_unique<PointsPnl>(QSize(pg->width(), POINTS_HEIGHT), ui->pointsPlace);
	ui->pointsPlace->setMinimumSize(pointsPnl->size());
	
	lfPnl = std::make_unique<LevelFigurePnl>(pointsPnl->height(), BLOCK_SIZE, ui->levelFigurePnlPlace);
	lfPnl->setMinimumSize(lfPnl->width(), ui->recordTablePlace->height() + ui->pointsPlace->height());
	ui->levelFigurePnlPlace->setMinimumSize(lfPnl->size());
	ui->gBox->addWidget(ui->levelFigurePnlPlace, 1, 0, 2, 1);
	
	ui->gBox->setAlignment(ui->pointsPlace, Qt::AlignCenter);
	ui->gBox->setAlignment(ui->playgroundPlace, Qt::AlignRight);
	ui->gBox->setAlignment(ui->recordTablePlace, Qt::AlignLeft);
	ui->gBox->setAlignment(ui->levelFigurePnlPlace, Qt::AlignRight);
	
	rightTopLbl = std::make_unique<QLabel>(this);
	ui->gBox->addWidget(rightTopLbl.get(), 1, 3);
	rightTopLbl->setMinimumSize(ui->recordTablePlace->width(), ui->pointsPlace->height());
	QPixmap yellowImg(":Images/Backgrounds/YellowBackground.png");
	rightTopLbl->setPixmap(yellowImg.scaled(rightTopLbl->size()));
	
	setMinimumHeight(pg->height() + pointsPnl->height() + 6);
	setMinimumWidth(ui->levelFigurePnlPlace->width() + TetrisInfo::COLUMN_COUNT*BLOCK_SIZE + rightTopLbl->width());
}

SingleWgt::~SingleWgt()
{
	delete ui;
}

void SingleWgt::updateGrid(const QMap<qint16, QImage *> &grid) const
{
	pg->update(grid);
}

void SingleWgt::updatePoints(qint32 points)
{
	pointsPnl->update(points);
}

void SingleWgt::updateLevel(qint16 level)
{
	lfPnl->setLevel(level);
}

void SingleWgt::updateFigure(AbstractFigure *&figure)
{
	lfPnl->setFigure(figure);
}
