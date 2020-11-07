#include "SaveResultsWgt.h"
#include "ui_SaveResultsWgt.h"

#include <QLabel>

#include "PushLabel.h"

#include <QDebug>

SaveResultsWgt::SaveResultsWgt(QHash<QString, QPixmap *> pixmaps, qreal mult, QWidget *parent) :
	QWidget(parent), ui(new Ui::SaveResultsWgt), MULT(mult)
{
	ui->setupUi(this);
	
	setLayout(ui->gridLayout);
	
	saveBtn = std::make_unique<PushLabel>("Сохранить", this);
	cancelBtn = std::make_unique<PushLabel>("Отмена", this);
	saveBtn->loadPixmaps(pixmaps["enter"], pixmaps["leave"]);
	cancelBtn->loadPixmaps(pixmaps["enter"], pixmaps["leave"]);
	ui->verticalLayout->addWidget(saveBtn.get());
	ui->verticalLayout->addWidget(cancelBtn.get());
	
	ELEMENT_HEIGHT = static_cast<quint16>(BASE_ELEMENT_HEIGHT*MULT);
	ELEMENT_WIDTH = static_cast<quint16>(BASE_ELEMENT_WIDTH*MULT);
	ui->lineEdit->setFixedSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	saveBtn->setFixedSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	cancelBtn->setFixedSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	
	QFont font = ui->lineEdit->font();
	font.setPixelSize(static_cast<quint8>(BASE_FONT*MULT));
	ui->lineEdit->setFont(font);
	saveBtn->setFont(font);
	cancelBtn->setFont(font);
	
	QPalette btnPal;
	btnPal.setColor(QPalette::WindowText, Qt::yellow);
	saveBtn->setPalette(btnPal);
	cancelBtn->setPalette(btnPal);
	
	BORDER = static_cast<quint16>(BASE_BORDER*MULT);
	ui->verticalLayout->setMargin(BORDER);
	
	ui->gridLayout->addWidget(ui->back, 1, 1);
	ui->back->resize(static_cast<qint32>(BASE_WEIGHT*MULT), static_cast<qint32>(BASE_HEIGHT*MULT));
	ui->back->setPixmap(pixmaps["back"]->scaled(ui->back->size()));
	
	QPalette pal(palette());
	QColor col;
	col.setRgb(0, 0, 0, 200);
	pal.setColor(QPalette::Background, col);
	setAutoFillBackground(true);
	setPalette(pal);
	
	connect(saveBtn.get(), &PushLabel::clicked, this, &SaveResultsWgt::saveBtnPush);
	connect(cancelBtn.get(), &PushLabel::clicked, this, &SaveResultsWgt::cancelBtnPush);
}

SaveResultsWgt::~SaveResultsWgt()
{
	delete ui;
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