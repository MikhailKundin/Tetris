#include "mainmenuwdt.h"
#include "ui_mainmenuwdt.h"

MainMenuWdt::MainMenuWdt(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::MainMenuWdt)
{
	ui->setupUi(this);
}

MainMenuWdt::~MainMenuWdt()
{
	delete ui;
}
