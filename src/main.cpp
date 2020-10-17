#include <QApplication>

#include "testgrid.h"
#include "testpaint.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	TestGrid w;
	//TestPaint w;
	//w.resize(500, 500);
	w.show();
	
	return app.exec();
}
