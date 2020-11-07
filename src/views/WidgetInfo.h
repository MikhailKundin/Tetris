#ifndef WIDGETINFO_H
#define WIDGETINFO_H

#include <QWidget>

class WidgetInfo : public QWidget
{
public:
	WidgetInfo(QWidget *parent = nullptr);
	~WidgetInfo();
	qreal getMult() const;
	const QHash<QString, QPixmap *> getPanelPixmaps() const;
	
protected:
	const quint8 BLOCK_SIZE = 30;
	qreal MULT;
	QPixmap *buttonEnter;
	QPixmap *buttonLeave;
	QPixmap *backPanel;
	
private:
	const quint16 BASE_SCREEN_HEIGHT = 768;
};

#endif // WIDGETINFO_H
