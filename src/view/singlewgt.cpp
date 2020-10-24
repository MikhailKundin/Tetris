#include "singlewgt.h"
#include "ui_singlewgt.h"

#include <QDebug>

SingleWgt::SingleWgt(qint8 row, qint8 column, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SingleWgt)
{
	ui->setupUi(this);
	
	setLayout(ui->gBox);
	
	pg = std::make_unique<Playground>(row, column, ui->playgroundPlace);
	ui->playgroundPlace->setMinimumSize(pg->size());
	
	rtWgt = std::make_unique<RecordTable>(QSize(RECORD_WIDTH, pg->height()), ui->recordTablePlace);
	ui->recordTablePlace->setMinimumSize(rtWgt->size());
	
	pointsWgt = std::make_unique<PointsWgt>(QSize(pg->width(), POINTS_HEIGHT), ui->pointsPlace);
	ui->pointsPlace->setMinimumSize(pointsWgt->size());
	
	ui->gBox->setAlignment(ui->pointsPlace, Qt::AlignCenter);
	ui->gBox->setAlignment(ui->playgroundPlace, Qt::AlignRight);
	ui->gBox->setAlignment(ui->recordTablePlace, Qt::AlignLeft);
	
	rightTopLbl = std::make_unique<QLabel>(this);
	ui->gBox->addWidget(rightTopLbl.get(), 1, 3);
	//rightTopLbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	rightTopLbl->setMinimumSize(ui->recordTablePlace->width(), ui->pointsPlace->height());
	QPixmap yellowImg(":Images/Backgrounds/YellowBackground.png");
	rightTopLbl->setPixmap(yellowImg.scaled(rightTopLbl->size()));
	
	setMinimumHeight(pg->height() + pointsWgt->height() + 6);
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
	pointsWgt->update(points);
}
