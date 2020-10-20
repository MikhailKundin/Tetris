#include "mainmenuwdt.h"
#include "ui_mainmenuwdt.h"

MainMenuWdt::MainMenuWdt(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MainMenuWdt)
{
	ui->setupUi(this);
	
	logoImg = std::make_unique<QPixmap>(":Images/Pictures/Logo.png");
	logoImg = std::make_unique<QPixmap>(logoImg->scaled(300, 100, Qt::KeepAspectRatio));
	ui->logo->setMinimumSize(logoImg->size());
	ui->logo->setPixmap(*logoImg.get());
	
	ui->verticalLayout->setAlignment(ui->logo, Qt::AlignCenter);
	ui->verticalLayout->setAlignment(ui->singleBtn, Qt::AlignCenter);
	ui->verticalLayout->setAlignment(ui->onlineBtn, Qt::AlignCenter);
	ui->verticalLayout->setAlignment(ui->exitBtn, Qt::AlignCenter);
	
	connect(ui->singleBtn, &QPushButton::clicked, this, &MainMenuWdt::singleBtnClicked);
	connect(ui->onlineBtn, &QPushButton::clicked, this, &MainMenuWdt::onlineBtnClicked);
	connect(ui->exitBtn, &QPushButton::clicked, this, &MainMenuWdt::exitBtnClicked);
}

MainMenuWdt::~MainMenuWdt()
{
	delete ui;
}

void MainMenuWdt::singleBtnClicked()
{
	emit singleSignal();
}

void MainMenuWdt::onlineBtnClicked()
{
	emit onlineSignal();
}

void MainMenuWdt::exitBtnClicked()
{
	emit exitSignal();
}
