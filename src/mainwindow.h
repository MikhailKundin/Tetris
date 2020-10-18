#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mainmenuwdt.h"
#include "singlewgt.h"

namespace Ui {
class MainWindow;
}

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
	
private:
	Ui::MainWindow *ui;
	std::unique_ptr<MainMenuWdt> mainMenuWdt;
	std::unique_ptr<SingleWgt> singleWdt;
};

#endif // MAINWINDOW_H
