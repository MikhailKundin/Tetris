#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QWidget>
#include <QMap>

class Playground : public QWidget
{
public:
	Playground(qint8 row, qint8 column, QWidget *parent = nullptr);
	void update(const QMap<qint16, QImage *>& map);
	
private:
	void paintEvent(QPaintEvent *e) override;
	void drawGrid();
	void drawPalayground();
	
	 QMap<qint16, QImage*> m_map;
	
	const qint8 BLOCK_SIZE = 30;
	const qint8 COLUMN_COUNT;
	const qint8 ROW_COUNT;
	const qint8 GRID_WIDTH = 1;
};

#endif // PLAYGROUND_H
