#include "playground.h"

#include <QPainter>
#include <QRectF>

#include <QDebug>

Playground::Playground(qint8 row, qint8 column, QWidget *parent) : 
	QWidget(parent), COLUMN_COUNT(column), ROW_COUNT(row)
{
	setMinimumSize(COLUMN_COUNT * BLOCK_SIZE + 1, ROW_COUNT * BLOCK_SIZE + 1);
}

void Playground::update(const QMap<qint16, QImage *>& map)
{
	for (QMap<qint16, QImage *>::const_iterator it = map.constBegin(); it != map.constEnd(); it++)
	{
		m_map.insert(it.key(), it.value());
	}
	
	repaint();
}

void Playground::paintEvent(QPaintEvent *e)
{
	Q_UNUSED(e)
	
	drawGrid();
	drawPalayground();
}

void Playground::drawGrid()
{
	QPainter painter(this);
	painter.setPen(Qt::gray);
	
	for (qint16 i = 0; i <= ROW_COUNT; i++)
	{
		painter.drawLine(0, i * BLOCK_SIZE, COLUMN_COUNT * BLOCK_SIZE, i * BLOCK_SIZE);
	}
	
	for (qint16 i = 0; i <= COLUMN_COUNT; i++)
	{
		painter.drawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, ROW_COUNT * BLOCK_SIZE);
	}
}

void Playground::drawPalayground()
{
	QPainter painter(this);
	QRectF rect;
	for (QMap<qint16, QImage *>::const_iterator it = m_map.constBegin(); it != m_map.constEnd(); it++)
	{
		qint16 coord = it.key();
		qint16 x = coord % COLUMN_COUNT;
		qint16 y = coord / COLUMN_COUNT;
		
		rect.setRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE+1, BLOCK_SIZE+1);
		painter.drawImage(rect, *it.value());
	}
}
