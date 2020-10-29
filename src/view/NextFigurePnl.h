#ifndef NEXTFIGUREPNL_H
#define NEXTFIGUREPNL_H

#include <QWidget>

class QLabel;
class AbstractFigure;

class NextFigurePnl : public QWidget
{
public:
	NextFigurePnl(quint8 blockSize, qreal mult, QWidget *parent = nullptr);
	
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
	quint16 BLOCK_SIZE;
	quint16 WIDTH;
	quint16 HEIGHT;
	quint8 BORDER_WIDTH = 7;
};

#endif // NEXTFIGUREPNL_H
