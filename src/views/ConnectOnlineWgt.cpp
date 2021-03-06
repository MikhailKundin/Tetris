#include "ConnectOnlineWgt.h"
#include "ui_ConnectOnlineWgt.h"

#include <QLineEdit>
#include <QSpacerItem>

#include "PushLabel.h"

ConnectOnlineWgt::ConnectOnlineWgt(QPair<QHash<QString, QPixmap *>, QHash<QString, QSoundEffect *> > media, 
								   qreal mult, QWidget *parent) :
	QWidget(parent), ui(new Ui::ConnectOnlineWgt), MULT(mult)
{
	ui->setupUi(this);
	
	setLayout(ui->gridLayout);
	
	QHash<QString, QPixmap *> pixmaps = media.first;
	QHash<QString, QSoundEffect *> sounds = media.second;
	
	ELEMENT_HEIGHT = static_cast<quint16>(BASE_ELEMENT_HEIGHT*MULT);
	ELEMENT_WIDTH = static_cast<quint16>(BASE_ELEMENT_WIDTH*MULT);
	BORDER = static_cast<quint16>(BASE_BORDER*MULT);
	
	createBtn = std::make_unique<PushLabel>("Создать", this);
	connectBtn = std::make_unique<PushLabel>("Присоединиться", this);
	cancelBtn = std::make_unique<PushLabel>("Выход", this);
	
	ipLine = std::make_unique<QLineEdit>(this);
	ipLine->setPlaceholderText("Введите IP-адрес");
	ipLine->setMaxLength(15);
	QPalette linePal;
	linePal.setColor(QPalette::Text, Qt::yellow);
	linePal.setColor(QPalette::Base, qRgb(0, 0, 0));
	ipLine->setPalette(linePal);
	
	spacer1 = std::make_unique<QSpacerItem>(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	spacer2 = std::make_unique<QSpacerItem>(ELEMENT_WIDTH, ELEMENT_HEIGHT);
	
	createBtn->loadPixmaps(pixmaps["enter"], pixmaps["leave"]);
	connectBtn->loadPixmaps(pixmaps["enter"], pixmaps["leave"]);
	cancelBtn->loadPixmaps(pixmaps["enter"], pixmaps["leave"]);
	
	createBtn->loadSounds(sounds["enterSound"]);
	connectBtn->loadSounds(sounds["enterSound"]);
	cancelBtn->loadSounds(sounds["enterSound"]);
	
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
	
	QFont font("Segoe Print", -1, QFont::Bold);
	font.setPixelSize(static_cast<quint8>(BASE_FONT*MULT));
	createBtn->setFont(font);
	connectBtn->setFont(font);
	cancelBtn->setFont(font);
	ipLine->setFont(font);
	createBtn->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	connectBtn->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	cancelBtn->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	ipLine->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
	
	QPalette btnPal;
	btnPal.setColor(QPalette::WindowText, Qt::yellow);
	createBtn->setPalette(btnPal);
	connectBtn->setPalette(btnPal);
	cancelBtn->setPalette(btnPal);
	
	ui->gridLayout->addWidget(ui->back, 1, 1);
	ui->back->resize(static_cast<qint32>(BASE_WEIGHT*MULT), static_cast<qint32>(BASE_HEIGHT*MULT));
	ui->back->setPixmap(pixmaps["back"]->scaled(ui->back->size()));
	
	QPalette pal(palette());
	QColor col;
	col.setRgb(0, 0, 0, 200);
	pal.setColor(QPalette::Window, col);
	setAutoFillBackground(true);
	setPalette(pal);
	
	connect(createBtn.get(), &PushLabel::clicked, this, &ConnectOnlineWgt::createBtnPush);
	connect(connectBtn.get(), &PushLabel::clicked, this, &ConnectOnlineWgt::connectBtnPush);
	connect(cancelBtn.get(), &PushLabel::clicked, this, &ConnectOnlineWgt::exitSignal);
}

ConnectOnlineWgt::~ConnectOnlineWgt()
{
	ui->verticalLayout->removeItem(spacer1.get());
	ui->verticalLayout->removeItem(spacer2.get());
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
	emit exitSignal();
}
