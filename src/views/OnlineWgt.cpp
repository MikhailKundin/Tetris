#include "OnlineWgt.h"
#include "ui_OnlineWgt.h"

#include <QLabel>
#include <QApplication>
#include <QScreen>

#include "../TetrisInfo.h"
#include "PlaygroundPnl.h"
#include "PointsPnl.h"
#include "LevelFigurePnl.h"
#include "SaveResultsWgt.h"
#include "SingleExitWgt.h"

#include <QDebug>

OnlineWgt::OnlineWgt(QWidget *parent) :
	WidgetInfo(parent), ui(new Ui::OnlineWgt)
{
	ui->setupUi(this);
	setLayout(ui->gBox);
	
	ofPg = std::make_unique<PlaygroundPnl>(BLOCK_SIZE, MULT, ui->ofPgPnl);
	ui->ofPgPnl->setFixedSize(ofPg->size());
	onPg = std::make_unique<PlaygroundPnl>(BLOCK_SIZE, MULT, ui->onPgPnl);
	ui->onPgPnl->setFixedSize(onPg->size());
	
	onPoints = std::make_unique<PointsPnl>(onPg->width(), MULT, ui->onPointsPnl);
	ui->onPointsPnl->setFixedSize(onPoints->size());
	ofPoints = std::make_unique<PointsPnl>(ofPg->width(), MULT, ui->ofPointsPnl);
	ui->ofPointsPnl->setFixedSize(ofPoints->size());
	
	ofLevelFigure = std::make_unique<LevelFigurePnl>(ofPoints->height(), BLOCK_SIZE, MULT, ui->ofLevelFigurePnl);
	ofLevelFigure->setFixedSize(ofLevelFigure->width(), ui->ofPgPnl->height() + ui->ofPointsPnl->height());
	ui->ofLevelFigurePnl->setFixedSize(ofLevelFigure->size());
	ui->gBox->addWidget(ui->ofLevelFigurePnl, 1, 1, 2, 1);
	onLevelFigure = std::make_unique<LevelFigurePnl>(onPoints->height(), BLOCK_SIZE, MULT, ui->onLevelFigurePnl);
	onLevelFigure->setFixedSize(onLevelFigure->width(), ui->onPgPnl->height() + ui->onPointsPnl->height());
	ui->onLevelFigurePnl->setFixedSize(onLevelFigure->size());
	ui->gBox->addWidget(ui->onLevelFigurePnl, 1, 5, 2, 1);
	
	QPixmap yellowImg(":Images/Backgrounds/YellowBackground.png");
	ui->topYellowLbl->setFixedSize(static_cast<qint32>(BASE_YELLOW_WIDTH*MULT), ui->ofPointsPnl->height());
	ui->topYellowLbl->setPixmap(yellowImg.scaled(ui->topYellowLbl->size()));
	ui->yellowLbl->setFixedSize(static_cast<qint32>(BASE_YELLOW_WIDTH*MULT), ui->ofPgPnl->height());
	ui->yellowLbl->setPixmap(yellowImg.scaled(ui->yellowLbl->size()));
	
	setMinimumHeight(ofPg->height() + ofPoints->height());
	setMinimumWidth(ui->ofLevelFigurePnl->width() + ofPg->width() + ui->yellowLbl->width() + 
					ui->onLevelFigurePnl->width() + onPg->width());
}

OnlineWgt::~OnlineWgt()
{
	delete ui;
}

void OnlineWgt::ofUpdateGrid(const QMap<qint16, QImage *> &grid) const
{
	ofPg->update(grid);
}

void OnlineWgt::ofUpdatePoints(quint32 points)
{
	ofPoints->update(points);
}

void OnlineWgt::ofUpdateLevel(quint16 level)
{
	ofLevelFigure->setLevel(level);
}

void OnlineWgt::ofUpdateFigure(AbstractFigure *&figure)
{
	ofLevelFigure->setFigure(figure);
}

void OnlineWgt::onUpdateGrid(const QMap<qint16, QImage *> &grid) const
{
	onPg->update(grid);
}

void OnlineWgt::onUpdatePoints(quint32 points)
{
	onPoints->update(points);
}

void OnlineWgt::onUpdateLevel(quint16 level)
{
	onLevelFigure->setLevel(level);
}

void OnlineWgt::onUpdateFigure(AbstractFigure *&figure)
{
	onLevelFigure->setFigure(figure);
}
