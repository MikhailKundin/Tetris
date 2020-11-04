#include "WidgetInfo.h"

#include <QApplication>
#include <QScreen>

WidgetInfo::WidgetInfo(QPair<QPixmap *, QPixmap *> buttonImg, QWidget *parent) : 
	QWidget(parent), m_buttonImg(buttonImg)
{
	MULT = static_cast<qreal>(QApplication::screens().at(0)->geometry().height()) / BASE_SCREEN_HEIGHT;
}
