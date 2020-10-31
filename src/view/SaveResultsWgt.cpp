#include "SaveResultsWgt.h"
#include "ui_SaveResultsWgt.h"

#include <QLabel>

SaveResultsWgt::SaveResultsWgt(qreal MULT, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SaveResultsWgt)
{
	ui->setupUi(this);
	
	//setVisible(false);
	setLayout(ui->verticalLayout);
	resize(static_cast<qint32>(BASE_WEIGHT*MULT), static_cast<qint32>(BASE_HEIGHT*MULT));
	
	ui->back->move(0, 0);
	ui->back->resize(size());
	QPixmap img(":/Images/Backgrounds/200x200PanelBackground.png");
	ui->back->setPixmap(img.scaled(ui->back->size()));
	
	ELEMENT_HEIGHT = static_cast<quint16>(BASE_ELEMENT_HEIGHT*MULT);
	ELEMENT_WIDTH = static_cast<quint16>(BASE_ELEMENT_WIDTH*MULT);
	ui->lineEdit->setFixedSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	ui->pushButton->setFixedSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	ui->pushButton_2->setFixedSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	
	QFont font = ui->lineEdit->font();
	font.setPixelSize(static_cast<quint8>(BASE_FONT*MULT));
	ui->lineEdit->setFont(font);
	ui->pushButton->setFont(font);
	ui->pushButton_2->setFont(font);
	
	BORDER = static_cast<quint16>(BASE_BORDER*MULT);
	ui->verticalLayout->setMargin(BORDER);
	
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