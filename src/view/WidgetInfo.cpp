#include "WidgetInfo.h"

#include <QApplication>
#include <QScreen>

WidgetInfo::WidgetInfo(QWidget *parent) : QWidget(parent)
{
	MULT = static_cast<qreal>(QApplication::screens().at(0)->geometry().height()) / BASE_SCREEN_HEIGHT;
}
