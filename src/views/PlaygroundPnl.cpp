#include "PlaygroundPnl.h"

#include <QPainter>
#include <QRectF>

#include "../TetrisInfo.h"

#include <QDebug>

PlaygroundPnl::PlaygroundPnl(quint8 blockSize, qreal mult, QWidget *parent) : 
	QWidget(parent), BLOCK_SIZE(blockSize)
{
	BLOCK_SIZE = static_cast<quint8>(blockSize * mult);
	
	resize(TetrisInfo::COLUMN_COUNT*BLOCK_SIZE + 1, TetrisInfo::ROW_COUNT*BLOCK_SIZE + 1);
	
	QPalette pal(palette());
	pal.setColor(QPalette::Window, qRgb(20, 20, 60));
	setAutoFillBackground(true);
	setPalette(pal);
}

void PlaygroundPnl::update(const QMap<qint16, QImage *>& grid)
{
	m_grid.clear();
	m_grid.insert(grid);
	
	repaint();
}

void PlaygroundPnl::setState(PlaygroundPnl::PgState state)
{
	QPalette pal(palette());
	QColor color;
	switch (state)
	{
	case Default:
		color = qRgb(20, 20, 60);
		break;
	case Defeat:
		color = Qt::darkRed;
		break;
	case Ready:
		color = Qt::darkGreen;
		break;
	case NotReady:
		color = Qt::darkYellow;
		break;
	}
	pal.setColor(QPalette::Window, color);
	setPalette(pal);
}

void PlaygroundPnl::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e)
	
	drawGrid();
	drawPalayground();
}

void PlaygroundPnl::drawGrid()
{
	QPainter painter(this);
	painter.setPen(Qt::darkGray);
	
	for (qint16 i = 0; i <= TetrisInfo::ROW_COUNT; i++)
	{
		painter.drawLine(0, i * BLOCK_SIZE, TetrisInfo::COLUMN_COUNT * BLOCK_SIZE, i * BLOCK_SIZE);
	}
	
	for (qint16 i = 0; i <= TetrisInfo::COLUMN_COUNT; i++)
	{
		painter.drawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, TetrisInfo::ROW_COUNT * BLOCK_SIZE);
	}
}

void PlaygroundPnl::drawPalayground()
{
	QPainter painter(this);
	QRectF rect;
	for (QMap<qint16, QImage *>::const_iterator it = m_grid.constBegin(); it != m_grid.constEnd(); it++)
	{
		qint16 coord = it.key();
		qint16 x = coord % TetrisInfo::COLUMN_COUNT;
		qint16 y = coord / TetrisInfo::COLUMN_COUNT;
		
		rect.setRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE+1, BLOCK_SIZE+1);
		painter.drawImage(rect, *it.value());
	}
}
