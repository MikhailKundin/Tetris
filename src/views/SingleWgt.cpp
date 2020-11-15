#include "SingleWgt.h"
#include "ui_SingleWgt.h"

#include <QLabel>

#include "../TetrisInfo.h"
#include "PlaygroundPnl.h"
#include "PointsPnl.h"
#include "RecordTablePnl.h"
#include "LevelFigurePnl.h"
#include "../Database.h"
#include "SaveResultsWgt.h"
#include "ButtonPanel.h"

#include <QDebug>

SingleWgt::SingleWgt(QWidget *parent) : 
	WidgetInfo(parent), ui(new Ui::SingleWgt)
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
	
	pauseWgt = std::make_unique<ButtonPanel>("Пауза", pauseButtons, getPanelPixmaps(), MULT, this);
	pauseWgt->setObjectName(PAUSE_NAME);
	pauseWgt->setVisible(false);
	connect(pauseWgt.get(), &ButtonPanel::clicked, this, &SingleWgt::buttonsFilter);
	connect(this, &SingleWgt::wgtResize, pauseWgt.get(), [=](){pauseWgt->resize(size());});
	
	screenSize = size();
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

void SingleWgt::updateFigure(AbstractFigure *figure)
{
	lfPnl->setFigure(figure);
}

void SingleWgt::defeat()
{
	blockPause = true;
	if (rtPnl->getPlace() < 10)
	{
		SaveResultsWgt *srWgt = new SaveResultsWgt(getPanelPixmaps(), MULT, this);
		srWgt->setVisible(true);
		srWgt->resize(size());
		connect(srWgt, &SaveResultsWgt::saveResult, this, &SingleWgt::saveBtnPush);
		connect(this, &SingleWgt::wgtResize, srWgt, [=](){srWgt->resize(size());});
	}
	else
	{
		createDefeatPanel();
	}
}

void SingleWgt::pauseBtnPress()
{
	if (!blockPause)
	{
		if (pauseWgt->isVisible())
		{
			pauseWgt->setVisible(false);
			emit resumeSignal();
		}
		else
		{
			pauseWgt->setVisible(true);
			emit pauseSignal();
		}
	}
}

void SingleWgt::restart()
{
	blockPause = false;
	rtPnl->restart();
}

void SingleWgt::saveBtnPush(QString name)
{
	rtPnl->saveResult(name);
	createDefeatPanel();
	SaveResultsWgt *srWgt = qobject_cast<SaveResultsWgt *>(sender());
	srWgt->setVisible(false);
	srWgt->deleteLater();
}

void SingleWgt::buttonsFilter(QString objName)
{
	if (sender()->objectName() == PAUSE_NAME)
	{
		if (objName == pauseButtons.at(0))
		{
			pauseWgt->setVisible(false);
			emit resumeSignal();
		}
		else if (objName == pauseButtons.at(1))
		{
			pauseWgt->setVisible(false);
			emit restartSignal();
		}
		else if (objName == pauseButtons.at(2))
		{
			pauseWgt->setVisible(false);
			emit exitSignal();
		}
	}
	else if (sender()->objectName() == DEFEAT_NAME)
	{
		ButtonPanel *defPnl = qobject_cast<ButtonPanel *>(sender());
		if (objName == defeatButtons.at(0))
		{
			defPnl->setVisible(false);
			defPnl->deleteLater();
			emit restartSignal();
		}
		else if (objName == defeatButtons.at(1))
		{
			defPnl->setVisible(false);
			defPnl->deleteLater();
			emit exitSignal();
		}
	}
}

void SingleWgt::resizeEvent(QResizeEvent *e)
{
	Q_UNUSED(e)
	
	emit wgtResize();
}

void SingleWgt::createDefeatPanel()
{
	ButtonPanel *defeatPnl = new ButtonPanel("Поражение", defeatButtons, getPanelPixmaps(), MULT, this);
	defeatPnl->setObjectName(DEFEAT_NAME);
	defeatPnl->setVisible(true);
	defeatPnl->resize(size());
	connect(defeatPnl, &ButtonPanel::clicked, this, &SingleWgt::buttonsFilter);
	connect(this, &SingleWgt::wgtResize, defeatPnl, [=](){defeatPnl->resize(size());});
}
