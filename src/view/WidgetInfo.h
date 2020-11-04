#ifndef WIDGETINFO_H
#define WIDGETINFO_H

#include <QWidget>

class WidgetInfo : public QWidget
{
public:
	WidgetInfo(QPair<QPixmap *, QPixmap *> buttonImg, QWidget *parent = nullptr);
	qreal getMult() const;
	
protected:
	const quint8 BLOCK_SIZE = 30;
	qreal MULT;
	QPair<QPixmap *, QPixmap *> m_buttonImg;
	
private:
	const quint16 BASE_SCREEN_HEIGHT = 768;
};

#endif // WIDGETINFO_H
