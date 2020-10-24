#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mainmenuwdt.h"
#include "singlewgt.h"

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
	void deleteController(GeneralController *controller);
	
signals:
	void moveRightSignal();
	void moveLeftSignal();
	void moveDownSignal();
	void rotateSignal();
	
private:
	void keyPressEvent(QKeyEvent *e) override;
	void keyReleaseEvent(QKeyEvent *e) override;
	
	Ui::MainWindow *ui;
	std::unique_ptr<MainMenuWdt> mainMenuWdt;
	std::unique_ptr<SingleWgt> singleWgt;
	
	std::unique_ptr<QShortcut> rightDownArr;
	std::unique_ptr<QShortcut> leftDownArr;
	std::unique_ptr<QShortcut> rightDownEng;
	std::unique_ptr<QShortcut> leftDownEng;
	std::unique_ptr<QShortcut> rightDownRus;
	std::unique_ptr<QShortcut> leftDownRus;
	
	QList<qint32> keyList;
	
	qint8 ROW_COUNT = 20;
	qint8 COLUMN_COUNT = 10;
	
	QMap<qint8, QImage *> blocks;
};

#endif // MAINWINDOW_H
