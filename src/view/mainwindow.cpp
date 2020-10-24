#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QKeyEvent>
#include <QShortcut>

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
	
	blocks.insert(GeneralController::Figures::I, new QImage(":Images/Blocks/IBlockOriginal.png"));
	blocks.insert(GeneralController::Figures::O, new QImage(":Images/Blocks/OBlockOriginal.png"));
	blocks.insert(GeneralController::Figures::T, new QImage(":Images/Blocks/TBlockOriginal.png"));
	blocks.insert(GeneralController::Figures::L, new QImage(":Images/Blocks/LBlockOriginal.png"));
	blocks.insert(GeneralController::Figures::J, new QImage(":Images/Blocks/JBlockOriginal.png"));
	blocks.insert(GeneralController::Figures::S, new QImage(":Images/Blocks/SBlockOriginal.png"));
	blocks.insert(GeneralController::Figures::Z, new QImage(":Images/Blocks/ZBlockOriginal.png"));
	
	rightDownArr = std::make_unique<QShortcut>(this);
	leftDownArr = std::make_unique<QShortcut>(this);
	rightDownEng = std::make_unique<QShortcut>(this);
	leftDownEng = std::make_unique<QShortcut>(this);
	rightDownRus = std::make_unique<QShortcut>(this);
	leftDownRus = std::make_unique<QShortcut>(this);
	
	rightDownArr->setKey(Qt::Key_Right + Qt::Key_Down);
	leftDownArr->setKey(Qt::Key_Left + Qt::Key_Down);
	rightDownEng->setKey(Qt::Key_D + Qt::Key_S);
	
	singleWgt = std::make_unique<SingleWgt>(ROW_COUNT, COLUMN_COUNT);
	mainMenuWdt = std::make_unique<MainMenuWdt>();
	
	connect(mainMenuWdt.get(), &MainMenuWdt::exitSignal, this, &MainWindow::closeAll);
	connect(mainMenuWdt.get(), &MainMenuWdt::singleSignal, this, &MainWindow::openSingleLayout);
	
	openMainMenuLayout();
}

MainWindow::~MainWindow()
{
	delete ui;
	
	foreach (QImage *block, blocks)
	{
		delete block;
	}
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
	
	GeneralController *controller = new GeneralController(ROW_COUNT, COLUMN_COUNT, blocks);
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
	QString keyText = e->text();
	if (keyText == "ц")
	{
		key = Qt::Key_W;
	}
	else if (keyText == "ы")
	{
		key = Qt::Key_S;
	}
	else if (keyText == "в")
	{
		key = Qt::Key_D;
	}
	else if (keyText == "ф")
	{
		key = Qt::Key_A;
	}
	
	if (!keyList.contains(key))
	{
		keyList.append(key);
	}
	
	foreach (key, keyList)
	{
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
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
	int key = e->key();
	QString keyText = e->text();
	if (keyText == "ц")
	{
		key = Qt::Key_W;
	}
	else if (keyText == "ы")
	{
		key = Qt::Key_S;
	}
	else if (keyText == "в")
	{
		key = Qt::Key_D;
	}
	else if (keyText == "ф")
	{
		key = Qt::Key_A;
	}
	
	qint32 index = index = keyList.indexOf(key);
	if (index != -1)
	{
		keyList.removeAt(index);
	}
}
