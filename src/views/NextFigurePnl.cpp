#include "NextFigurePnl.h"

#include <QPainter>
#include <QRectF>
#include <QLabel>

#include "../TetrisInfo.h"
#include "../AbstractFigure.h"

#include <QDebug>

NextFigurePnl::NextFigurePnl(quint8 blockSize, qreal mult, QWidget *parent) : QWidget(parent)
{
	BLOCK_SIZE = static_cast<quint16>(blockSize * mult);
	BORDER_WIDTH = static_cast<quint8>(BORDER_WIDTH * mult);
	
	WIDTH = BLOCK_SIZE*4 + BORDER_WIDTH*2;
	HEIGHT = BLOCK_SIZE*2 + BORDER_WIDTH*2;
	
	resize(WIDTH, HEIGHT);
	
	QPixmap img(":/Images/Backgrounds/NextFigureBackground.png");
	border = std::make_unique<QLabel>(this);
	border->resize(size());
	border->setPixmap(img.scaled(border->size()));
	
	clear();
}

void NextFigurePnl::update(AbstractFigure *&figure)
{
	image = figure->getBlocks().at(0).getImage();
	type = figure->getType();
	repaint();
}

void NextFigurePnl::clear()
{
	type = -1;
}

void NextFigurePnl::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e)
	
	drawFigure();
}

void NextFigurePnl::drawFigure()
{
	QPainter painter(this);
	QRect rect;
	
	switch (type)
	{
	case TetrisInfo::Figures::I:
		drawI(painter, rect);
		break;
	case TetrisInfo::Figures::O:
		drawO(painter, rect);
		break;
	case TetrisInfo::Figures::T:
		drawT(painter, rect);
		break;
	case TetrisInfo::Figures::L:
		drawL(painter, rect);
		break;
	case TetrisInfo::Figures::J:
		drawJ(painter, rect);
		break;
	case TetrisInfo::Figures::S:
		drawS(painter, rect);
		break;
	case TetrisInfo::Figures::Z:
		drawZ(painter, rect);
		break;
	}
}

void NextFigurePnl::drawI(QPainter &painter, QRect &rect)
{
	quint16 x = BORDER_WIDTH;
	quint16 y = HEIGHT/2 - BLOCK_SIZE/2;
	
	for (qint8 i = 0; i < 3; i++)
	{
		rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
		painter.drawImage(rect, *image);
		x += BLOCK_SIZE;
	}
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
}

void NextFigurePnl::drawO(QPainter &painter, QRect &rect)
{
	quint16 x = BORDER_WIDTH + BLOCK_SIZE;
	quint16 y = BORDER_WIDTH;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	x += BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	y += BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	x -= BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
}

void NextFigurePnl::drawT(QPainter &painter, QRect &rect)
{	
	quint16 x = BORDER_WIDTH + BLOCK_SIZE/2;
	quint16 y = BORDER_WIDTH;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	x += BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	y += BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	x += BLOCK_SIZE;
	y -= BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
}

void NextFigurePnl::drawL(QPainter &painter, QRect &rect)
{
	quint16 x = BORDER_WIDTH + BLOCK_SIZE/2;
	quint16 y = BORDER_WIDTH + BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	y -= BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	x += BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	x += BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
}

void NextFigurePnl::drawJ(QPainter &painter, QRect &rect)
{
	quint16 x = BORDER_WIDTH + BLOCK_SIZE/2;
	quint16 y = BORDER_WIDTH;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	x += BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	x += BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	y += BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
}

void NextFigurePnl::drawS(QPainter &painter, QRect &rect)
{
	quint16 x = BORDER_WIDTH + BLOCK_SIZE/2;
	quint16 y = BORDER_WIDTH + BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	x += BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	y -= BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	x += BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
}

void NextFigurePnl::drawZ(QPainter &painter, QRect &rect)
{
	quint16 x = BORDER_WIDTH + BLOCK_SIZE/2;
	quint16 y = BORDER_WIDTH;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	x += BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	y += BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
	x += BLOCK_SIZE;
	
	rect.setRect(x, y, BLOCK_SIZE+1, BLOCK_SIZE+1);
	painter.drawImage(rect, *image);
}
