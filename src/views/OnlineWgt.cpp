#include "OnlineWgt.h"
#include "ui_OnlineWgt.h"

OnlineWgt::OnlineWgt(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::OnlineWgt)
{
	ui->setupUi(this);
}

OnlineWgt::~OnlineWgt()
{
	delete ui;
}
