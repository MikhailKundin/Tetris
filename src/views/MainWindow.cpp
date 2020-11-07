#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QKeyEvent>
#include <QShortcut>
#include <QApplication>
#include <QScreen>

#include "MainMenuWgt.h"
#include "SingleWgt.h"
#include "../controllers/GeneralController.h"
#include "../controllers/OfflineController.h"
#include "../TetrisInfo.h"

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
	
	blocks.insert(TetrisInfo::Figures::I, new QImage(":Images/Blocks/IBlockOriginal.png"));
	blocks.insert(TetrisInfo::Figures::O, new QImage(":Images/Blocks/OBlockOriginal.png"));
	blocks.insert(TetrisInfo::Figures::T, new QImage(":Images/Blocks/TBlockOriginal.png"));
	blocks.insert(TetrisInfo::Figures::L, new QImage(":Images/Blocks/LBlockOriginal.png"));
	blocks.insert(TetrisInfo::Figures::J, new QImage(":Images/Blocks/JBlockOriginal.png"));
	blocks.insert(TetrisInfo::Figures::S, new QImage(":Images/Blocks/SBlockOriginal.png"));
	blocks.insert(TetrisInfo::Figures::Z, new QImage(":Images/Blocks/ZBlockOriginal.png"));
	
//	singleWgt = std::make_unique<SingleWgt>();
//	mainMenuWdt = std::make_unique<MainMenuWgt>();
	
//	connect(mainMenuWdt.get(), &MainMenuWgt::exitSignal, this, &MainWindow::closeAll);
//	connect(mainMenuWdt.get(), &MainMenuWgt::singleSignal, this, &MainWindow::openSingleLayout);
	
	openMainMenuLayout();
}

MainWindow::~MainWindow()
{
	delete ui;
	
	foreach (QImage *block, blocks)
	{
		delete block;
	}
	
	//delete generalCtrlOffline;
	//delete offlineCtrl;
}

void MainWindow::openMainMenuLayout()
{
	emit newLayout();
	
	MainMenuWgt *mainMenuWgt = new MainMenuWgt;
	ui->scenePlace = mainMenuWgt;
	ui->scenePlace->setMinimumSize(mainMenuWgt->size());
	ui->gBox->addWidget(ui->scenePlace, 1, 1);
	
	connect(mainMenuWgt, &MainMenuWgt::exitSignal, this, &MainWindow::closeAll);
	connect(mainMenuWgt, &MainMenuWgt::singleSignal, this, &MainWindow::openSingleLayout);
	connect(mainMenuWgt, &MainMenuWgt::onlineSignal, this, &MainWindow::openOnlineLayout);
	connect(this, &MainWindow::newLayout, mainMenuWgt, &MainMenuWgt::deleteLater);
}

void MainWindow::openSingleLayout()
{
	emit newLayout();
	
	SingleWgt *singleWgt = new SingleWgt;
	GeneralController *generalCtrl = new GeneralController(blocks);
	OfflineController *offlineCtrl = new OfflineController;
	
	ui->scenePlace = singleWgt;
	ui->scenePlace->setMinimumSize(singleWgt->size());
	ui->gBox->addWidget(ui->scenePlace, 1, 1);
	
	connect(singleWgt, &SingleWgt::resumeSignal, generalCtrl, &GeneralController::start);
	connect(singleWgt, &SingleWgt::resumeSignal, offlineCtrl, &OfflineController::resume);
	connect(singleWgt, &SingleWgt::pauseSignal, generalCtrl, &GeneralController::stop);
	connect(singleWgt, &SingleWgt::pauseSignal, offlineCtrl, &OfflineController::pause);
	connect(singleWgt, &SingleWgt::restartSignal, generalCtrl, &GeneralController::restart);
	connect(singleWgt, &SingleWgt::restartSignal, offlineCtrl, &OfflineController::restart);
	connect(singleWgt, &SingleWgt::restartSignal, singleWgt, &SingleWgt::restart);
	connect(singleWgt, &SingleWgt::exitSignal, generalCtrl, &GeneralController::deleteLater);
	connect(singleWgt, &SingleWgt::exitSignal, offlineCtrl, &OfflineController::deleteLater);
	connect(singleWgt, &SingleWgt::exitSignal, this, &MainWindow::openMainMenuLayout);
	
	connect(generalCtrl, &GeneralController::update, singleWgt, &SingleWgt::updateGrid);
	connect(generalCtrl, &GeneralController::newPointsSignal, singleWgt, &SingleWgt::updatePoints);
	connect(generalCtrl, &GeneralController::newLevelSignal, singleWgt, &SingleWgt::updateLevel);
	connect(generalCtrl, &GeneralController::newFigureSignal, singleWgt, &SingleWgt::updateFigure);
	connect(generalCtrl, &GeneralController::defeatSignal, generalCtrl, &GeneralController::stop);
	connect(generalCtrl, &GeneralController::defeatSignal, offlineCtrl, &OfflineController::stop);
	connect(generalCtrl, &GeneralController::defeatSignal, singleWgt, &SingleWgt::defeat);
	connect(generalCtrl, &GeneralController::newLevelSignal, offlineCtrl, &OfflineController::newLevel);
	connect(generalCtrl, &GeneralController::newFigureSignal, offlineCtrl, &OfflineController::getNewFigure);
	
	connect(offlineCtrl, &OfflineController::tickSignal, generalCtrl, &GeneralController::newTick);
	connect(offlineCtrl, &OfflineController::newFigureSignal, generalCtrl, &GeneralController::setThirdFigure);
	
	connect(this, &MainWindow::moveRightSignal, generalCtrl, &GeneralController::moveRight);
	connect(this, &MainWindow::moveLeftSignal, generalCtrl, &GeneralController::moveLeft);
	connect(this, &MainWindow::moveDownSignal, generalCtrl, &GeneralController::newTick);
	connect(this, &MainWindow::rotateSignal, generalCtrl, &GeneralController::rotate);
	connect(this, &MainWindow::pauseBtnPress, singleWgt, &SingleWgt::pauseBtnPress);
	connect(this, &MainWindow::newLayout, singleWgt, &SingleWgt::deleteLater);
	
	generalCtrl->restart();
	offlineCtrl->restart();
}

void MainWindow::openOnlineLayout()
{
	
}

void MainWindow::closeAll()
{
	emit newLayout();
	close();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
	int key = e->key();
	
	if (key == Qt::Key_Escape)
	{
		emit pauseBtnPress();
		return;
	}
	
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

//void MainWindow::makeOfflineConnections(SingleWgt *singleWgt, GeneralController *generalCtrl, 
//										OfflineController *offlineCtrl)
//{
//	connect(singleWgt, &SingleWgt::resumeSignal, this, &MainWindow::singleResume);
//	connect(singleWgt, &SingleWgt::resumeSignal, generalCtrl, &GeneralController::start);
//	connect(singleWgt, &SingleWgt::resumeSignal, offlineCtrl, &OfflineController::resume);
//	connect(singleWgt, &SingleWgt::pauseSignal, generalCtrl, &GeneralController::stop);
//	connect(singleWgt, &SingleWgt::pauseSignal, offlineCtrl, &OfflineController::pause);
//	connect(singleWgt, &SingleWgt::restartSignal, generalCtrl, &GeneralController::restart);
//	connect(singleWgt, &SingleWgt::restartSignal, offlineCtrl, &OfflineController::restart);
//	connect(singleWgt, &SingleWgt::restartSignal, singleWgt, &SingleWgt::restart);
//	connect(singleWgt, &SingleWgt::exitSignal, generalCtrl, &GeneralController::deleteLater);
//	connect(singleWgt, &SingleWgt::exitSignal, offlineCtrl, &OfflineController::deleteLater);
//	connect(singleWgt, &SingleWgt::exitSignal, this, &MainWindow::openMainMenuLayout);
	
//	connect(generalCtrl, &GeneralController::update, singleWgt, &SingleWgt::updateGrid);
//	connect(generalCtrl, &GeneralController::newPointsSignal, singleWgt, &SingleWgt::updatePoints);
//	connect(generalCtrl, &GeneralController::newLevelSignal, singleWgt, &SingleWgt::updateLevel);
//	connect(generalCtrl, &GeneralController::newFigureSignal, singleWgt, &SingleWgt::updateFigure);
//	connect(generalCtrl, &GeneralController::defeatSignal, generalCtrl, &GeneralController::stop);
//	connect(generalCtrl, &GeneralController::defeatSignal, offlineCtrl, &OfflineController::stop);
//	connect(generalCtrl, &GeneralController::defeatSignal, singleWgt, &SingleWgt::defeat);
//	connect(generalCtrl, &GeneralController::newLevelSignal, offlineCtrl, &OfflineController::newLevel);
//	connect(generalCtrl, &GeneralController::newFigureSignal, offlineCtrl, &OfflineController::getNewFigure);
	
//	connect(offlineCtrl, &OfflineController::tickSignal, generalCtrl, &GeneralController::newTick);
//	connect(offlineCtrl, &OfflineController::newFigureSignal, generalCtrl, &GeneralController::setThirdFigure);
	
//	connect(this, &MainWindow::moveRightSignal, generalCtrl, &GeneralController::moveRight);
//	connect(this, &MainWindow::moveLeftSignal, generalCtrl, &GeneralController::moveLeft);
//	connect(this, &MainWindow::moveDownSignal, generalCtrl, &GeneralController::newTick);
//	connect(this, &MainWindow::rotateSignal, generalCtrl, &GeneralController::rotate);
//	connect(this, &MainWindow::pauseBtnPress, singleWgt, &SingleWgt::pauseBtnPress);
//}

//void MainWindow::singleDisconnect()
//{
//	disconnect(generalCtrlOffline, &GeneralController::update, singleWgt.get(), &SingleWgt::updateGrid);
//	disconnect(generalCtrlOffline, &GeneralController::newPointsSignal, singleWgt.get(), &SingleWgt::updatePoints);
//	disconnect(generalCtrlOffline, &GeneralController::newLevelSignal, singleWgt.get(), &SingleWgt::updateLevel);
//	disconnect(generalCtrlOffline, &GeneralController::newFigureSignal, singleWgt.get(), &SingleWgt::updateFigure);
//	disconnect(generalCtrlOffline, &GeneralController::defeatSignal, this, &MainWindow::singleDefeat);

//	disconnect(this, &MainWindow::moveRightSignal, generalCtrlOffline, &GeneralController::moveRight);
//	disconnect(this, &MainWindow::moveLeftSignal, generalCtrlOffline, &GeneralController::moveLeft);
//	disconnect(this, &MainWindow::moveDownSignal, generalCtrlOffline, &GeneralController::newTick);
//	disconnect(this, &MainWindow::rotateSignal, generalCtrlOffline, &GeneralController::rotate);
	
//	disconnect(this, &MainWindow::pauseBtnPress, singleWgt.get(), &SingleWgt::pauseBtnPress);
//	disconnect(singleWgt.get(), &SingleWgt::resumeSignal, this, &MainWindow::singleResume);
//	disconnect(singleWgt.get(), &SingleWgt::pauseSignal, this, &MainWindow::singlePause);
//	disconnect(singleWgt.get(), &SingleWgt::restartSignal, this, &MainWindow::singleRestart);
//	disconnect(singleWgt.get(), &SingleWgt::exitSignal, this, &MainWindow::singleExit);

//	disconnect(offlineCtrl, &OfflineController::tickSignal, generalCtrlOffline, &GeneralController::newTick);
//	disconnect(generalCtrlOffline, &GeneralController::newLevelSignal, offlineCtrl, &OfflineController::newLevel);
//	disconnect(generalCtrlOffline, &GeneralController::newFigureSignal, 
//			   offlineCtrl, &OfflineController::getNewFigure);
//	disconnect(offlineCtrl, &OfflineController::newFigureSignal, 
//			   generalCtrlOffline, &GeneralController::setThirdFigure);
//}
