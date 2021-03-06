#include "OnlineWgt.h"
#include "ui_OnlineWgt.h"

#include <QLabel>

#include "../TetrisInfo.h"
#include "PlaygroundPnl.h"
#include "PointsPnl.h"
#include "LevelFigurePnl.h"
#include "ConnectOnlineWgt.h"
#include "ButtonPanel.h"

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
	
	escPanel = new ButtonPanel("Меню", {"Продолжить", "Выход"}, getPanelMedia(), MULT, this);
	escPanel->setObjectName(ESCAPE_PANEL_NAME);
	escPanel->setVisible(false);
	connect(escPanel, &ButtonPanel::clicked, this, &OnlineWgt::buttonFilter);
	connect(this, &OnlineWgt::wgtResize, escPanel, [=](){escPanel->resize(size());});
	
	onPg->setState(PlaygroundPnl::NotReady);
	ofPg->setState(PlaygroundPnl::NotReady);
	openConnectWgt();
}

OnlineWgt::~OnlineWgt()
{
	delete escPanel;
	delete ui;
}

void OnlineWgt::restart()
{
	ofPoints->update(0);
	onPoints->update(0);
	ofLevelFigure->setLevel(1);
	onLevelFigure->setLevel(1);
}

void OnlineWgt::ofUpdateGrid(const QMap<qint16, QImage *> &grid) const
{
	ofPg->update(grid);
}

void OnlineWgt::ofUpdatePoints(quint32 points)
{
	ofPoints->update(points);
	if (opponentDefeat && ofPoints->getPoints() > onPoints->getPoints())
	{
		openEndPanel(EndState::Victory);
	}
}

void OnlineWgt::ofUpdateLevel(quint16 level)
{
	ofLevelFigure->setLevel(level);
}

void OnlineWgt::ofUpdateFigure(AbstractFigure *figure)
{
	ofLevelFigure->setFigure(figure);
}

void OnlineWgt::ofDefeat()
{
	ofPg->setState(PlaygroundPnl::Defeat);
	meDefeat = true;
	if (opponentDefeat && ofPoints->getPoints() == onPoints->getPoints())
	{
		openEndPanel(EndState::Draw);
	}
	else if (ofPoints->getPoints() < onPoints->getPoints())
	{
		openEndPanel(EndState::Defeat);
	}
}

void OnlineWgt::onUpdateGrid(const QMap<qint16, QImage *> &grid) const
{
	onPg->update(grid);
}

void OnlineWgt::onUpdatePoints(quint32 points)
{
	onPoints->update(points);
	if (meDefeat && onPoints->getPoints() > ofPoints->getPoints())
	{
		openEndPanel(EndState::Defeat);
	}
}

void OnlineWgt::onUpdateLevel(quint16 level)
{
	onLevelFigure->setLevel(level);
}

void OnlineWgt::onUpdateFigure(AbstractFigure *figure)
{
	onLevelFigure->setFigure(figure);
}

void OnlineWgt::onDefeat()
{
	onPg->setState(PlaygroundPnl::Defeat);
	opponentDefeat = true;
	if (meDefeat && ofPoints->getPoints() == onPoints->getPoints())
	{
		openEndPanel(EndState::Draw);
	}
	else if (ofPoints->getPoints() > onPoints->getPoints())
	{
		openEndPanel(EndState::Victory);
	}
}

void OnlineWgt::unableToConnect(const QString &message)
{
	if (findChild<ButtonPanel *>(CONNECTING_ERROR_PANEL_NAME) != nullptr)
	{
		return;
	}
	
	emit unableToConnectSignal();
	emit closeEndPanel();
	
	blockEsc = true;
	escPanel->setVisible(false);
	
	ButtonPanel *connectingErr = new ButtonPanel(message, {"Ок"}, getPanelMedia(), MULT, this);
	connectingErr->setObjectName(CONNECTING_ERROR_PANEL_NAME);
	connectingErr->resize(size());
	connectingErr->setVisible(true);
	
	connect(this, &OnlineWgt::closeConnectingErrPanel, connectingErr, &ButtonPanel::deleteLater);
	connect(connectingErr, &ButtonPanel::clicked, this, &OnlineWgt::buttonFilter);
	connect(this, &OnlineWgt::wgtResize, connectingErr, [=](){connectingErr->resize(size());});
	disconnect(this, &OnlineWgt::closeConnectingErrPanel, this, &OnlineWgt::openConnectWgt);
	connect(this, &OnlineWgt::closeConnectingErrPanel, this, &OnlineWgt::openConnectWgt);
}

void OnlineWgt::connectToServer(const QString &ip)
{
	blockEsc = true;
	escPanel->setVisible(false);
	
	connectingToServer = true;
	ButtonPanel *connectingPnl = new ButtonPanel("Присоединение...", {"Отмена"}, getPanelMedia(), MULT, this);
	connectingPnl->setObjectName(CONNECTING_PANEL_NAME);
	connectingPnl->resize(size());
	connectingPnl->setVisible(true);
	emit makeClientSignal(ip);
	
	connect(this, &OnlineWgt::unableToConnectSignal, connectingPnl, [=](){
		connectingPnl->deleteLater();
		connectingToServer = false;
	});
	connect(this, &OnlineWgt::connectedSignal, connectingPnl, [=](){
		connectingPnl->deleteLater();
		connectingToServer = false;
	});
	connect(this, &OnlineWgt::cancelConnectingSignal, connectingPnl, [=](){
		connectingPnl->deleteLater();
		connectingToServer = false;
	});
	connect(connectingPnl, &ButtonPanel::clicked, this, &OnlineWgt::buttonFilter);
	connect(this, &OnlineWgt::wgtResize, connectingPnl, [=](){connectingPnl->resize(size());});
	disconnect(this, &OnlineWgt::cancelConnectingSignal, this, &OnlineWgt::openConnectWgt);
	connect(this, &OnlineWgt::cancelConnectingSignal, this, &OnlineWgt::openConnectWgt);
}

void OnlineWgt::waitingClient()
{
	blockEsc = true;
	escPanel->setVisible(false);
	
	ButtonPanel *waitingPnl = new ButtonPanel("Ожидание соперника...", {"Отмена"}, getPanelMedia(), MULT, this);
	waitingPnl->setObjectName(WAITING_PANEL_NAME);
	waitingPnl->resize(size());
	waitingPnl->setVisible(true);
	emit makeServerSignal();
	
	connect(this, &OnlineWgt::connectedSignal, waitingPnl, &ButtonPanel::deleteLater);
	connect(waitingPnl, &ButtonPanel::clicked, this, &OnlineWgt::buttonFilter);
	connect(this, &OnlineWgt::wgtResize, waitingPnl, [=](){waitingPnl->resize(size());});
	connect(this, &OnlineWgt::cancelWaitingSignal, waitingPnl, &ButtonPanel::deleteLater);
	disconnect(this, &OnlineWgt::cancelWaitingSignal, this, &OnlineWgt::openConnectWgt);
	connect(this, &OnlineWgt::cancelWaitingSignal, this, &OnlineWgt::openConnectWgt);
}

void OnlineWgt::cancelConnecting()
{
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
	else if (sender()->objectName() == READY_PANEL_NAME)
	{
		if (buttonName == "Готов!")
		{
			meReady = true;
			ofPg->setState(PlaygroundPnl::Ready);
			emit readySignal();
			emit closeReadyPanel();
			blockEsc = false;
			if (meReady && opponentReady)
			{
				ofPg->setState(PlaygroundPnl::Default);
				onPg->setState(PlaygroundPnl::Default);
				meReady = false;
				opponentReady = false;
				emit startGame();
			}
		}
		else if (buttonName == "Отмена")
		{
			emit disconnectSignal();
			emit closeReadyPanel();
			openConnectWgt();
		}
	}
	else if (sender()->objectName() == ESCAPE_PANEL_NAME)
	{
		if (buttonName == "Продолжить")
		{
			escPanel->setVisible(false);
		}
		else if (buttonName == "Выход")
		{
			escPanel->setVisible(false);
			emit disconnectSignal();
			openConnectWgt();
		}
	}
	else if (sender()->objectName() == END_PANEL_NAME)
	{
		if (buttonName == "Повтор")
		{
			emit closeEndPanel();
			openReadyPanel();
		}
		else if (buttonName == "Выход")
		{
			emit closeEndPanel();
			emit disconnectSignal();
			openConnectWgt();
		}
	}
}

void OnlineWgt::openConnectWgt()
{
	blockEsc = true;
	escPanel->setVisible(false);
	
	clear();
	
	ConnectOnlineWgt *connectOnlineWgt = new ConnectOnlineWgt(getPanelMedia(), MULT, this);
	connectOnlineWgt->resize(size());
	connectOnlineWgt->setVisible(true);
	
	connect(connectOnlineWgt, &ConnectOnlineWgt::exitSignal, this, [=]()
	{
		cancelConnecting();
		connectOnlineWgt->deleteLater();
	});
	connect(connectOnlineWgt, &ConnectOnlineWgt::connectSignal, this, [=](QString ip)
	{
		connectToServer(ip);
		connectOnlineWgt->deleteLater();
	});
	connect(connectOnlineWgt, &ConnectOnlineWgt::createSignal, this, [=]()
	{
		waitingClient();
		connectOnlineWgt->deleteLater();
	});
	connect(this, &OnlineWgt::wgtResize, connectOnlineWgt, [=](){connectOnlineWgt->resize(size());});
}

void OnlineWgt::connected()
{
	emit connectedSignal();
	ofPg->setState(PlaygroundPnl::NotReady);
	onPg->setState(PlaygroundPnl::NotReady);
	openReadyPanel();
}

void OnlineWgt::ready()
{
	opponentReady = true;
	if (!blockChangePgState)
	{
		onPg->setState(PlaygroundPnl::Ready);
	}
	if (meReady && opponentReady)
	{
		ofPg->setState(PlaygroundPnl::Default);
		onPg->setState(PlaygroundPnl::Default);
		blockEsc = false;
		meReady = false;
		opponentReady = false;
		emit startGame();
	}
}

void OnlineWgt::disconnected()
{
	if (connectingToServer)
	{
		unableToConnect("Нет соединения с сервером");
	}
	else
	{
		unableToConnect();
	}
}

void OnlineWgt::clear()
{
	meDefeat = false;
	meReady = false;
	ofPg->update({});
	ofPoints->update(0);
	ofLevelFigure->setLevel(1);
	ofLevelFigure->clearFigure();
	ofPg->setState(PlaygroundPnl::NotReady);
	
	opponentDefeat = false;
	opponentReady = false;
	onPg->update({});
	onPoints->update(0);
	onLevelFigure->setLevel(0);
	onLevelFigure->clearFigure();
	if (!opponentReady)
	{
		onPg->setState(PlaygroundPnl::NotReady);
	}
	else
	{
		onPg->setState(PlaygroundPnl::Ready);
	}
}

void OnlineWgt::escBtnPress()
{
	if (blockEsc)
	{
		return;
	}
	
	escPanel->setVisible(!escPanel->isVisible());
	emit escPnlSignal(escPanel->isVisible());
}

void OnlineWgt::resizeEvent(QResizeEvent *e)
{
	Q_UNUSED(e)
	
	emit wgtResize();
}

void OnlineWgt::openReadyPanel()
{
	blockEsc = true;
	escPanel->setVisible(false);
	bool opponentCheck = opponentReady;
	clear();
	if (opponentCheck)
	{
		ready();
	}
	
	ButtonPanel *readyPanel = new ButtonPanel("Готов?", {"Готов!", "Отмена"}, getPanelMedia(), MULT, this);
	readyPanel->setObjectName(READY_PANEL_NAME);
	readyPanel->resize(size());
	readyPanel->setVisible(true);
	
	connect(this, &OnlineWgt::closeReadyPanel, readyPanel, &ButtonPanel::deleteLater);
	connect(this, &OnlineWgt::unableToConnectSignal, readyPanel, &ButtonPanel::deleteLater);
	connect(readyPanel, &ButtonPanel::clicked, this, &OnlineWgt::buttonFilter);
	connect(this, &OnlineWgt::wgtResize, readyPanel, [=](){readyPanel->resize(size());});
}

void OnlineWgt::openEndPanel(EndState state)
{
	blockEsc = true;
	escPanel->setVisible(false);
	
	blockChangePgState = true;
	
	ButtonPanel *endPanel;
	switch (state)
	{
	case Victory:
		endPanel = new ButtonPanel("Вы победили!", {"Повтор", "Выход"}, getPanelMedia(), MULT, this);
		break;
	case Defeat:
		endPanel = new ButtonPanel("Вы проиграли!", {"Повтор", "Выход"}, getPanelMedia(), MULT, this);
		break;
	case Draw:
		endPanel = new ButtonPanel("Ничья!", {"Повтор", "Выход"}, getPanelMedia(), MULT, this);
		break;
	}

	endPanel->setObjectName(END_PANEL_NAME);
	endPanel->resize(size());
	endPanel->setVisible(true);
	
	emit stopSignal();
	
	connect(endPanel, &ButtonPanel::clicked, this, &OnlineWgt::buttonFilter);
	connect(this, &OnlineWgt::wgtResize, endPanel, [=](){endPanel->resize(size());});
	connect(this, &OnlineWgt::closeEndPanel, endPanel, &ButtonPanel::deleteLater);
	connect(this, &OnlineWgt::closeEndPanel, endPanel, [=]()
	{
		endPanel->deleteLater();
		blockChangePgState = false;
	});
}
