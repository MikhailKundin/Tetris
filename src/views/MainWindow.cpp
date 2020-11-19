#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QKeyEvent>
#include <QThread>
#include <QMetaMethod>

#include "MainMenuWgt.h"
#include "SingleWgt.h"
#include "OnlineWgt.h"
#include "../controllers/GeneralController.h"
#include "../controllers/OfflineController.h"
#include "../controllers/OnlineController.h"
#include "../controllers/SoundController.h"
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
	emit destroySignal();
	
	delete ui;
	
	foreach (QImage *block, blocks)
	{
		delete block;
	}
	
}

void MainWindow::openMainMenuLayout()
{
	emit newLayout();
	
	SoundController *soundController = new SoundController(SoundController::MainMenu);
	
	QThread *soundThread = new QThread(this);
	soundController->moveToThread(soundThread);
	
	MainMenuWgt *mainMenuWgt = new MainMenuWgt;
	ui->scenePlace = mainMenuWgt;
	ui->scenePlace->setMinimumSize(mainMenuWgt->size());
	ui->gBox->addWidget(ui->scenePlace, 1, 1);
	
	connect(mainMenuWgt, &MainMenuWgt::exitSignal, soundController, &SoundController::deleteLater);
	connect(mainMenuWgt, &MainMenuWgt::exitSignal, this, &MainWindow::closeAll);
	connect(mainMenuWgt, &MainMenuWgt::singleSignal, soundController, &SoundController::deleteLater);
	connect(mainMenuWgt, &MainMenuWgt::singleSignal, this, &MainWindow::openSingleLayout);
	connect(mainMenuWgt, &MainMenuWgt::onlineSignal, soundController, &SoundController::deleteLater);
	connect(mainMenuWgt, &MainMenuWgt::onlineSignal, this, &MainWindow::openOnlineLayout);
	
	connect(soundController, &SoundController::destroyed, soundThread, &QThread::quit);
	
	connect(this, &MainWindow::newLayout, mainMenuWgt, &MainMenuWgt::deleteLater);
	connect(this, &MainWindow::destroySignal, soundThread, [=]()
	{
		disconnect(soundThread, &QThread::finished, soundThread, &QThread::deleteLater);
		
		soundThread->terminate();
	});
	
	connect(soundThread, &QThread::started, soundController, &SoundController::playMainTheme);
	connect(soundThread, &QThread::finished, soundThread, &QThread::deleteLater);
	
	soundThread->start();
}

void MainWindow::openSingleLayout()
{
	emit newLayout();
	
	SingleWgt *singleWgt = new SingleWgt;
	GeneralController *generalCtrl = new GeneralController(blocks);
	OfflineController *offlineCtrl = new OfflineController;
	SoundController *soundCtrl = new SoundController(SoundController::Playground);
	
	QThread *ctrlThread = new QThread(this);
	QThread *soundThread = new QThread(this);
	
	generalCtrl->moveToThread(ctrlThread);
	offlineCtrl->moveToThread(ctrlThread);
	soundCtrl->moveToThread(soundThread);
	
	ui->scenePlace = singleWgt;
	ui->scenePlace->setMinimumSize(singleWgt->size());
	ui->gBox->addWidget(ui->scenePlace, 1, 1);
	
	connect(singleWgt, &SingleWgt::resumeSignal, offlineCtrl, &OfflineController::resume);
	connect(singleWgt, &SingleWgt::resumeSignal, generalCtrl, &GeneralController::start);
	connect(singleWgt, &SingleWgt::resumeSignal, soundCtrl, &SoundController::unmute);
	connect(singleWgt, &SingleWgt::pauseSignal, generalCtrl, &GeneralController::stop);
	connect(singleWgt, &SingleWgt::pauseSignal, offlineCtrl, &OfflineController::pause);
	connect(singleWgt, &SingleWgt::pauseSignal, soundCtrl, &SoundController::mute);
	connect(singleWgt, &SingleWgt::restartSignal, generalCtrl, &GeneralController::clearFigure);
	connect(singleWgt, &SingleWgt::restartSignal, generalCtrl, &GeneralController::restart);
	connect(singleWgt, &SingleWgt::restartSignal, offlineCtrl, &OfflineController::restart);
	connect(singleWgt, &SingleWgt::restartSignal, singleWgt, &SingleWgt::restart);
	connect(singleWgt, &SingleWgt::restartSignal, soundCtrl, &SoundController::unmute);
	connect(singleWgt, &SingleWgt::exitSignal, generalCtrl, &GeneralController::deleteLater);
	connect(singleWgt, &SingleWgt::exitSignal, offlineCtrl, &OfflineController::deleteLater);
	connect(singleWgt, &SingleWgt::exitSignal, soundCtrl, &SoundController::deleteLater);
	connect(singleWgt, &SingleWgt::exitSignal, this, &MainWindow::openMainMenuLayout);
	
	connect(generalCtrl, &GeneralController::moveDownSignal, generalCtrl, &GeneralController::newTick);
	connect(generalCtrl, &GeneralController::update, singleWgt, &SingleWgt::updateGrid);
	connect(generalCtrl, &GeneralController::newPointsSignal, singleWgt, &SingleWgt::updatePoints);
	connect(generalCtrl, &GeneralController::newPointsSignal, soundCtrl, &SoundController::rowDeleted);
	connect(generalCtrl, &GeneralController::newLevelSignal, offlineCtrl, &OfflineController::newLevel);
	connect(generalCtrl, &GeneralController::newLevelSignal, singleWgt, &SingleWgt::updateLevel);
	connect(generalCtrl, &GeneralController::getNewFigureSignal, offlineCtrl, &OfflineController::getNewFigure);
	connect(generalCtrl, &GeneralController::newFigureSignal, singleWgt, &SingleWgt::updateFigure);
	connect(generalCtrl, &GeneralController::defeatSignal, generalCtrl, &GeneralController::stop);
	connect(generalCtrl, &GeneralController::defeatSignal, offlineCtrl, &OfflineController::stop);
	connect(generalCtrl, &GeneralController::defeatSignal, singleWgt, &SingleWgt::defeat);
	connect(generalCtrl, &GeneralController::defeatSignal, soundCtrl, &SoundController::defeat);
	connect(generalCtrl, &GeneralController::rightSignal, soundCtrl, &SoundController::moveRight);
	connect(generalCtrl, &GeneralController::leftSignal, soundCtrl, &SoundController::moveLeft);
	connect(generalCtrl, &GeneralController::downSignal, soundCtrl, &SoundController::moveDown);
	connect(generalCtrl, &GeneralController::rotateSignal, soundCtrl, &SoundController::rotate);
	//connect(generalCtrl, &GeneralController::destroyed, ctrlThread, &QThread::quit);
	
	connect(offlineCtrl, &OfflineController::tickSignal, generalCtrl, &GeneralController::newTick);
	connect(offlineCtrl, &OfflineController::newFigureSignal, generalCtrl, &GeneralController::getNextFigure);
	connect(offlineCtrl, &OfflineController::destroyed, ctrlThread, &QThread::quit);
	
	connect(soundCtrl, &SoundController::destroyed, soundThread, &QThread::quit);
	
	connect(this, &MainWindow::moveRightSignal, generalCtrl, &GeneralController::moveRight);
	connect(this, &MainWindow::moveLeftSignal, generalCtrl, &GeneralController::moveLeft);
	connect(this, &MainWindow::moveDownSignal, generalCtrl, &GeneralController::newTick);
	connect(this, &MainWindow::rotateSignal, generalCtrl, &GeneralController::rotate);
	connect(this, &MainWindow::pauseBtnPress, singleWgt, &SingleWgt::pauseBtnPress);
	connect(this, &MainWindow::newLayout, singleWgt, &SingleWgt::deleteLater);
	connect(this, &MainWindow::destroySignal, this, [=]()
	{
		disconnect(ctrlThread, &QThread::finished, ctrlThread, &QThread::deleteLater);
		//disconnect(offlineThread, &QThread::finished, offlineThread, &QThread::deleteLater);
		disconnect(soundThread, &QThread::finished, soundThread, &QThread::deleteLater);
		
		ctrlThread->terminate();
		//offlineThread->terminate();
		soundThread->terminate();
	});
	
	connect(ctrlThread, &QThread::started, generalCtrl, &GeneralController::restart);
	connect(ctrlThread, &QThread::started, offlineCtrl, &OfflineController::restart);
	connect(ctrlThread, &QThread::finished, ctrlThread, &QThread::deleteLater);
	
	//connect(offlineThread, &QThread::started, offlineCtrl, &OfflineController::restart);
	//connect(offlineThread, &QThread::finished, offlineThread, &QThread::deleteLater);
	
	connect(soundThread, &QThread::finished, soundThread, &QThread::deleteLater);
	
	ctrlThread->start();
	soundThread->start();
	//offlineThread->start();
}

void MainWindow::openOnlineLayout()
{	
	emit newLayout();
	
	OnlineWgt *onlineWgt = new OnlineWgt;
	GeneralController *ofGeneralCtrl = new GeneralController(blocks);
	GeneralController *onGeneralCtrl = new GeneralController(blocks);
	OfflineController *offlineCtrl = new OfflineController;
	OnlineController *onlineCtrl = new OnlineController;
	SoundController *ofSoundCtrl = new SoundController(SoundController::Playground);
	SoundController *onSoundCtrl = new SoundController(SoundController::Playground);
	
//	QThread *ofGeneralThread = new QThread(this);
//	QThread *onGeneralThread = new QThread(this);
//	QThread *offlineThread = new QThread(this);
//	QThread *onlineThread = new QThread(this);
//	QThread *ctrlThread = new QThread(this);
	QThread *soundThread = new QThread(this);
	
//	ofGeneralCtrl->moveToThread(ctrlThread);
//	onGeneralCtrl->moveToThread(ctrlThread);
//	offlineCtrl->moveToThread(ctrlThread);
//	onlineCtrl->moveToThread(ctrlThread);
	ofSoundCtrl->moveToThread(soundThread);
	onSoundCtrl->moveToThread(soundThread);
	
	ui->scenePlace = onlineWgt;
	ui->scenePlace->setMinimumSize(onlineWgt->size());
	ui->gBox->addWidget(ui->scenePlace, 1, 1);
	
	connect(onlineWgt, &OnlineWgt::exitSignal, ofGeneralCtrl, &GeneralController::deleteLater);
	connect(onlineWgt, &OnlineWgt::exitSignal, onGeneralCtrl, &GeneralController::deleteLater);
	connect(onlineWgt, &OnlineWgt::exitSignal, offlineCtrl, &OfflineController::deleteLater);
	connect(onlineWgt, &OnlineWgt::exitSignal, onlineCtrl, &OnlineController::deleteLater);
	connect(onlineWgt, &OnlineWgt::exitSignal, ofSoundCtrl, &SoundController::deleteLater);
	connect(onlineWgt, &OnlineWgt::exitSignal, onSoundCtrl, &SoundController::deleteLater);
	connect(onlineWgt, &OnlineWgt::exitSignal, this, &MainWindow::openMainMenuLayout);
	connect(onlineWgt, &OnlineWgt::makeServerSignal, onlineCtrl, &OnlineController::makeServer);
	connect(onlineWgt, &OnlineWgt::makeClientSignal, onlineCtrl, &OnlineController::makeClient);
	connect(onlineWgt, &OnlineWgt::cancelWaitingSignal, onlineCtrl, &OnlineController::deleteServer);
	connect(onlineWgt, &OnlineWgt::cancelConnectingSignal, onlineCtrl, &OnlineController::deleteSocket);
	connect(onlineWgt, &OnlineWgt::readySignal, onlineCtrl, &OnlineController::ready);
	connect(onlineWgt, &OnlineWgt::disconnectSignal, onlineCtrl, &OnlineController::disconnectSocket);
	connect(onlineWgt, &OnlineWgt::disconnectSignal, ofGeneralCtrl, &GeneralController::stop);
	connect(onlineWgt, &OnlineWgt::disconnectSignal, onGeneralCtrl, &GeneralController::stop);
	connect(onlineWgt, &OnlineWgt::disconnectSignal, onGeneralCtrl, &GeneralController::clearGrid);
	connect(onlineWgt, &OnlineWgt::disconnectSignal, onGeneralCtrl, &GeneralController::clearFigure);
	connect(onlineWgt, &OnlineWgt::disconnectSignal, offlineCtrl, &OfflineController::stop);
	connect(onlineWgt, &OnlineWgt::disconnectSignal, onlineWgt, &OnlineWgt::restart);
	connect(onlineWgt, &OnlineWgt::startGame, onlineCtrl, &OnlineController::start);
	connect(onlineWgt, &OnlineWgt::startGame, ofGeneralCtrl, &GeneralController::clearFigure);
	connect(onlineWgt, &OnlineWgt::startGame, ofGeneralCtrl, &GeneralController::restart);
	connect(onlineWgt, &OnlineWgt::startGame, onGeneralCtrl, &GeneralController::restart);
	connect(onlineWgt, &OnlineWgt::startGame, offlineCtrl, &OfflineController::restart);
	connect(onlineWgt, &OnlineWgt::startGame, onlineWgt, &OnlineWgt::restart);
	connect(onlineWgt, &OnlineWgt::stopSignal, ofGeneralCtrl, &GeneralController::stop);
	connect(onlineWgt, &OnlineWgt::stopSignal, onGeneralCtrl, &GeneralController::stop);
	connect(onlineWgt, &OnlineWgt::stopSignal, onGeneralCtrl, &GeneralController::clearFigure);
	connect(onlineWgt, &OnlineWgt::stopSignal, onGeneralCtrl, &GeneralController::clearGrid);
	connect(onlineWgt, &OnlineWgt::stopSignal, offlineCtrl, &OfflineController::stop);
	connect(onlineWgt, &OnlineWgt::escPnlSignal, ofSoundCtrl, &SoundController::setMute);
	connect(onlineWgt, &OnlineWgt::escPnlSignal, onSoundCtrl, &SoundController::setMute);
	
	connect(ofGeneralCtrl, &GeneralController::moveDownSignal, onlineCtrl, &OnlineController::moveDown);
	connect(ofGeneralCtrl, &GeneralController::moveDownSignal, ofGeneralCtrl, &GeneralController::newTick);
	connect(ofGeneralCtrl, &GeneralController::update, onlineWgt, &OnlineWgt::ofUpdateGrid);
	connect(ofGeneralCtrl, &GeneralController::newPointsSignal, onlineWgt, &OnlineWgt::ofUpdatePoints);
	connect(ofGeneralCtrl, &GeneralController::newPointsSignal, ofSoundCtrl, &SoundController::rowDeleted);
	connect(ofGeneralCtrl, &GeneralController::newLevelSignal, onlineWgt, &OnlineWgt::ofUpdateLevel);
	connect(ofGeneralCtrl, &GeneralController::newLevelSignal, offlineCtrl, &OfflineController::newLevel);
	connect(ofGeneralCtrl, &GeneralController::newFigureSignal, onlineWgt, &OnlineWgt::ofUpdateFigure);
	connect(ofGeneralCtrl, &GeneralController::getNewFigureSignal, offlineCtrl, &OfflineController::getNewFigure);
	connect(ofGeneralCtrl, &GeneralController::defeatSignal, onlineCtrl, &OnlineController::defeat);
	connect(ofGeneralCtrl, &GeneralController::defeatSignal, onlineCtrl, &OnlineController::stop);
	connect(ofGeneralCtrl, &GeneralController::defeatSignal, ofGeneralCtrl, &GeneralController::stop);
	connect(ofGeneralCtrl, &GeneralController::defeatSignal, onlineWgt, &OnlineWgt::ofDefeat);
	connect(ofGeneralCtrl, &GeneralController::defeatSignal, offlineCtrl, &OfflineController::stop);
	connect(ofGeneralCtrl, &GeneralController::defeatSignal, ofSoundCtrl, &SoundController::defeat);
	connect(ofGeneralCtrl, &GeneralController::downSignal, ofSoundCtrl, &SoundController::moveDown);
	connect(ofGeneralCtrl, &GeneralController::rotateSignal, ofSoundCtrl, &SoundController::rotate);
	connect(ofGeneralCtrl, &GeneralController::rightSignal, ofSoundCtrl, &SoundController::moveRight);
	connect(ofGeneralCtrl, &GeneralController::leftSignal, ofSoundCtrl, &SoundController::moveLeft);
	//connect(ofGeneralCtrl, &GeneralController::destroyed, ctrlThread, &QThread::quit);
	
	connect(onGeneralCtrl, &GeneralController::update, onlineWgt, &OnlineWgt::onUpdateGrid);
	connect(onGeneralCtrl, &GeneralController::newPointsSignal, onlineWgt, &OnlineWgt::onUpdatePoints);
	connect(onGeneralCtrl, &GeneralController::newPointsSignal, onSoundCtrl, &SoundController::rowDeleted);
	connect(onGeneralCtrl, &GeneralController::newLevelSignal, onlineWgt, &OnlineWgt::onUpdateLevel);
	connect(onGeneralCtrl, &GeneralController::newFigureSignal, onlineWgt, &OnlineWgt::onUpdateFigure);
	connect(onGeneralCtrl, &GeneralController::defeatSignal, onGeneralCtrl, &GeneralController::stop);
	connect(onGeneralCtrl, &GeneralController::defeatSignal, onGeneralCtrl, &GeneralController::clearFigure);
	connect(onGeneralCtrl, &GeneralController::defeatSignal, onGeneralCtrl, &GeneralController::clearGrid);
	connect(onGeneralCtrl, &GeneralController::downSignal, onSoundCtrl, &SoundController::moveDown);
	connect(onGeneralCtrl, &GeneralController::rotateSignal, onSoundCtrl, &SoundController::rotate);
	connect(onGeneralCtrl, &GeneralController::rightSignal, onSoundCtrl, &SoundController::moveRight);
	connect(onGeneralCtrl, &GeneralController::leftSignal, onSoundCtrl, &SoundController::moveLeft);
	//connect(onGeneralCtrl, &GeneralController::destroyed, onGeneralThread, &QThread::quit);
	
	connect(offlineCtrl, &OfflineController::tickSignal, onlineCtrl, &OnlineController::moveDown);
	connect(offlineCtrl, &OfflineController::tickSignal, ofGeneralCtrl, &GeneralController::newTick);
	connect(offlineCtrl, &OfflineController::newFigureSignal, onlineCtrl, &OnlineController::newFigure);
	connect(offlineCtrl, &OfflineController::newFigureSignal, ofGeneralCtrl, &GeneralController::getNextFigure);
	//connect(offlineCtrl, &OfflineController::destroyed, offlineThread, &QThread::quit);
	
	connect(onlineCtrl, &OnlineController::moveDownSignal, onGeneralCtrl, &GeneralController::newTick);
	connect(onlineCtrl, &OnlineController::rotateSignal, onGeneralCtrl, &GeneralController::rotate);
	connect(onlineCtrl, &OnlineController::moveRightSignal, onGeneralCtrl, &GeneralController::moveRight);
	connect(onlineCtrl, &OnlineController::moveLeftSignal, onGeneralCtrl, &GeneralController::moveLeft);
	connect(onlineCtrl, &OnlineController::newFigureSignal, onGeneralCtrl, &GeneralController::getNextFigure);
	connect(onlineCtrl, &OnlineController::cannotConnectSignal, onlineWgt, &OnlineWgt::disconnected);
	connect(onlineCtrl, &OnlineController::connectedSignal, onlineWgt, &OnlineWgt::connected);
	connect(onlineCtrl, &OnlineController::readySignal, onlineWgt, &OnlineWgt::ready);
	connect(onlineCtrl, &OnlineController::defeatSignal, onlineWgt, &OnlineWgt::onDefeat);
	connect(onlineCtrl, &OnlineController::defeatSignal, onSoundCtrl, &SoundController::defeat);
	connect(onlineCtrl, &OnlineController::disconnectSignal, onlineWgt, &OnlineWgt::disconnected);
	connect(onlineCtrl, &OnlineController::disconnectSignal, onlineWgt, &OnlineWgt::clear);
	connect(onlineCtrl, &OnlineController::disconnectSignal, ofGeneralCtrl, &GeneralController::stop);
	connect(onlineCtrl, &OnlineController::disconnectSignal, onGeneralCtrl, &GeneralController::stop);
	connect(onlineCtrl, &OnlineController::disconnectSignal, onGeneralCtrl, &GeneralController::clearFigure);
	connect(onlineCtrl, &OnlineController::disconnectSignal, onGeneralCtrl, &GeneralController::clearGrid);
	connect(onlineCtrl, &OnlineController::disconnectSignal, offlineCtrl, &OfflineController::stop);
	connect(onlineCtrl, &OnlineController::disconnectSignal, onlineWgt, &OnlineWgt::restart);
	//connect(onlineCtrl, &OnlineController::destroyed, onlineThread, &QThread::quit);
	
	connect(this, &MainWindow::newLayout, onlineWgt, &OnlineWgt::deleteLater);
	connect(this, &MainWindow::pauseBtnPress, onlineWgt, &OnlineWgt::escBtnPress);
	connect(this, &MainWindow::moveRightSignal, onlineCtrl, &OnlineController::moveRight);
	connect(this, &MainWindow::moveRightSignal, ofGeneralCtrl, &GeneralController::moveRight);
	connect(this, &MainWindow::moveLeftSignal, onlineCtrl, &OnlineController::moveLeft);
	connect(this, &MainWindow::moveLeftSignal, ofGeneralCtrl, &GeneralController::moveLeft);
	connect(this, &MainWindow::rotateSignal, onlineCtrl, &OnlineController::rotate);
	connect(this, &MainWindow::rotateSignal, ofGeneralCtrl, &GeneralController::rotate);
	connect(this, &MainWindow::moveDownSignal, onlineCtrl, &OnlineController::moveDown);
	connect(this, &MainWindow::moveDownSignal, ofGeneralCtrl, &GeneralController::newTick);
	connect(this, &MainWindow::destroySignal, this, [=]()
	{
		//disconnect(ctrlThread, &QThread::finished, ctrlThread, &QThread::deleteLater);
//		disconnect(onGeneralThread, &QThread::finished, onGeneralThread, &QThread::deleteLater);
//		disconnect(offlineThread, &QThread::finished, offlineThread, &QThread::deleteLater);
//		disconnect(onlineThread, &QThread::finished, onlineThread, &QThread::deleteLater);
		disconnect(soundThread, &QThread::finished, soundThread, &QThread::deleteLater);
//		disconnect(onSoundThread, &QThread::finished, onSoundThread, &QThread::deleteLater);
		
		//ctrlThread->quit();
//		onGeneralThread->quit();
//		offlineThread->quit();
//		onlineThread->quit();
		soundThread->quit();
//		onSoundThread->quit();
	});
	
//	connect(ofGeneralThread, &QThread::started, ofGeneralCtrl, &GeneralController::stop);
//	connect(ofGeneralThread, &QThread::finished, ofGeneralThread, &QThread::deleteLater);
	
//	connect(onGeneralThread, &QThread::started, onGeneralCtrl, &GeneralController::stop);
//	connect(onGeneralThread, &QThread::finished, onGeneralThread, &QThread::deleteLater);
	
//	connect(offlineThread, &QThread::started, offlineCtrl, &OfflineController::stop);
//	connect(offlineThread, &QThread::finished, offlineThread, &QThread::deleteLater);
	
//	connect(ctrlThread, &QThread::started, ofGeneralCtrl, &GeneralController::stop);
//	connect(ctrlThread, &QThread::started, onGeneralCtrl, &GeneralController::stop);
//	connect(ctrlThread, &QThread::started, offlineCtrl, &OfflineController::stop);
//	connect(ctrlThread, &QThread::started, onlineCtrl, &OnlineController::stop);
//	connect(ctrlThread, &QThread::finished, ctrlThread, &QThread::deleteLater);
	
	connect(soundThread, &QThread::finished, soundThread, &QThread::deleteLater);
	
//	connect(onSoundThread, &QThread::finished, onSoundThread, &QThread::deleteLater);
	
//	ctrlThread->start();
//	onGeneralThread->start();
//	offlineThread->start();
//	onlineThread->start();
	soundThread->start();
//	onSoundThread->start();
	
	offlineCtrl->stop();
	ofGeneralCtrl->stop();
	onGeneralCtrl->stop();
	onlineCtrl->stop();
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
