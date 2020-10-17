#include "mainmenuwdt.h"
#include "ui_mainmenuwdt.h"

MainMenuWdt::MainMenuWdt(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MainMenuWdt)
{
	ui->setupUi(this);
	
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
