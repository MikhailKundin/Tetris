#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>

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
	connect(controller, &GeneralController::update, singleWgt.get(), &SingleWgt::update);
	connect(controller, &GeneralController::defeatSignal, this, &MainWindow::deleteController);
	connect(this, &MainWindow::moveRightSignal, controller, &GeneralController::moveRight);
	connect(this, &MainWindow::moveLeftSignal, controller, &GeneralController::moveLeft);
	connect(this, &MainWindow::moveDownSignal, controller, &GeneralController::moveDown);
	connect(this, &MainWindow::rotateSignal, controller, &GeneralController::rotate);
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

void MainWindow::keyPressEvent(QKeyEvent *e)
{
	int key = e->key();
	switch(key)
	{
	case Qt::Key_Up:
	case Qt::Key_W:
		emit rotateSignal();
		break;
	case Qt::Key_Down:
	case Qt::Key_S:
		emit moveDownSignal();
		break;
	case Qt::Key_Right:
	case Qt::Key_D:
		emit moveRightSignal();
		break;
	case Qt::Key_Left:
	case Qt::Key_A:
		emit moveLeftSignal();
		break;
	}
}
