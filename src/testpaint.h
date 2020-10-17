#ifndef TESTPAINT_H
#define TESTPAINT_H

#include <QWidget>
#include <QLabel>

#include <QPainter>
#include <QImage>
#include <QRectF>

class TestPaint : public QWidget
{
public:
	TestPaint(QWidget* parent = nullptr);
	
private:
	void paintEvent(QPaintEvent* e) override;
	void draw();
};

#endif // TESTPAINT_H
