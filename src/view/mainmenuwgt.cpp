#include "MainMenuWgt.h"
#include "ui_mainmenuwgt.h"

#include <QPushButton>

#include "PushLabel.h"

#include <QDebug>

MainMenuWgt::MainMenuWgt(WidgetInfo *parent) :
	WidgetInfo(parent),
	ui(new Ui::MainMenuWdt)
{
	ui->setupUi(this);
	
	logoImg = std::make_unique<QPixmap>(":Images/Pictures/Logo.png");
	logoImg = std::make_unique<QPixmap>(logoImg->scaled(300, 100, Qt::KeepAspectRatio));
	ui->logo->setMinimumSize(logoImg->size());
	ui->logo->setPixmap(*logoImg.get());
	
	QString enterImg = ":/Images/Buttons/HoverEnter.png";
	QString leaveImg = ":/Images/Buttons/HoverLeave.png";
	
	singleBtn = std::make_unique<PushLabel>(ui->singleBtn->objectName(), enterImg, leaveImg);
	onlineBtn = std::make_unique<PushLabel>(ui->onlineBtn->objectName(), enterImg, leaveImg);
	exitBtn = std::make_unique<PushLabel>(ui->exitBtn->objectName(), enterImg, leaveImg);
	
	ui->singleBtn->installEventFilter(singleBtn.get());
	ui->onlineBtn->installEventFilter(onlineBtn.get());
	ui->exitBtn->installEventFilter(exitBtn.get());
	
	ui->singleBtn->setMouseTracking(true);
	
	QFont font = ui->singleBtn->font();
	font.setPixelSize(static_cast<quint8>(BASE_FONT*MULT));
	ui->singleBtn->setFont(font);
	ui->onlineBtn->setFont(font);
	ui->exitBtn->setFont(font);
	
	ui->singleBtn = singleBtn.get();
	ui->onlineBtn = onlineBtn.get();
	ui->exitBtn = exitBtn.get();
	
	quint16 height = static_cast<quint16>(BASE_BUTTON_HEIGHT*MULT);
	quint16 width = static_cast<quint16>(BASE_BUTTON_WIDTH*MULT);
	ui->singleBtn->resize(width, height);
	ui->onlineBtn->resize(width, height);
	ui->exitBtn->resize(width, height);
	
	ui->verticalLayout->setAlignment(ui->logo, Qt::AlignCenter);
	ui->verticalLayout->setAlignment(ui->singleBtn, Qt::AlignCenter);
	ui->verticalLayout->setAlignment(ui->onlineBtn, Qt::AlignCenter);
	ui->verticalLayout->setAlignment(ui->exitBtn, Qt::AlignCenter);
	
//	ui->singleBtn->setStyleSheet("background: black;"
//								 "background-image: url(:/Images/Backgrounds/200x200PanelBackground.png);"
//								 "background-position: center;");
//	ui->onlineBtn->setStyleSheet("background: black;"
//								 "background-image: url(:/Images/Backgrounds/GreyBackground.png);");
//	ui->exitBtn->setStyleSheet("background: black;"
//							   "background-image: url(:/Images/Backgrounds/GreyBackground.png);");
	
	connect(singleBtn.get(), &PushLabel::clicked, this, &MainMenuWgt::singleBtnClicked);
	connect(onlineBtn.get(), &PushLabel::clicked, this, &MainMenuWgt::onlineBtnClicked);
	connect(exitBtn.get(), &PushLabel::clicked, this, &MainMenuWgt::exitBtnClicked);
}

MainMenuWgt::~MainMenuWgt()
{
	delete ui;
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
