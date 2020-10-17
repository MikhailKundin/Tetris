#include "testpaint.h"

#include <QDebug>

TestPaint::TestPaint(QWidget* parent) : QWidget(parent)
{
	//resize(300, 600);
	setMinimumSize(300, 600);
	setMaximumSize(300, 600);
}

void TestPaint::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e)
	
	draw();
}

void TestPaint::draw()
{
	QPainter painter(this);
	QImage block("..\\..\\etc\\Images\\Blocks\\Original\\LBlockOriginal.png");
	QRectF pos;
	
	
	
	for (int i = 0; i < 10; i++)
	{		
		pos.setRect(i*30, i*30, 30, 30);
		painter.drawImage(pos, block);
		
		pos.setRect((9-i)*30, (i+10)*30, 30, 30);
		painter.drawImage(pos, block);
	}
}
