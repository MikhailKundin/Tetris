#include <QApplication>

#include "view/MainWindow.h"

#include <QMap>
#include <QImage>
#include "view/PlaygroundPnl.h"
#include "view/SingleWgt.h"
#include "view/PointsPnl.h"
#include "view/RecordTablePnl.h"
#include "model/Block.h"
#include <QTime>
#include <QRandomGenerator>
#include "controller/GeneralController.h"
#include <QObject>

#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	MainWindow window;
	window.move(800, 0);
	window.show();
	
//	QImage *green = new QImage(":Images/Blocks/OBlockOriginal.png");
	
	return app.exec();
}
