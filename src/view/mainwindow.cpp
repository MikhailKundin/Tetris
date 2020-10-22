#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../controller/generalcontroller.h"

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
	
	singleWgt = std::make_shared<SingleWgt>(ROW_COUNT, COLUMN_COUNT);
	mainMenuWdt = std::make_unique<MainMenuWdt>();
	
	connect(mainMenuWdt.get(), &MainMenuWdt::exitSignal, this, &MainWindow::closeAll);
	connect(mainMenuWdt.get(), &MainMenuWdt::singleSignal, this, &MainWindow::openSingleLayout);
	
	openMainMenuLayout();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::openMainMenuLayout()
{
	singleWgt->setParent(nullptr);
	
	ui->scenePlace = mainMenuWdt.get();
	ui->scenePlace->setMinimumSize(mainMenuWdt->size());
	ui->gBox->addWidget(ui->scenePlace, 1, 1);
}

void MainWindow::openSingleLayout()
{
	mainMenuWdt->setParent(nullptr);
	
	ui->scenePlace = singleWgt.get();
	ui->scenePlace->setMinimumSize(singleWgt->size());
	ui->gBox->addWidget(ui->scenePlace, 1, 1);
	
	GeneralController *controller = new GeneralController(ROW_COUNT, COLUMN_COUNT);
	singleWgt->update(controller->getMap());
	connect(controller, &GeneralController::update, singleWgt.get(), &SingleWgt::update);
	connect(controller, &GeneralController::defeatSignal, this, &MainWindow::deleteController);
}

void MainWindow::openOnlineLayout()
{
	
}

void MainWindow::closeAll()
{
	close();
}

void MainWindow::deleteController(GeneralController *controller)
{
	delete controller;
}
