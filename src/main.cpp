#include <QApplication>

#include "view/MainWindow.h"

#include <QMap>
#include <QImage>
#include "view/PlaygroundPnl.h"
#include "view/SingleWgt.h"
#include "view/PointsPnl.h"
#include "view/RecordTablePnl.h"
#include "view/NextFigurePnl.h"
#include "view/LevelPnl.h"
#include "view/LevelFigurePnl.h"
#include "view/SaveResultsWgt.h"
#include "model/Block.h"
#include <QTime>
#include <QRandomGenerator>
#include "controller/GeneralController.h"
#include "TetrisInfo.h"
#include "view/SingleExitWgt.h"
#include <QObject>
#include <QDialog>
#include <QLabel>

#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	MainWindow window;
	window.move(750, 0);
	window.showMaximized();
	
//	QPixmap *imgEnter = new QPixmap(":/Images/Buttons/HoverEnter.png");
//	QPixmap *imgLeave = new QPixmap(":/Images/Buttons/HoverLeave.png");
//	QPair <QPixmap *, QPixmap *> p = {imgEnter, imgLeave};
//	SingleExitWgt s(p, 2.66);
//	s.show();
	
//	SaveResultsWgt w;
//	w.show();
	
//	QImage *green = new QImage(":Images/Blocks/OBlockOriginal.png");
	
	return app.exec();
}
