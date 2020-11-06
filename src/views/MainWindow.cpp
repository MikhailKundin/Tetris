#include "MainWindow.h"
#include "ui_mainwindow.h"

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
	
	singleWgt = std::make_unique<SingleWgt>();
	mainMenuWdt = std::make_unique<MainMenuWgt>();
	
	connect(mainMenuWdt.get(), &MainMenuWgt::exitSignal, this, &MainWindow::closeAll);
	connect(mainMenuWdt.get(), &MainMenuWgt::singleSignal, this, &MainWindow::openSingleLayout);
	
	openMainMenuLayout();
}

MainWindow::~MainWindow()
{
	delete ui;
	
	foreach (QImage *block, blocks)
	{
		delete block;
	}
	
	delete buttonImg.first;
	delete buttonImg.second;
	
	delete generalCtrlOffline;
	delete offlineCtrl;
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
	
	generalCtrlOffline = new GeneralController(blocks);
	offlineCtrl = new OfflineController;
	
	singleConnect();
	
	generalCtrlOffline->restart();
	offlineCtrl->restart();
}

void MainWindow::openOnlineLayout()
{
	
}

void MainWindow::closeAll()
{
	close();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
	int key = e->key();
	
	if (key == Qt::Key_Escape)
	{
		escapePress();
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

void MainWindow::singleConnect()
{
	connect(generalCtrlOffline, &GeneralController::update, singleWgt.get(), &SingleWgt::updateGrid);
	connect(generalCtrlOffline, &GeneralController::newPointsSignal, singleWgt.get(), &SingleWgt::updatePoints);
	connect(generalCtrlOffline, &GeneralController::newLevelSignal, singleWgt.get(), &SingleWgt::updateLevel);
	connect(generalCtrlOffline, &GeneralController::newFigureSignal, singleWgt.get(), &SingleWgt::updateFigure);
	connect(generalCtrlOffline, &GeneralController::defeatSignal, this, &MainWindow::singleDefeat);
	
	connect(this, &MainWindow::moveRightSignal, generalCtrlOffline, &GeneralController::moveRight);
	connect(this, &MainWindow::moveLeftSignal, generalCtrlOffline, &GeneralController::moveLeft);
	connect(this, &MainWindow::moveDownSignal, generalCtrlOffline, &GeneralController::newTick);
	connect(this, &MainWindow::rotateSignal, generalCtrlOffline, &GeneralController::rotate);
	
	connect(this, &MainWindow::pauseSignal, this, &MainWindow::singlePause);
	connect(this, &MainWindow::resumeSignal, this, &MainWindow::singleResume);
	
	connect(offlineCtrl, &OfflineController::tickSignal, generalCtrlOffline, &GeneralController::newTick);
	connect(generalCtrlOffline, &GeneralController::newLevelSignal, offlineCtrl, &OfflineController::newLevel);
	connect(generalCtrlOffline, &GeneralController::newFigureSignal, 
			offlineCtrl, &OfflineController::getNewFigure);
	connect(offlineCtrl, &OfflineController::newFigureSignal, 
			generalCtrlOffline, &GeneralController::setThirdFigure);
	
	connect(singleWgt.get(), &SingleWgt::savedSignal, this, &MainWindow::singleSaved);
	connect(singleWgt.get(), &SingleWgt::restartSignal, this, &MainWindow::singleRestart);
	connect(singleWgt.get(), &SingleWgt::exitSignal, this, &MainWindow::singleExit);
}

void MainWindow::singleDisconnect()
{
	disconnect(generalCtrlOffline, &GeneralController::update, singleWgt.get(), &SingleWgt::updateGrid);
	disconnect(generalCtrlOffline, &GeneralController::newPointsSignal, singleWgt.get(), &SingleWgt::updatePoints);
	disconnect(generalCtrlOffline, &GeneralController::newLevelSignal, singleWgt.get(), &SingleWgt::updateLevel);
	disconnect(generalCtrlOffline, &GeneralController::newFigureSignal, singleWgt.get(), &SingleWgt::updateFigure);
	disconnect(generalCtrlOffline, &GeneralController::defeatSignal, this, &MainWindow::singleDefeat);

	disconnect(this, &MainWindow::moveRightSignal, generalCtrlOffline, &GeneralController::moveRight);
	disconnect(this, &MainWindow::moveLeftSignal, generalCtrlOffline, &GeneralController::moveLeft);
	disconnect(this, &MainWindow::moveDownSignal, generalCtrlOffline, &GeneralController::newTick);
	disconnect(this, &MainWindow::rotateSignal, generalCtrlOffline, &GeneralController::rotate);

	disconnect(this, &MainWindow::pauseSignal, this, &MainWindow::singlePause);
	disconnect(this, &MainWindow::resumeSignal, this, &MainWindow::singleResume);

	disconnect(offlineCtrl, &OfflineController::tickSignal, generalCtrlOffline, &GeneralController::newTick);
	disconnect(generalCtrlOffline, &GeneralController::newLevelSignal, offlineCtrl, &OfflineController::newLevel);
	disconnect(generalCtrlOffline, &GeneralController::newFigureSignal, 
			   offlineCtrl, &OfflineController::getNewFigure);
	disconnect(offlineCtrl, &OfflineController::newFigureSignal, 
			   generalCtrlOffline, &GeneralController::setThirdFigure);

	disconnect(singleWgt.get(), &SingleWgt::savedSignal, this, &MainWindow::singleSaved);
	disconnect(singleWgt.get(), &SingleWgt::restartSignal, this, &MainWindow::singleRestart);
	disconnect(singleWgt.get(), &SingleWgt::exitSignal, this, &MainWindow::singleExit);
}

void MainWindow::escapePress()
{
	if (finalEscape)
	{
		return;
	}
	
	escape = !escape;
	if (escape)
	{
		emit pauseSignal();
	}
	else
	{
		emit resumeSignal();
	}
}

void MainWindow::singleDefeat()
{
	generalCtrlOffline->stop();
	offlineCtrl->stop();
	singleWgt->saveResult();
}

void MainWindow::singlePause()
{
	generalCtrlOffline->stop();
	offlineCtrl->pause();
	singleWgt->openPausePanel();
}

void MainWindow::singleResume()
{
	generalCtrlOffline->start();
	offlineCtrl->resume();
	singleWgt->closePausePanel();
}

void MainWindow::singleSaved()
{
	escapePress();
	finalEscape = true;
	singleWgt->openPausePanel();
}

void MainWindow::singleRestart()
{
	generalCtrlOffline->restart();
	offlineCtrl->restart();
	singleWgt->restart();
	escape = false;
	finalEscape = false;
}

void MainWindow::singleExit()
{
	singleDisconnect();
	generalCtrlOffline->deleteController();
	offlineCtrl->deleteController();
	openMainMenuLayout();
	escape = false;
	finalEscape = false;
}
