#include "OnlineWgt.h"
#include "ui_OnlineWgt.h"

#include <QLabel>

#include "../TetrisInfo.h"
#include "PlaygroundPnl.h"
#include "PointsPnl.h"
#include "LevelFigurePnl.h"
#include "SaveResultsWgt.h"
#include "ConnectOnlineWgt.h"
#include "ButtonPanel.h"

#include <QDebug>

OnlineWgt::OnlineWgt(QWidget *parent) :
	WidgetInfo(parent), ui(new Ui::OnlineWgt)
{
	ui->setupUi(this);
	setLayout(ui->gBox);
	
	ofPg = std::make_unique<PlaygroundPnl>(BLOCK_SIZE, MULT, ui->ofPgPnl);
	ui->ofPgPnl->setFixedSize(ofPg->size());
	onPg = std::make_unique<PlaygroundPnl>(BLOCK_SIZE, MULT, ui->onPgPnl);
	ui->onPgPnl->setFixedSize(onPg->size());
	
	onPoints = std::make_unique<PointsPnl>(onPg->width(), MULT, ui->onPointsPnl);
	ui->onPointsPnl->setFixedSize(onPoints->size());
	ofPoints = std::make_unique<PointsPnl>(ofPg->width(), MULT, ui->ofPointsPnl);
	ui->ofPointsPnl->setFixedSize(ofPoints->size());
	
	ofLevelFigure = std::make_unique<LevelFigurePnl>(ofPoints->height(), BLOCK_SIZE, MULT, ui->ofLevelFigurePnl);
	ofLevelFigure->setFixedSize(ofLevelFigure->width(), ui->ofPgPnl->height() + ui->ofPointsPnl->height());
	ui->ofLevelFigurePnl->setFixedSize(ofLevelFigure->size());
	ui->gBox->addWidget(ui->ofLevelFigurePnl, 1, 1, 2, 1);
	onLevelFigure = std::make_unique<LevelFigurePnl>(onPoints->height(), BLOCK_SIZE, MULT, ui->onLevelFigurePnl);
	onLevelFigure->setFixedSize(onLevelFigure->width(), ui->onPgPnl->height() + ui->onPointsPnl->height());
	ui->onLevelFigurePnl->setFixedSize(onLevelFigure->size());
	ui->gBox->addWidget(ui->onLevelFigurePnl, 1, 5, 2, 1);
	
	QPixmap yellowImg(":Images/Backgrounds/YellowBackground.png");
	ui->topYellowLbl->setFixedSize(static_cast<qint32>(BASE_YELLOW_WIDTH*MULT), ui->ofPointsPnl->height());
	ui->topYellowLbl->setPixmap(yellowImg.scaled(ui->topYellowLbl->size()));
	ui->yellowLbl->setFixedSize(static_cast<qint32>(BASE_YELLOW_WIDTH*MULT), ui->ofPgPnl->height());
	ui->yellowLbl->setPixmap(yellowImg.scaled(ui->yellowLbl->size()));
	
	setMinimumHeight(ofPg->height() + ofPoints->height());
	setMinimumWidth(ui->ofLevelFigurePnl->width() + ofPg->width() + ui->yellowLbl->width() + 
					ui->onLevelFigurePnl->width() + onPg->width());
	
	onPg->setState(PlaygroundPnl::NotReady);
	ofPg->setState(PlaygroundPnl::NotReady);
	openConnectWgt();
}

OnlineWgt::~OnlineWgt()
{
	delete ui;
}

void OnlineWgt::ofUpdateGrid(const QMap<qint16, QImage *> &grid) const
{
	ofPg->update(grid);
}

void OnlineWgt::ofUpdatePoints(quint32 points)
{
	ofPoints->update(points);
}

void OnlineWgt::ofUpdateLevel(quint16 level)
{
	ofLevelFigure->setLevel(level);
}

void OnlineWgt::ofUpdateFigure(AbstractFigure *&figure)
{
	ofLevelFigure->setFigure(figure);
}

void OnlineWgt::ofDefeat()
{
	ofPg->setState(PlaygroundPnl::Defeat);
}

void OnlineWgt::onUpdateGrid(const QMap<qint16, QImage *> &grid) const
{
	onPg->update(grid);
}

void OnlineWgt::onUpdatePoints(quint32 points)
{
	onPoints->update(points);
}

void OnlineWgt::onUpdateLevel(quint16 level)
{
	onLevelFigure->setLevel(level);
}

void OnlineWgt::onUpdateFigure(AbstractFigure *&figure)
{
	onLevelFigure->setFigure(figure);
}

void OnlineWgt::onDefeat()
{
	onPg->setState(PlaygroundPnl::Defeat);
}

void OnlineWgt::unableToConnect()
{
	emit unableToConnectSignal();
	
	ButtonPanel *connectingErr = new ButtonPanel("Подключение не удалось!", {"Ок"}, getPanelPixmaps(), MULT, this);
	connectingErr->setObjectName(CONNECTING_ERROR_PANEL_NAME);
	connectingErr->resize(size());
	connectingErr->setVisible(true);
	
	connect(this, &OnlineWgt::closeConnectingErrPanel, connectingErr, &ButtonPanel::deleteLater);
	connect(connectingErr, &ButtonPanel::clicked, this, &OnlineWgt::buttonFilter);
	connect(this, &OnlineWgt::wgtResize, [=](){connectingErr->resize(size());});
	connect(this, &OnlineWgt::closeConnectingErrPanel, this, &OnlineWgt::openConnectWgt);
}

void OnlineWgt::connectToServer(QString ip)
{
	connectOnlineWgt->setVisible(false);
	
	ButtonPanel *connectingPnl = new ButtonPanel("Присоединение...", {"Отмена"}, getPanelPixmaps(), MULT, this);
	connectingPnl->setObjectName(CONNECTING_PANEL_NAME);
	connectingPnl->resize(size());
	connectingPnl->setVisible(true);
	emit makeClientSignal(ip);
	
	connect(this, &OnlineWgt::unableToConnectSignal, connectingPnl, &ButtonPanel::deleteLater);
	connect(this, &OnlineWgt::connectedSignal, connectingPnl, &ButtonPanel::deleteLater);
	connect(this, &OnlineWgt::cancelConnectingSignal, connectingPnl, &ButtonPanel::deleteLater);
	connect(connectingPnl, &ButtonPanel::clicked, this, &OnlineWgt::buttonFilter);
	connect(this, &OnlineWgt::wgtResize, [=](){connectingPnl->resize(size());});
	connect(this, &OnlineWgt::cancelConnectingSignal, this, &OnlineWgt::openConnectWgt);
}

void OnlineWgt::waitingClient()
{
	connectOnlineWgt->setVisible(false);
	
	ButtonPanel *waitingPnl = new ButtonPanel("Ожидание соперника...", {"Отмена"}, getPanelPixmaps(), MULT, this);
	waitingPnl->setObjectName(WAITING_PANEL_NAME);
	waitingPnl->resize(size());
	waitingPnl->setVisible(true);
	emit makeServerSignal();
	
	connect(this, &OnlineWgt::connectedSignal, waitingPnl, &ButtonPanel::deleteLater);
	connect(waitingPnl, &ButtonPanel::clicked, this, &OnlineWgt::buttonFilter);
	connect(this, &OnlineWgt::wgtResize, [=](){waitingPnl->resize(size());});
	connect(this, &OnlineWgt::cancelWaitingSignal, waitingPnl, &ButtonPanel::deleteLater);
	connect(this, &OnlineWgt::cancelWaitingSignal, this, &OnlineWgt::openConnectWgt);
}

void OnlineWgt::cancelConnecting()
{
	connectOnlineWgt->setVisible(false);
	connectOnlineWgt->deleteLater();
	emit exitSignal();
}

void OnlineWgt::buttonFilter(const QString &buttonName)
{
	if (sender()->objectName() == WAITING_PANEL_NAME)
	{
		if (buttonName == "Отмена")
		{
			emit cancelWaitingSignal();
		}
	}
	else if (sender()->objectName() == CONNECTING_PANEL_NAME)
	{
		if (buttonName == "Отмена")
		{
			emit cancelConnectingSignal();
		}
	}
	else if (sender()->objectName() == CONNECTING_ERROR_PANEL_NAME)
	{
		if (buttonName == "Ок")
		{
			emit closeConnectingErrPanel();
		}
	}
}

void OnlineWgt::openConnectWgt()
{
	if (connectOnlineWgt == nullptr)
	{
		connectOnlineWgt = new ConnectOnlineWgt(getPanelPixmaps(), MULT, this);
		connectOnlineWgt->resize(size());
		
		//connect(this, &OnlineWgt::connectedSignal, connectOnlineWgt, &ConnectOnlineWgt::deleteLater);
		connect(connectOnlineWgt, &ConnectOnlineWgt::createSignal, this, &OnlineWgt::waitingClient);
		connect(connectOnlineWgt, &ConnectOnlineWgt::connectSignal, this, &OnlineWgt::connectToServer);
		connect(connectOnlineWgt, &ConnectOnlineWgt::exitSignal, this, &OnlineWgt::cancelConnecting);
		connect(this, &OnlineWgt::wgtResize, [=](){connectOnlineWgt->resize(size());});
	}
	connectOnlineWgt->setVisible(true);
}

void OnlineWgt::connected()
{
	connectOnlineWgt->deleteLater();
	
	emit connectedSignal();
	ofPg->setState(PlaygroundPnl::Default);
	onPg->setState(PlaygroundPnl::Default);
	emit startGame();
}

void OnlineWgt::resizeEvent(QResizeEvent *e)
{
	Q_UNUSED(e)
	
	emit wgtResize();
}
