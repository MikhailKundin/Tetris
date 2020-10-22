#include <QApplication>

#include "view/mainwindow.h"

#include <QMap>
#include <QImage>
#include "view/playground.h"
#include "view/singlewgt.h"
#include "view/pointswgt.h"
#include "view/recordtable.h"
#include "model/block.h"
#include <QTime>
#include <QRandomGenerator>
#include "controller/generalcontroller.h"
#include <QObject>

#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	MainWindow window;
	window.move(800, 0);
	window.show();
	
//	QImage *green = new QImage(":Images/Blocks/OBlockOriginal.png");
//	qDebug() << green;
	
	return app.exec();
}
