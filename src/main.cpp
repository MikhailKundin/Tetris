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

#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
//	MainWindow window;
//	window.show();
	
//	QImage *green = new QImage(":Images/Blocks/OBlockOriginal.png");
//	qDebug() << green;
	
//	Block block(16, green);
//	qDebug() << block.getBlock();
//	QRandomGenerator random(QTime::currentTime().msecsSinceStartOfDay());
//	qDebug() <<  random.generate() % 7;
	
//	QMap<qint16, QImage *> map;
//	map.insert(16, green);
//	if (!map.value(15))
//	{
//		qDebug() << 0;
//	}
//	else
//	{
//		qDebug() << 1;
//	}
	
	return app.exec();
}
