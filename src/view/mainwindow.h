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
	~MainWindow();
	
private slots:
	void openMainMenuLayout();
	void openSingleLayout();
	void openOnlineLayout();
	void closeAll();
	void deleteController(GeneralController *controller);
	
private:
	Ui::MainWindow *ui;
	std::unique_ptr<MainMenuWdt> mainMenuWdt;
	std::shared_ptr<SingleWgt> singleWgt;
	
	qint8 ROW_COUNT = 20;
	qint8 COLUMN_COUNT = 10;
};

#endif // MAINWINDOW_H
