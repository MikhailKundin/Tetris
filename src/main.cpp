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
	
//	SaveResultsWgt w;
//	w.show();
	
//	QImage *green = new QImage(":Images/Blocks/OBlockOriginal.png");
	
	return app.exec();
}
