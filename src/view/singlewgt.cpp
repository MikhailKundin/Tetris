#include "SingleWgt.h"
#include "ui_singlewgt.h"

#include <QLabel>

#include "../TetrisInfo.h"
#include "PlaygroundPnl.h"
#include "PointsPnl.h"
#include "RecordTablePnl.h"
#include "LevelFigurePnl.h"

#include <QDebug>

SingleWgt::SingleWgt(QWidget *parent) : WidgetInfo(parent), ui(new Ui::SingleWgt)
{
	ui->setupUi(this);
	
	setLayout(ui->gBox);
	
	pg = std::make_unique<PlaygroundPnl>(BLOCK_SIZE, MULT, ui->playgroundPlace);
	ui->playgroundPlace->setFixedSize(pg->size());
	
	rtPnl = std::make_unique<RecordTablePnl>(pg->height(), MULT, ui->recordTablePlace);
	ui->recordTablePlace->setFixedSize(rtPnl->size());
	
	pointsPnl = std::make_unique<PointsPnl>(pg->width(), MULT, ui->pointsPlace);
	ui->pointsPlace->setFixedSize(pointsPnl->size());
	
	lfPnl = std::make_unique<LevelFigurePnl>(pointsPnl->height(), BLOCK_SIZE, MULT, ui->levelFigurePnlPlace);
	lfPnl->setFixedSize(lfPnl->width(), ui->recordTablePlace->height() + ui->pointsPlace->height());
	ui->levelFigurePnlPlace->setFixedSize(lfPnl->size());
	ui->gBox->addWidget(ui->levelFigurePnlPlace, 1, 0, 2, 1);
	
	ui->gBox->setAlignment(ui->pointsPlace, Qt::AlignCenter);
	ui->gBox->setAlignment(ui->playgroundPlace, Qt::AlignRight);
	ui->gBox->setAlignment(ui->recordTablePlace, Qt::AlignLeft);
	ui->gBox->setAlignment(ui->levelFigurePnlPlace, Qt::AlignRight);
	
	rightTopLbl = std::make_unique<QLabel>(this);
	ui->gBox->addWidget(rightTopLbl.get(), 1, 3);
	rightTopLbl->setFixedSize(ui->recordTablePlace->width(), ui->pointsPlace->height());
	QPixmap yellowImg(":Images/Backgrounds/YellowBackground.png");
	rightTopLbl->setPixmap(yellowImg.scaled(rightTopLbl->size()));
	
	setMinimumHeight(pg->height() + pointsPnl->height());
	setMinimumWidth(ui->levelFigurePnlPlace->width() + pg->width() + rtPnl->width());
}

SingleWgt::~SingleWgt()
{
	delete ui;
}

void SingleWgt::updateGrid(const QMap<qint16, QImage *> &grid) const
{
	pg->update(grid);
}

void SingleWgt::updatePoints(quint32 points)
{
	pointsPnl->update(points);
	rtPnl->updateRecordTable(points);
}

void SingleWgt::updateLevel(quint16 level)
{
	lfPnl->setLevel(level);
}

void SingleWgt::updateFigure(AbstractFigure *&figure)
{
	lfPnl->setFigure(figure);
}
