#include <QApplication>

#include "sockets.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	Sockets sockets;
	sockets.show();
	
	return a.exec();
}
