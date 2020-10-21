#include <QApplication>

#include "view/mainwindow.h"

#include <QMap>
#include <QImage>
#include "view/playground.h"
#include "view/singlewgt.h"
#include "view/pointswgt.h"
#include "view/recordtable.h"
#include "model/block.h"

#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
//	MainWindow window;
//	window.show();
	
//	QImage *green = new QImage(":Image/Blocks/OBlockOriginal.png");
//	qDebug() << green;
	
//	Block block(16, green);
//	qDebug() << block.getBlock();
	
	return app.exec();
}
