#include "ConnectOnlineWgt.h"
#include "ui_ConnectOnlineWgt.h"

#include <QLineEdit>
#include <QSpacerItem>

#include "PushLabel.h"

#include <QDebug>

ConnectOnlineWgt::ConnectOnlineWgt(QPair<QPixmap *, QPixmap *> buttonImg, qreal mult, QWidget *parent) :
	QWidget(parent), ui(new Ui::ConnectOnlineWgt), MULT(mult)
{
	ui->setupUi(this);
	
	setVisible(false);
	setLayout(ui->gridLayout);
	
	ELEMENT_HEIGHT = static_cast<quint16>(BASE_ELEMENT_HEIGHT*MULT);
	ELEMENT_WIDTH = static_cast<quint16>(BASE_ELEMENT_WIDTH*MULT);
	BORDER = static_cast<quint16>(BASE_BORDER*MULT);
	
	createBtn = std::make_unique<PushLabel>("Создать", this);
	connectBtn = std::make_unique<PushLabel>("Присоединиться", this);
	cancelBtn = std::make_unique<PushLabel>("Отмена", this);
	
	ipLine = std::make_unique<QLineEdit>(this);
	ipLine->setPlaceholderText("Введите IP-адрес");
	ipLine->setMaxLength(15);
	QPalette linePal;
	linePal.setColor(QPalette::Text, Qt::yellow);
	linePal.setColor(QPalette::Base, qRgb(0, 0, 0));
	ipLine->setPalette(linePal);
	
	spacer1 = std::make_unique<QSpacerItem>(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	spacer2 = std::make_unique<QSpacerItem>(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	
	createBtn->loadPixmaps(buttonImg.first, buttonImg.second);
	connectBtn->loadPixmaps(buttonImg.first, buttonImg.second);
	cancelBtn->loadPixmaps(buttonImg.first, buttonImg.second);
	
	createBtn->setFixedSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	connectBtn->setFixedSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	cancelBtn->setFixedSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	ipLine->setFixedSize(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	
	ui->verticalLayout->setMargin(BORDER);
	ui->verticalLayout->addWidget(createBtn.get());
	ui->verticalLayout->addSpacerItem(spacer1.get());
	ui->verticalLayout->addWidget(ipLine.get());
	ui->verticalLayout->addWidget(connectBtn.get());
	ui->verticalLayout->addSpacerItem(spacer2.get());
	ui->verticalLayout->addWidget(cancelBtn.get());
	
	QFont font = createBtn->font();
	font.setPixelSize(static_cast<quint8>(BASE_FONT*MULT));
	createBtn->setFont(font);
	connectBtn->setFont(font);
	cancelBtn->setFont(font);
	ipLine->setFont(font);
	
	QPalette btnPal;
	btnPal.setColor(QPalette::WindowText, Qt::yellow);
	createBtn->setPalette(btnPal);
	connectBtn->setPalette(btnPal);
	cancelBtn->setPalette(btnPal);
	
	ui->gridLayout->addWidget(ui->back, 1, 1);
	ui->back->resize(static_cast<qint32>(BASE_WEIGHT*MULT), static_cast<qint32>(BASE_HEIGHT*MULT));
	QPixmap img(":/Images/Backgrounds/200x200PanelBackground.png");
	ui->back->setPixmap(img.scaled(ui->back->size()));
	
	QPalette pal(palette());
	QColor col;
	col.setRgb(0, 0, 0, 200);
	pal.setColor(QPalette::Background, col);
	setAutoFillBackground(true);
	setPalette(pal);
	
	connect(createBtn.get(), &PushLabel::clicked, this, &ConnectOnlineWgt::createBtnPush);
	connect(connectBtn.get(), &PushLabel::clicked, this, &ConnectOnlineWgt::connectBtnPush);
	connect(cancelBtn.get(), &PushLabel::clicked, this, &ConnectOnlineWgt::cancelSignal);
}

ConnectOnlineWgt::~ConnectOnlineWgt()
{
	delete ui;
}

void ConnectOnlineWgt::createBtnPush()
{
	emit createSignal();
}

void ConnectOnlineWgt::connectBtnPush()
{
	emit connectSignal(ipLine->text());
}

void ConnectOnlineWgt::cancelBtnPush()
{
	emit cancelSignal();
}
