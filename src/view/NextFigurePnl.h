#ifndef NEXTFIGUREPNL_H
#define NEXTFIGUREPNL_H

#include <QWidget>
#include <QLabel>

class AbstractFigure;
class NextFigurePnl : public QWidget
{
public:
	NextFigurePnl(qint8 blockSize, QWidget *parent = nullptr);
	
	void update(AbstractFigure *&figure);
	
private:
	void paintEvent(QPaintEvent *e) override;
	void drawFigure();
	
	void drawI(QPainter &painter, QRect &rect);
	void drawO(QPainter &painter, QRect &rect);
	void drawT(QPainter &painter, QRect &rect);
	void drawL(QPainter &painter, QRect &rect);
	void drawJ(QPainter &painter, QRect &rect);
	void drawS(QPainter &painter, QRect &rect);
	void drawZ(QPainter &painter, QRect &rect);
	
	qint8 type;
	QImage *image;
	std::unique_ptr<QLabel> border;
	const qint8 BLOCK_SIZE;
	qint16 WIDTH;
	qint16 HEIGHT;
	qint16 BORDER_WIDTH;
};

#endif // NEXTFIGUREPNL_H
