#include "MainMenuWgt.h"
#include "ui_mainmenuwgt.h"

#include "PushLabel.h"

#include <QDebug>

MainMenuWgt::MainMenuWgt(QPair<QPixmap *, QPixmap *> buttonImg, WidgetInfo *parent) :
	WidgetInfo(buttonImg, parent), ui(new Ui::MainMenuWdt)
{
	ui->setupUi(this);
	
	QPixmap logoImg(":Images/Pictures/Logo.png");
	quint16 logoWidth = static_cast<quint16>(BASE_LOGO_WIDTH*MULT);
	quint16 logoHeight = static_cast<quint16>(BASE_LOGO_HEIGHT*MULT);
	logoImg = logoImg.scaled(logoWidth, logoHeight);
	ui->logo->resize(logoImg.size());
	ui->logo->setPixmap(logoImg.scaled(ui->logo->size(), Qt::KeepAspectRatio));
	
	singleBtn = std::make_unique<PushLabel>("Одиночная игра", this);
	onlineBtn = std::make_unique<PushLabel>("Сетевая игра", this);
	exitBtn = std::make_unique<PushLabel>("Выход", this);
	
	singleBtn->loadPixmaps(m_buttonImg.first, m_buttonImg.second);
	onlineBtn->loadPixmaps(m_buttonImg.first, m_buttonImg.second);
	exitBtn->loadPixmaps(m_buttonImg.first, m_buttonImg.second);
	
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
	
	connect(singleBtn.get(), &PushLabel::clicked, this, &MainMenuWgt::singleBtnClicked);
	connect(onlineBtn.get(), &PushLabel::clicked, this, &MainMenuWgt::onlineBtnClicked);
	connect(exitBtn.get(), &PushLabel::clicked, this, &MainMenuWgt::exitBtnClicked);
}

MainMenuWgt::~MainMenuWgt()
{
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
