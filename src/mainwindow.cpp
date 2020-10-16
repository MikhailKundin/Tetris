#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mainmenuwdt.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->widget1 = new MainMenuWdt(this);
	ui->gBox->addWidget(ui->widget1, 1, 1);
}

MainWindow::~MainWindow()
{
	delete ui;
}
