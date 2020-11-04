#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

class SingleWgt;
class MainMenuWgt;
class SaveResultsWgt;
class QImage;
class GeneralController;
class OnlineController;
class OfflineController;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow() override;
	
private slots:
	void openMainMenuLayout();
	void openSingleLayout();
	void openOnlineLayout();
	void closeAll();
	
	void escapePress();
	
	void singleDefeat();
	void singlePause();
	void singleResume();
	void singleSaved();
	void singleRestart();
	void singleExit();
	
signals:
	void moveRightSignal();
	void moveLeftSignal();
	void moveDownSignal();
	void rotateSignal();
	
	void resumeSignal();
	void pauseSignal();
	
private:
	void keyPressEvent(QKeyEvent *e) override;
	void keyReleaseEvent(QKeyEvent *e) override;
	
	void singleConnect();
	void singleDisconnect();
	
	Ui::MainWindow *ui;
	std::unique_ptr<MainMenuWgt> mainMenuWdt;
	std::unique_ptr<SingleWgt> singleWgt;
	
	GeneralController *generalCtrlOffline;
	OfflineController *offlineCtrl;
	
	QList<qint32> keyList;
	QMap<qint8, QImage *> blocks;
	QPair <QPixmap *, QPixmap *> buttonImg;
	
	bool escape = false;
	bool finalEscape = false;
};

#endif // MAINWINDOW_H
