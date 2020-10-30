#include "SaveResultsWgt.h"
#include "ui_SaveResultsWgt.h"

SaveResultsWgt::SaveResultsWgt(qreal mult, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SaveResultsWgt)
{
	ui->setupUi(this);
	
	//setVisible(false);
	setFixedSize(static_cast<qint32>(BASE_WEIGHT*mult), static_cast<qint32>(BASE_HEIGHT*mult));
	
	connect(ui->pushButton, &QPushButton::clicked, this, &SaveResultsWgt::saveBtnPush);
	connect(ui->pushButton_2, &QPushButton::clicked, this, &SaveResultsWgt::cancelBtnPush);
}

SaveResultsWgt::~SaveResultsWgt()
{
	delete ui;
}

void SaveResultsWgt::activate()
{
	setVisible(true);
}

void SaveResultsWgt::cancelBtnPush()
{
	emit saveResult("");
	ui->lineEdit->setText("");
	setVisible(false);
}

void SaveResultsWgt::saveBtnPush()
{
	if (ui->lineEdit->text() != "")
	{
		emit saveResult(ui->lineEdit->text());
		ui->lineEdit->setText("");
		setVisible(false);
	}
	else
	{
		ui->lineEdit->setPlaceholderText("Введите имя!");
	}
}
