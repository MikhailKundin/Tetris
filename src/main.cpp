#include <QApplication>

#include "mainwindow.h"

#include <QMap>
#include <QImage>
#include "playground.h"
#include "singlewgt.h"
#include "pointswgt.h"
#include "recordtable.h"

#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	MainWindow window;
	window.show();
	
//	QImage* red = new QImage("..//..//etc//Images//Blocks//Original//LBlockOriginal.png");
//	QImage* green = new QImage("..//..//etc//Images//Blocks//Original//OBlockOriginal.png");
//	QImage* blue = new QImage("..//..//etc//Images//Blocks//Original//IBlockOriginal.png");
//	QMap<qint16, QImage*> map;
//	map.insert(0, blue);
//	map.insert(9, blue);
//	map.insert(190, blue);
//	map.insert(199, blue);
//	for (qint16 i = 1; i < 175; i++)
//	{
//		if (i == 9 || i == 190)
//		{
//			continue;
//		}
		
//		if (i % 2 == 0)
//		{
//			map.insert(i, green);
//		}
//		else
//		{
//			map.insert(i, red);
//		}
//	}
//	map.erase(map.find(100));
//	map.erase(map.find(101));
	
//	Playground pg;
//	pg.resize(pg.minimumSize());
//	pg.show();
//	pg.update(map);
	
//	SingleWgt w;
//	w.show();
//	qDebug() << w.minimumSize();
	
	return app.exec();
}
