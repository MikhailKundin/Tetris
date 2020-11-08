#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QWidget>
#include <QMap>

class PlaygroundPnl : public QWidget
{
public:
	enum PgState : quint8 {Defeat, Ready, NotReady, Default};
	
	PlaygroundPnl(quint8 blockSize, qreal mult, QWidget *parent = nullptr);
	void update(const QMap<qint16, QImage *> &grid);
	void setState(PgState state);
	
private:
	void paintEvent(QPaintEvent *e) override;
	void drawGrid();
	void drawPalayground();
	
	 QMap<qint16, QImage*> m_grid;
	
	quint8 BLOCK_SIZE;
	const quint8 GRID_WIDTH = 1;
};

#endif // PLAYGROUND_H
