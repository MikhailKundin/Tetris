#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QWidget>
#include <QMap>

class PlaygroundPnl : public QWidget
{
public:
	PlaygroundPnl(qint8 blockSize, QWidget *parent = nullptr);
	void update(const QMap<qint16, QImage *>& grid);
	
private:
	void paintEvent(QPaintEvent *e) override;
	void drawGrid();
	void drawPalayground();
	
	 QMap<qint16, QImage*> m_grid;
	
	const qint8 BLOCK_SIZE;
	const qint8 GRID_WIDTH = 1;
};

#endif // PLAYGROUND_H
