#include <QApplication>

#include "views/MainWindow.h"

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
#include <QObject>
#include <QDialog>
#include <QLabel>
#include "controllers/OnlineController.h"
#include "controllers/OfflineController.h"
#include "views/ConnectOnlineWgt.h"
#include "views/OnlineWgt.h"
#include "views/ButtonPanel.h"
#include "views/PushLabel.h"
#include "views/MainMenuWgt.h"

#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	MainWindow window;
	window.move(750, 0);
	//window.showMaximized();
	window.showFullScreen();
	
//	SingleWgt *w = new SingleWgt;
//	w->show();
	
//	std::unique_ptr<LevelFigurePnl> w;
//	w = std::make_unique<LevelFigurePnl>(50, 30, 1);
//	w->show();
	
//	LevelFigurePnl *w = new LevelFigurePnl(50, 30, 1);
//	w->show();
	
//	std::unique_ptr<NextFigurePnl> w;
//	w = std::make_unique<NextFigurePnl>(30, 1);
//	w->show();
	
//	NextFigurePnl *w = new NextFigurePnl(30, 1);
//	w->show();
	
//	WidgetInfo *w = new WidgetInfo;
//	w->show();
//	auto p = w.getPanelPixmaps();
//	ConnectOnlineWgt *wi = new ConnectOnlineWgt(p, 1);
//	wi->show();
//	wi->deleteLater();
	
//	QMap<qint8, QImage *> map;
//	map.insert(0, nullptr);
//	GeneralController *c = new GeneralController(map);
//	OnlineController *c = new OnlineController;
//	c->deleteLater();
	
//	OnlineController s;
//	s.makeServer();
//	OnlineController c;
//	c.makeClient("127.0.0.1");
	
//	QPixmap *imgEnter = new QPixmap(":/Images/Buttons/HoverEnter.png");
//	QPixmap *imgLeave = new QPixmap(":/Images/Buttons/HoverLeave.png");
//	QPair <QPixmap *, QPixmap *> p = {imgEnter, imgLeave};
//	OnlineWgt w;
//	w.show();
	
//	LevelFigurePnl w(50, 30, 1);
//	w.show();
	
//	WidgetInfo wi;
//	wi.show();
//	ButtonPanel *w = new ButtonPanel("Пауза", {"Перезапуск", "Выход"}, wi.getPanelPixmaps(), 1);
//	NextFigurePnl *w = new NextFigurePnl(30, 1);
//	w->setVisible(true);
//	w->show();
//	w->deleteLater();
//	PushLabel *w = new PushLabel("Test");
//	w->show();
//	delete w;
	
//	QImage *green = new QImage(":Images/Blocks/OBlockOriginal.png");
	
	return app.exec();
}
