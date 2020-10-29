#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "MainMenuWgt.h"
#include "SingleWgt.h"

namespace Ui {
class MainWindow;
}

class GeneralController;
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
	
	void setBlockSize();
	
signals:
	void moveRightSignal();
	void moveLeftSignal();
	void moveDownSignal();
	void rotateSignal();
	
private:
	void keyPressEvent(QKeyEvent *e) override;
	void keyReleaseEvent(QKeyEvent *e) override;
	
	Ui::MainWindow *ui;
	std::unique_ptr<MainMenuWgt> mainMenuWdt;
	std::unique_ptr<SingleWgt> singleWgt;
	
	QList<qint32> keyList;
	QMap<qint8, QImage *> blocks;
	
	qint8 BLOCK_SIZE;
	const qint8 BASE_BLOCK_SIZE = 30;
	const qint16 BASE_SCREEN_HEIGHT = 768;
};

#endif // MAINWINDOW_H
