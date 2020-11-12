#ifndef ONLINEWGT_H
#define ONLINEWGT_H

#include "WidgetInfo.h"

class PlaygroundPnl;
class PointsPnl;
class RecordTablePnl;
class LevelFigurePnl;
class AbstractFigure;
class QLabel;
class SaveResultsWgt;
class SingleExitWgt;
class ConnectOnlineWgt;
class ButtonPanel;

namespace Ui {
class OnlineWgt;
}

class OnlineWgt : public WidgetInfo
{
	Q_OBJECT
	
public:
	explicit OnlineWgt(QWidget *parent = nullptr);
	~OnlineWgt() override;
	
public slots:
	void ofUpdateGrid(const QMap<qint16, QImage *> &grid) const;
	void ofUpdatePoints(quint32 points);
	void ofUpdateLevel(quint16 level);
	void ofUpdateFigure(AbstractFigure *&figure);
	void ofDefeat();
	
	void onUpdateGrid(const QMap<qint16, QImage *> &grid) const;
	void onUpdatePoints(quint32 points);
	void onUpdateLevel(quint16 level);
	void onUpdateFigure(AbstractFigure *&figure);
	void onDefeat();
	
	void unableToConnect();
	void connected();
	void ready();
	void disconnected();
	void clear();
	void escBtnPress();
	
private slots:
	void connectToServer(QString ip);
	void waitingClient();
	void cancelConnecting();
	
	void buttonFilter(const QString &buttonName);
	
	void openConnectWgt();
	
signals:
	void startGame();
	void readySignal();
	
	void exitSignal();
	void makeServerSignal();
	void makeClientSignal(const QString &ip);
	
	void wgtResize();
	
	void cancelWaitingSignal();
	void cancelConnectingSignal();
	void unableToConnectSignal();
	void connectedSignal();
	void closeConnectingErrPanel();
	void disconnectSignal();
	void closeReadyPanel();
	void closeEndPanel();
	
private:
	void resizeEvent(QResizeEvent *e) override;
	
	void openReadyPanel();
	void openEndPanel(bool isWinner);
	
	Ui::OnlineWgt *ui;
	
	std::unique_ptr<PlaygroundPnl> ofPg;
	std::unique_ptr<PointsPnl> ofPoints;
	std::unique_ptr<LevelFigurePnl> ofLevelFigure;
	
	std::unique_ptr<PlaygroundPnl> onPg;
	std::unique_ptr<PointsPnl> onPoints;
	std::unique_ptr<LevelFigurePnl> onLevelFigure;
	
	std::unique_ptr<QLabel> yellow;
	std::unique_ptr<QLabel> topYellow;
	
	ButtonPanel *escPanel;
	
	const quint16 BASE_YELLOW_WIDTH = 100;
	
	const QString WAITING_PANEL_NAME = "waitingPanel";
	const QString CONNECTING_PANEL_NAME = "connectingPanel";
	const QString CONNECTING_ERROR_PANEL_NAME = "connectingErrorPanel";
	const QString READY_PANEL_NAME = "readyPanel";
	const QString ESCAPE_PANEL_NAME = "escapePanel";
	const QString END_PANEL_NAME = "endPanel";
	
	bool meReady = false;
	bool opponentReady = false;
	
	bool meDefeat = false;
	bool opponentDefeat = false;
	
	bool blockEsc = true;
};

#endif // ONLINEWGT_H
