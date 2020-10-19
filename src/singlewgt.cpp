#include "singlewgt.h"
#include "ui_singlewgt.h"

#include <QDebug>

SingleWgt::SingleWgt(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SingleWgt)
{
	ui->setupUi(this);
	
	setLayout(ui->gBox);
	
	pg = std::make_unique<Playground>(ui->playgroundPlace);
	ui->playgroundPlace->setMinimumSize(pg->size());
	
	pointsWgt = std::make_unique<PointsWgt>(ui->pointsPlace);
	ui->pointsPlace->setMinimumSize(pointsWgt->size());
	
	rtWgt = std::make_unique<RecordTable>(ui->recordTablePlace);
	ui->recordTablePlace->setMinimumSize(rtWgt->size());
	
	ui->gBox->setAlignment(ui->pointsPlace, Qt::AlignCenter);
	ui->gBox->setAlignment(ui->playgroundPlace, Qt::AlignRight);
	ui->gBox->setAlignment(ui->recordTablePlace, Qt::AlignLeft);
	
	setMinimumHeight(pg->height() + pointsWgt->height() + 6);
}

SingleWgt::~SingleWgt()
{
	delete ui;
}

void SingleWgt::update(const QMap<qint16, QImage *> &map) const
{
	pg->update(map);
}
