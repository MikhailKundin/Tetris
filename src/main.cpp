#include <QApplication>

#include "view/MainWindow.h"

#include <QMap>
#include <QImage>
#include "views/PlaygroundPnl.h"
#include "views/SingleWgt.h"
#include "views/PointsPnl.h"
#include "views/RecordTablePnl.h"
#include "views/NextFigurePnl.h"
#include "views/LevelPnl.h"
#include "views/LevelFigurePnl.h"
#include "views/SaveResultsWgt.h"
#include "Block.h"
#include <QTime>
#include <QRandomGenerator>
#include "controllers/GeneralController.h"
#include "TetrisInfo.h"
#include "views/SingleExitWgt.h"
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
