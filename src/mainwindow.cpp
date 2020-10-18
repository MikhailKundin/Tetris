#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	
	QPalette pal(palette());
	pal.setColor(QPalette::Background, Qt::black);
	setAutoFillBackground(true);
	setPalette(pal);
	
	ui->mainMenuScene->setVisible(false);
	mainMenuWdt = std::make_unique<MainMenuWdt>(ui->mainMenuWdtPlace);
	//ui->mainMenuWdtPlace->setMinimumSize(mainMenuWdt->minimumSize());
	//ui->mainMenuWdtPlace->setMinimumSize(mainMenuWdt->geometry().height(), mainMenuWdt->geometry().width());
	ui->mainMenuWdtPlace->setMinimumSize(mainMenuWdt->size());
	connect(mainMenuWdt.get(), &MainMenuWdt::exitSignal, this, &MainWindow::closeAll);
	
	openMainMenuLayout();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::openMainMenuLayout()
{
	ui->mainWidget->setLayout(ui->mainMenuBox);
	ui->mainMenuScene->setVisible(true);
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
