#include "MainMenuWgt.h"
#include "ui_MainMenuWgt.h"

#include "PushLabel.h"

#include <QDebug>

MainMenuWgt::MainMenuWgt(WidgetInfo *parent) :
	WidgetInfo(parent), ui(new Ui::MainMenuWdt)
{
	ui->setupUi(this);
	
	QPixmap logoImg(":Images/Pictures/Logo.png");
	quint16 logoWidth = static_cast<quint16>(BASE_LOGO_WIDTH*MULT);
	quint16 logoHeight = static_cast<quint16>(BASE_LOGO_HEIGHT*MULT);
	logoImg = logoImg.scaled(logoWidth, logoHeight);
	ui->logo->resize(logoImg.size());
	ui->logo->setPixmap(logoImg.scaled(ui->logo->size(), Qt::KeepAspectRatio));
	
	spacer = std::make_unique<QSpacerItem>(10, static_cast<qint32>(BASE_SPACER_HEIGHT*MULT), 
										   QSizePolicy::Fixed, QSizePolicy::Fixed);
	ui->verticalLayout->addSpacerItem(spacer.get());
	
	singleBtn = std::make_unique<PushLabel>("Одиночная игра", this);
	onlineBtn = std::make_unique<PushLabel>("Сетевая игра", this);
	exitBtn = std::make_unique<PushLabel>("Выход", this);
	
	singleBtn->loadPixmaps(buttonEnter, buttonLeave);
	singleBtn->loadSounds(enter);
	onlineBtn->loadPixmaps(buttonEnter, buttonLeave);
	onlineBtn->loadSounds(enter);
	exitBtn->loadPixmaps(buttonEnter, buttonLeave);
	exitBtn->loadSounds(enter);
	
	ui->verticalLayout->addWidget(singleBtn.get());
	ui->verticalLayout->addWidget(onlineBtn.get());
	ui->verticalLayout->addWidget(exitBtn.get());
	
	QFont font = singleBtn->font();
	font.setPixelSize(static_cast<quint8>(BASE_FONT*MULT));
	singleBtn->setFont(font);
	onlineBtn->setFont(font);
	exitBtn->setFont(font);
	
	QPalette pal;
	pal.setColor(QPalette::WindowText, Qt::yellow);
	singleBtn->setPalette(pal);
	onlineBtn->setPalette(pal);
	exitBtn->setPalette(pal);
	
	quint16 height = static_cast<quint16>(BASE_BUTTON_HEIGHT*MULT);
	quint16 width = static_cast<quint16>(BASE_BUTTON_WIDTH*MULT);
	singleBtn->setFixedSize(width, height);
	onlineBtn->setFixedSize(width, height);
	exitBtn->setFixedSize(width, height);
	
	ui->verticalLayout->setAlignment(ui->logo, Qt::AlignCenter);
	ui->verticalLayout->setAlignment(singleBtn.get(), Qt::AlignCenter);
	ui->verticalLayout->setAlignment(onlineBtn.get(), Qt::AlignCenter);
	ui->verticalLayout->setAlignment(exitBtn.get(), Qt::AlignCenter);
	
	resize(ui->verticalLayout->totalMinimumSize());
	
	connect(singleBtn.get(), &PushLabel::clicked, this, &MainMenuWgt::singleBtnClicked);
	connect(onlineBtn.get(), &PushLabel::clicked, this, &MainMenuWgt::onlineBtnClicked);
	connect(exitBtn.get(), &PushLabel::clicked, this, &MainMenuWgt::exitBtnClicked);
}

MainMenuWgt::~MainMenuWgt()
{
	ui->verticalLayout->removeItem(spacer.get());
	delete ui;
}

QString MainMenuWgt::test()
{
	return singleBtn->text();
}

void MainMenuWgt::singleBtnClicked()
{
	emit singleSignal();
}

void MainMenuWgt::onlineBtnClicked()
{
	emit onlineSignal();
}

void MainMenuWgt::exitBtnClicked()
{
	emit exitSignal();
}
