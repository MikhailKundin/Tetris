#include "MainMenuWgt.h"
#include "ui_mainmenuwgt.h"

#include <QPushButton>

MainMenuWgt::MainMenuWgt(QWidget *parent) :
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
	
	connect(ui->singleBtn, &QPushButton::clicked, this, &MainMenuWgt::singleBtnClicked);
	connect(ui->onlineBtn, &QPushButton::clicked, this, &MainMenuWgt::onlineBtnClicked);
	connect(ui->exitBtn, &QPushButton::clicked, this, &MainMenuWgt::exitBtnClicked);
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
