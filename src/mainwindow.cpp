#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	
	ui->mainMenuLayout->setVisible(false);
	mainMenuWdt = std::make_unique<MainMenuWdt>(ui->mainMenuWdtPlace);
	ui->mainMenuWdtPlace->setMinimumSize(mainMenuWdt->minimumSize());
	connect(mainMenuWdt.get(), &MainMenuWdt::exitSignal, this, &MainWindow::closeAll);
	
	openMainMenuLayout();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::openMainMenuLayout()
{
	ui->mainMenuLayout->setVisible(true);
}

void MainWindow::openSingleLayout()
{
	
}

void MainWindow::openOnlineLayout()
{
	
}

void MainWindow::closeAll()
{
	close();
}
