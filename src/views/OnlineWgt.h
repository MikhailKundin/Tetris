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
	
private slots:
	void connectToServer(QString ip);
	void waitingClient();
	void cancelConnecting();
	
	void buttonFilter(const QString &buttonName);
	void openConnectWgt();
	
signals:
	void exitSignal();
	void makeServerSignal();
	void makeClientSignal(const QString &ip);
	
	void wgtResize();
	
	void cancelWaitingSignal();
	void cancelConnectingSignal();
	void unableToConnectSignal();
	void closeConnectingErrPanel();
	void connectedSignal();
	void startGame();
	
private:
	void resizeEvent(QResizeEvent *e) override;
	
	Ui::OnlineWgt *ui;
	
	std::unique_ptr<PlaygroundPnl> ofPg;
	std::unique_ptr<PointsPnl> ofPoints;
	std::unique_ptr<LevelFigurePnl> ofLevelFigure;
	
	std::unique_ptr<PlaygroundPnl> onPg;
	std::unique_ptr<PointsPnl> onPoints;
	std::unique_ptr<LevelFigurePnl> onLevelFigure;
	
	std::unique_ptr<QLabel> yellow;
	std::unique_ptr<QLabel> topYellow;
	
	ConnectOnlineWgt *connectOnlineWgt = nullptr;
	
	const quint16 BASE_YELLOW_WIDTH = 100;
	
	const QString WAITING_PANEL_NAME = "waitingPanel";
	const QString CONNECTING_PANEL_NAME = "connectingPanel";
	const QString CONNECTING_ERROR_PANEL_NAME = "connectingErrorPanel";
};

#endif // ONLINEWGT_H
