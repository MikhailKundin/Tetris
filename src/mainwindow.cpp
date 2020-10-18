#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	
	QPalette pal(palette());
	pal.setColor(QPalette::Background, Qt::black);
	setAutoFillBackground(true);
	setPalette(pal);
	
	ui->mainMenuScene->setVisible(false);
	mainMenuWdt = std::make_unique<MainMenuWdt>(ui->mainMenuWdtPlace);
	ui->mainMenuWdtPlace->setMinimumSize(mainMenuWdt->size());
	connect(mainMenuWdt.get(), &MainMenuWdt::exitSignal, this, &MainWindow::closeAll);
	connect(mainMenuWdt.get(), &MainMenuWdt::singleSignal, this, &MainWindow::openSingleLayout);
	
	ui->singleScene->setVisible(false);
	singleWdt = std::make_unique<SingleWgt>(ui->singleWgtPlace);
	ui->singleWgtPlace->setMinimumSize(singleWdt->size());
	
	openMainMenuLayout();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::openMainMenuLayout()
{
	ui->mainWidget->setLayout(ui->mainMenuBox);
	ui->singleScene->setVisible(false);
	
	//ui->mainMenuScene->setVisible(true);
}

void MainWindow::openSingleLayout()
{
	//ui->mainWidget->setLayout(ui->singleBox);
	ui->singleBox->setParent(ui->mainMenuBox);
	ui->mainMenuScene->setVisible(false);
	
	ui->singleScene->setVisible(true);
}

void MainWindow::openOnlineLayout()
{
	
}

void MainWindow::closeAll()
{
	close();
}
