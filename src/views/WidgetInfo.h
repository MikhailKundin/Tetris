#ifndef WIDGETINFO_H
#define WIDGETINFO_H

#include <QWidget>

class QSoundEffect;

class WidgetInfo : public QWidget
{
public:
	WidgetInfo(QWidget *parent = nullptr);
	~WidgetInfo();
	qreal getMult() const;
	const QPair<QHash<QString, QPixmap *>, QHash<QString, QSoundEffect *> > getPanelMedia() const;
	
protected:
	const quint8 BLOCK_SIZE = 30;
	qreal MULT;
	QPixmap *buttonEnter;
	QPixmap *buttonLeave;
	QPixmap *backPanel;
	QSoundEffect *enter;
	
private:
	const quint16 BASE_SCREEN_HEIGHT = 680;
};

#endif // WIDGETINFO_H
