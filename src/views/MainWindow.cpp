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
	
	MainMenuWgt *mainMenuWgt = new MainMenuWgt;
	ui->scenePlace = mainMenuWgt;
	ui->scenePlace->setMinimumSize(mainMenuWgt->size());
	ui->gBox->addWidget(ui->scenePlace, 1, 1);
	
	connect(mainMenuWgt, &MainMenuWgt::exitSignal, this, &MainWindow::closeAll);
	connect(mainMenuWgt, &MainMenuWgt::singleSignal, this, &MainWindow::openSingleLayout);
	connect(mainMenuWgt, &MainMenuWgt::onlineSignal, this, &MainWindow::openOnlineLayout);
	connect(this, &MainWindow::newLayout, mainMenuWgt, &MainMenuWgt::deleteLater);
	connect(this, &MainWindow::newLayout, soundController, &SoundController::deleteLater);
	
	soundController->playMainTheme();
}

void MainWindow::openSingleLayout()
{
	emit newLayout();
	
	SingleWgt *singleWgt = new SingleWgt;
	GeneralController *generalCtrl = new GeneralController(blocks);
	OfflineController *offlineCtrl = new OfflineController;
	SoundController *soundCtrl = new SoundController(SoundController::Playground);
	
	ui->scenePlace = singleWgt;
	ui->scenePlace->setMinimumSize(singleWgt->size());
	ui->gBox->addWidget(ui->scenePlace, 1, 1);
	
	connect(singleWgt, &SingleWgt::resumeSignal, this, [=]()
	{
		offlineCtrl->resume();
		generalCtrl->start();
		soundCtrl->unmute();
	});
	connect(singleWgt, &SingleWgt::pauseSignal, this, [=]()
	{
		generalCtrl->stop();
		offlineCtrl->pause();
		soundCtrl->mute();
	});
	connect(singleWgt, &SingleWgt::restartSignal, this, [=]()
	{
		generalCtrl->clearFigure();
		generalCtrl->restart();
		offlineCtrl->restart();
		singleWgt->restart();
		soundCtrl->unmute();
	});
	connect(singleWgt, &SingleWgt::exitSignal, this, [=]()
	{
		generalCtrl->deleteLater();
		offlineCtrl->deleteLater();
		soundCtrl->deleteLater();
		openMainMenuLayout();
	});
	
	connect(generalCtrl, &GeneralController::moveDownSignal, generalCtrl, &GeneralController::newTick);
	connect(generalCtrl, &GeneralController::update, singleWgt, &SingleWgt::updateGrid);
	connect(generalCtrl, &GeneralController::newPointsSignal, this, [=](quint32 points)
	{
		singleWgt->updatePoints(points);
		soundCtrl->rowDeleted();
	});
	connect(generalCtrl, &GeneralController::newLevelSignal, this, [=](quint16 level)
	{
		offlineCtrl->newLevel(level);
		singleWgt->updateLevel(level);
	});
	connect(generalCtrl, &GeneralController::getNewFigureSignal, offlineCtrl, &OfflineController::getNewFigure);
	connect(generalCtrl, &GeneralController::newFigureSignal, singleWgt, &SingleWgt::updateFigure);
	connect(generalCtrl, &GeneralController::defeatSignal, this, [=]()
	{
		generalCtrl->stop();
		offlineCtrl->stop();
		singleWgt->defeat();
		soundCtrl->defeat();
	});
	connect(generalCtrl, &GeneralController::rightSignal, soundCtrl, &SoundController::moveRight);
	connect(generalCtrl, &GeneralController::leftSignal, soundCtrl, &SoundController::moveLeft);
	connect(generalCtrl, &GeneralController::downSignal, soundCtrl, &SoundController::moveDown);
	connect(generalCtrl, &GeneralController::rotateSignal, soundCtrl, &SoundController::rotate);
	
	connect(offlineCtrl, &OfflineController::tickSignal, this, [=]()
	{
		generalCtrl->newTick();
		//soundCtrl->moveDown();
	});
	connect(offlineCtrl, &OfflineController::newFigureSignal, generalCtrl, &GeneralController::getNextFigure);
	
	connect(this, &MainWindow::moveRightSignal, this, [=]()
	{
		generalCtrl->moveRight();
		//soundCtrl->moveRight();
	});
	connect(this, &MainWindow::moveLeftSignal, this, [=]()
	{
		generalCtrl->moveLeft();
		//soundCtrl->moveLeft();
	});
	connect(this, &MainWindow::moveDownSignal, this, [=]()
	{
		generalCtrl->newTick();
		//soundCtrl->moveDown();
	});
	connect(this, &MainWindow::rotateSignal, this, [=]()
	{
		generalCtrl->rotate();
		//soundCtrl->rotate();
	});
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
	SoundController *ofSoundCtrl = new SoundController(SoundController::Playground);
	SoundController *onSoundCtrl = new SoundController(SoundController::Playground);
	
	offlineCtrl->stop();
	ofGeneralCtrl->stop();
	onGeneralCtrl->stop();
	onlineCtrl->stop();
	ofSoundCtrl->stop();
	
	ui->scenePlace = onlineWgt;
	ui->scenePlace->setMinimumSize(onlineWgt->size());
	ui->gBox->addWidget(ui->scenePlace, 1, 1);
	
	connect(onlineWgt, &OnlineWgt::exitSignal, this, [=]()
	{
		ofGeneralCtrl->deleteLater();
		onGeneralCtrl->deleteLater();
		offlineCtrl->deleteLater();
		onlineCtrl->deleteLater();
		ofSoundCtrl->deleteLater();
		onSoundCtrl->deleteLater();
		openMainMenuLayout();
	});
	connect(onlineWgt, &OnlineWgt::makeServerSignal, onlineCtrl, &OnlineController::makeServer);
	connect(onlineWgt, &OnlineWgt::makeClientSignal, onlineCtrl, &OnlineController::makeClient);
	connect(onlineWgt, &OnlineWgt::cancelWaitingSignal, onlineCtrl, &OnlineController::deleteServer);
	connect(onlineWgt, &OnlineWgt::cancelConnectingSignal, onlineCtrl, &OnlineController::deleteSocket);
	connect(onlineWgt, &OnlineWgt::readySignal, onlineCtrl, &OnlineController::ready);
	connect(onlineWgt, &OnlineWgt::disconnectSignal, this, [=]()
	{
		onlineCtrl->disconnectSocket();
		ofGeneralCtrl->stop();
		onGeneralCtrl->stop();
		onGeneralCtrl->clearGrid();
		onGeneralCtrl->clearFigure();
		offlineCtrl->stop();
		ofSoundCtrl->stop();
		onlineWgt->restart();
	});
	connect(onlineWgt, &OnlineWgt::startGame, this, [=]()
	{
		onlineCtrl->start();
		ofGeneralCtrl->clearFigure();
		ofGeneralCtrl->restart();
		onGeneralCtrl->restart();
		offlineCtrl->restart();
		ofSoundCtrl->start();
		onlineWgt->restart();
	});
	connect(onlineWgt, &OnlineWgt::stopSignal, this, [=]()
	{
		ofGeneralCtrl->stop();
		onGeneralCtrl->stop();
		onGeneralCtrl->clearFigure();
		onGeneralCtrl->clearGrid();
		offlineCtrl->stop();
		ofSoundCtrl->stop();
	});
	connect(onlineWgt, &OnlineWgt::escPnlSignal, this, [=](bool state)
	{
		if (state)
		{
			ofSoundCtrl->mute();
			onSoundCtrl->mute();
		}
		else
		{
			ofSoundCtrl->unmute();
			onSoundCtrl->unmute();
		}
	});
	
	connect(ofGeneralCtrl, &GeneralController::moveDownSignal, this, [=]()
	{
		onlineCtrl->moveDown();
		ofGeneralCtrl->newTick();
		ofSoundCtrl->moveDown();
	});
	connect(ofGeneralCtrl, &GeneralController::update, onlineWgt, &OnlineWgt::ofUpdateGrid);
	connect(ofGeneralCtrl, &GeneralController::newPointsSignal, this, [=](quint32 points)
	{
		onlineWgt->ofUpdatePoints(points);
		ofSoundCtrl->rowDeleted();
	});
	connect(ofGeneralCtrl, &GeneralController::newLevelSignal, this, [=](quint16 level)
	{
		onlineWgt->ofUpdateLevel(level);
		offlineCtrl->newLevel(level);
	});
	connect(ofGeneralCtrl, &GeneralController::newFigureSignal, onlineWgt, &OnlineWgt::ofUpdateFigure);
	connect(ofGeneralCtrl, &GeneralController::getNewFigureSignal, offlineCtrl, &OfflineController::getNewFigure);
	connect(ofGeneralCtrl, &GeneralController::defeatSignal, this, [=]()
	{
		onlineCtrl->defeat();
		onlineCtrl->stop();
		ofGeneralCtrl->stop();
		onlineWgt->ofDefeat();
		offlineCtrl->stop();
		ofSoundCtrl->defeat();
		ofSoundCtrl->stop();
	});
	
	connect(onGeneralCtrl, &GeneralController::update, onlineWgt, &OnlineWgt::onUpdateGrid);
	connect(onGeneralCtrl, &GeneralController::newPointsSignal, this, [=](quint32 points)
	{
		onlineWgt->onUpdatePoints(points);
		onSoundCtrl->rowDeleted();
	});
	connect(onGeneralCtrl, &GeneralController::newLevelSignal, onlineWgt, &OnlineWgt::onUpdateLevel);
	connect(onGeneralCtrl, &GeneralController::newFigureSignal, onlineWgt, &OnlineWgt::onUpdateFigure);
	connect(onGeneralCtrl, &GeneralController::defeatSignal, [=]()
	{
		onGeneralCtrl->stop();
		onGeneralCtrl->clearFigure();
		onGeneralCtrl->clearGrid();
	});
	
	connect(offlineCtrl, &OfflineController::tickSignal, this, [=]()
	{
		onlineCtrl->moveDown();
		ofGeneralCtrl->newTick();
		ofSoundCtrl->moveDown();
	});
	connect(offlineCtrl, &OfflineController::newFigureSignal, this, [=](quint8 figure)
	{
		onlineCtrl->newFigure(figure);
		ofGeneralCtrl->getNextFigure(figure);
	});
	
	connect(onlineCtrl, &OnlineController::moveDownSignal, this, [=]()
	{
		onGeneralCtrl->newTick();
		onSoundCtrl->moveDown();
	});
	connect(onlineCtrl, &OnlineController::rotateSignal, this, [=]()
	{
		onGeneralCtrl->rotate();
		onSoundCtrl->rotate();
	});
	connect(onlineCtrl, &OnlineController::moveRightSignal, this, [=]()
	{
		onGeneralCtrl->moveRight();
		onSoundCtrl->moveRight();
	});
	connect(onlineCtrl, &OnlineController::moveLeftSignal, this, [=]()
	{
		onGeneralCtrl->moveLeft();
		onSoundCtrl->moveLeft();
	});
	connect(onlineCtrl, &OnlineController::newFigureSignal, onGeneralCtrl, &GeneralController::getNextFigure);
	connect(onlineCtrl, &OnlineController::cannotConnectSignal, onlineWgt, &OnlineWgt::disconnected);
	connect(onlineCtrl, &OnlineController::connectedSignal, onlineWgt, &OnlineWgt::connected);
	connect(onlineCtrl, &OnlineController::readySignal, onlineWgt, &OnlineWgt::ready);
	connect(onlineCtrl, &OnlineController::defeatSignal, this, [=]()
	{
		onlineWgt->onDefeat();
		onSoundCtrl->defeat();
	});
	connect(onlineCtrl, &OnlineController::disconnectSignal, this, [=]()
	{
		onlineWgt->disconnected();
		onlineWgt->clear();
		ofGeneralCtrl->stop();
		onGeneralCtrl->stop();
		onGeneralCtrl->clearFigure();
		onGeneralCtrl->clearGrid();
		offlineCtrl->stop();
		ofSoundCtrl->stop();
		onlineWgt->restart();
	});
	
	connect(this, &MainWindow::newLayout, onlineWgt, &OnlineWgt::deleteLater);
	connect(this, &MainWindow::pauseBtnPress, onlineWgt, &OnlineWgt::escBtnPress);
	connect(this, &MainWindow::moveRightSignal, this, [=]()
	{
		onlineCtrl->moveRight();
		ofGeneralCtrl->moveRight();
		ofSoundCtrl->moveRight();
	});
	connect(this, &MainWindow::moveLeftSignal, this, [=]()
	{
		onlineCtrl->moveLeft();
		ofGeneralCtrl->moveLeft();
		ofSoundCtrl->moveLeft();
	});
	connect(this, &MainWindow::rotateSignal, this, [=]()
	{
		onlineCtrl->rotate();
		ofGeneralCtrl->rotate();
		ofSoundCtrl->rotate();
	});
	connect(this, &MainWindow::moveDownSignal, this, [=]()
	{
		onlineCtrl->moveDown();
		ofGeneralCtrl->newTick();
		ofSoundCtrl->moveDown();
	});
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
