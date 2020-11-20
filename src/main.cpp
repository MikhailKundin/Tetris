#include <QApplication>

#include "views/MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	MainWindow window;
	window.move(750, 0);
	window.showFullScreen();
	
	return app.exec();
}
