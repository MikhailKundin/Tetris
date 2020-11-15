#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QKeyEvent>
#include <QThread>

#include "MainMenuWgt.h"
#include "SingleWgt.h"
#include "OnlineWgt.h"
#include "../controllers/GeneralController.h"
#include "../controllers/OfflineController.h"
#include "../controllers/OnlineController.h"
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
	
	connect(singleWgt, &SingleWgt::resumeSignal, [=]()
	{
		generalCtrl->start();
		offlineCtrl->resume();
	});
	connect(singleWgt, &SingleWgt::pauseSignal, [=]()
	{
		generalCtrl->stop();
		offlineCtrl->pause();
	});
	connect(singleWgt, &SingleWgt::restartSignal, [=]()
	{
		generalCtrl->clearFigure();
		generalCtrl->restart();
		offlineCtrl->restart();
		singleWgt->restart();
	});
	connect(singleWgt, &SingleWgt::exitSignal, [=]()
	{
		generalCtrl->deleteLater();
		offlineCtrl->deleteLater();
		openMainMenuLayout();
	});
	
	connect(generalCtrl, &GeneralController::moveDownSignal, generalCtrl, &GeneralController::newTick);
	connect(generalCtrl, &GeneralController::update, singleWgt, &SingleWgt::updateGrid);
	connect(generalCtrl, &GeneralController::newPointsSignal, singleWgt, &SingleWgt::updatePoints);
	connect(generalCtrl, &GeneralController::newLevelSignal, [=](quint16 level)
	{
		offlineCtrl->newLevel(level);
		singleWgt->updateLevel(level);
	});
	connect(generalCtrl, &GeneralController::getNewFigureSignal, offlineCtrl, &OfflineController::getNewFigure);
	connect(generalCtrl, &GeneralController::newFigureSignal, singleWgt, &SingleWgt::updateFigure);
	connect(generalCtrl, &GeneralController::defeatSignal, [=]()
	{
		generalCtrl->stop();
		offlineCtrl->stop();
		singleWgt->defeat();
	});
	
	connect(offlineCtrl, &OfflineController::tickSignal, generalCtrl, &GeneralController::newTick);
	connect(offlineCtrl, &OfflineController::newFigureSignal, generalCtrl, &GeneralController::getNextFigure);
	
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
	emit newLayout();
	
	OnlineWgt *onlineWgt = new OnlineWgt;
	GeneralController *ofGeneralCtrl = new GeneralController(blocks);
	GeneralController *onGeneralCtrl = new GeneralController(blocks);
	OfflineController *offlineCtrl = new OfflineController;
	OnlineController *onlineCtrl = new OnlineController;
	
	offlineCtrl->stop();
	ofGeneralCtrl->stop();
	onGeneralCtrl->stop();
	onlineCtrl->stop();
	
	ui->scenePlace = onlineWgt;
	ui->scenePlace->setMinimumSize(onlineWgt->size());
	ui->gBox->addWidget(ui->scenePlace, 1, 1);
	
	connect(onlineWgt, &OnlineWgt::exitSignal, ofGeneralCtrl, &GeneralController::deleteLater);
	connect(onlineWgt, &OnlineWgt::exitSignal, onGeneralCtrl, &GeneralController::deleteLater);
	connect(onlineWgt, &OnlineWgt::exitSignal, offlineCtrl, &OfflineController::deleteLater);
	connect(onlineWgt, &OnlineWgt::exitSignal, onlineCtrl, &OnlineController::deleteLater);
	connect(onlineWgt, &OnlineWgt::exitSignal, this, &MainWindow::openMainMenuLayout);
	connect(onlineWgt, &OnlineWgt::makeServerSignal, onlineCtrl, &OnlineController::makeServer);
	connect(onlineWgt, &OnlineWgt::makeClientSignal, onlineCtrl, &OnlineController::makeClient);
	connect(onlineWgt, &OnlineWgt::cancelWaitingSignal, onlineCtrl, &OnlineController::deleteServer);
	connect(onlineWgt, &OnlineWgt::cancelConnectingSignal, onlineCtrl, &OnlineController::deleteSocket);
	connect(onlineWgt, &OnlineWgt::readySignal, onlineCtrl, &OnlineController::ready);
	connect(onlineWgt, &OnlineWgt::disconnectSignal, onlineCtrl, &OnlineController::disconnectSocket);
	connect(onlineWgt, &OnlineWgt::disconnectSignal, ofGeneralCtrl, &GeneralController::stop);
	connect(onlineWgt, &OnlineWgt::disconnectSignal, onGeneralCtrl, &GeneralController::stop);
	connect(onlineWgt, &OnlineWgt::disconnectSignal, offlineCtrl, &OfflineController::stop);
	connect(onlineWgt, &OnlineWgt::startGame, [=]()
	{
		onlineCtrl->start();
		onGeneralCtrl->clearGrid();
		ofGeneralCtrl->clearFigure();
		ofGeneralCtrl->restart();
		onGeneralCtrl->restart();
		offlineCtrl->restart();
	});
	connect(onlineWgt, &OnlineWgt::stopSignal, ofGeneralCtrl, &GeneralController::stop);
	connect(onlineWgt, &OnlineWgt::stopSignal, onGeneralCtrl, &GeneralController::stop);
	connect(onlineWgt, &OnlineWgt::stopSignal, onGeneralCtrl, &GeneralController::clearFigure);
	connect(onlineWgt, &OnlineWgt::stopSignal, offlineCtrl, &OfflineController::stop);
	
	connect(ofGeneralCtrl, &GeneralController::defeatSignal, onlineCtrl, [=](){
		onlineCtrl->defeat();
		onlineCtrl->stop();
	});
	connect(ofGeneralCtrl, &GeneralController::moveDownSignal, onlineCtrl, &OnlineController::moveDown);
	connect(ofGeneralCtrl, &GeneralController::moveDownSignal, ofGeneralCtrl, &GeneralController::newTick);
	connect(ofGeneralCtrl, &GeneralController::update, onlineWgt, &OnlineWgt::ofUpdateGrid);
	connect(ofGeneralCtrl, &GeneralController::newPointsSignal, onlineWgt, &OnlineWgt::ofUpdatePoints);
	connect(ofGeneralCtrl, &GeneralController::newLevelSignal, onlineWgt, &OnlineWgt::ofUpdateLevel);
	connect(ofGeneralCtrl, &GeneralController::newLevelSignal, offlineCtrl, &OfflineController::newLevel);
	connect(ofGeneralCtrl, &GeneralController::newFigureSignal, onlineWgt, &OnlineWgt::ofUpdateFigure);
	connect(ofGeneralCtrl, &GeneralController::getNewFigureSignal, offlineCtrl, &OfflineController::getNewFigure);
	connect(ofGeneralCtrl, &GeneralController::defeatSignal, ofGeneralCtrl, &GeneralController::stop);
	connect(ofGeneralCtrl, &GeneralController::defeatSignal, onlineWgt, &OnlineWgt::ofDefeat);
	connect(ofGeneralCtrl, &GeneralController::defeatSignal, offlineCtrl, &OfflineController::stop);
	
	connect(onGeneralCtrl, &GeneralController::update, onlineWgt, &OnlineWgt::onUpdateGrid);
	connect(onGeneralCtrl, &GeneralController::newPointsSignal, onlineWgt, &OnlineWgt::onUpdatePoints);
	connect(onGeneralCtrl, &GeneralController::newLevelSignal, onlineWgt, &OnlineWgt::onUpdateLevel);
	connect(onGeneralCtrl, &GeneralController::newFigureSignal, onlineWgt, &OnlineWgt::onUpdateFigure);
	connect(onGeneralCtrl, &GeneralController::defeatSignal, onGeneralCtrl, &GeneralController::stop);
	connect(onGeneralCtrl, &GeneralController::defeatSignal, onGeneralCtrl, &GeneralController::clearFigure);
	
	connect(offlineCtrl, &OfflineController::tickSignal, onlineCtrl, &OnlineController::moveDown);
	connect(offlineCtrl, &OfflineController::newFigureSignal, onlineCtrl, &OnlineController::newFigure);
	connect(offlineCtrl, &OfflineController::tickSignal, ofGeneralCtrl, &GeneralController::newTick);
	connect(offlineCtrl, &OfflineController::newFigureSignal, ofGeneralCtrl, &GeneralController::getNextFigure);
	
	connect(onlineCtrl, &OnlineController::moveDownSignal, onGeneralCtrl, &GeneralController::newTick);
	connect(onlineCtrl, &OnlineController::rotateSignal, onGeneralCtrl, &GeneralController::rotate);
	connect(onlineCtrl, &OnlineController::moveRightSignal, onGeneralCtrl, &GeneralController::moveRight);
	connect(onlineCtrl, &OnlineController::moveLeftSignal, onGeneralCtrl, &GeneralController::moveLeft);
	connect(onlineCtrl, &OnlineController::newFigureSignal, onGeneralCtrl, &GeneralController::getNextFigure);
	connect(onlineCtrl, &OnlineController::cannotConnectSignal, onlineWgt, &OnlineWgt::disconnected);
	connect(onlineCtrl, &OnlineController::connectedSignal, onlineWgt, &OnlineWgt::connected);
	connect(onlineCtrl, &OnlineController::readySignal, onlineWgt, &OnlineWgt::ready);
	connect(onlineCtrl, &OnlineController::defeatSignal, onlineWgt, &OnlineWgt::onDefeat);
	connect(onlineCtrl, &OnlineController::disconnectSignal, onlineWgt, &OnlineWgt::disconnected);
	connect(onlineCtrl, &OnlineController::disconnectSignal, onlineWgt, &OnlineWgt::clear);
	connect(onlineCtrl, &OnlineController::disconnectSignal, ofGeneralCtrl, &GeneralController::stop);
	connect(onlineCtrl, &OnlineController::disconnectSignal, onGeneralCtrl, &GeneralController::stop);
	connect(onlineCtrl, &OnlineController::disconnectSignal, onGeneralCtrl, &GeneralController::clearFigure);
	connect(onlineCtrl, &OnlineController::disconnectSignal, offlineCtrl, &OfflineController::stop);
	
	connect(this, &MainWindow::moveRightSignal, onlineCtrl, &OnlineController::moveRight);
	connect(this, &MainWindow::moveLeftSignal, onlineCtrl, &OnlineController::moveLeft);
	connect(this, &MainWindow::rotateSignal, onlineCtrl, &OnlineController::rotate);
	connect(this, &MainWindow::moveDownSignal, onlineCtrl, &OnlineController::moveDown);
	connect(this, &MainWindow::moveRightSignal, ofGeneralCtrl, &GeneralController::moveRight);
	connect(this, &MainWindow::moveLeftSignal, ofGeneralCtrl, &GeneralController::moveLeft);
	connect(this, &MainWindow::moveDownSignal, ofGeneralCtrl, &GeneralController::newTick);
	connect(this, &MainWindow::rotateSignal, ofGeneralCtrl, &GeneralController::rotate);
	connect(this, &MainWindow::newLayout, onlineWgt, &OnlineWgt::deleteLater);
	connect(this, &MainWindow::pauseBtnPress, onlineWgt, &OnlineWgt::escBtnPress);
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
	
	qint32 index = keyList.indexOf(key);
	if (index != -1)
	{
		keyList.removeAt(index);
	}
}
