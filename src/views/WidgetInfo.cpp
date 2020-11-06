#include "WidgetInfo.h"

#include <QApplication>
#include <QScreen>

WidgetInfo::WidgetInfo(QWidget *parent) : 
	QWidget(parent)
{
	MULT = static_cast<qreal>(QApplication::screens().at(0)->geometry().height()) / BASE_SCREEN_HEIGHT;
	
	buttonEnter = new QPixmap(":/Images/Buttons/HoverEnter.png");
	buttonLeave = new QPixmap(":/Images/Buttons/HoverLeave.png");
	backPanel = new QPixmap(":/Images/Backgrounds/200x200PanelBackground.png");
}

WidgetInfo::~WidgetInfo()
{
	delete buttonEnter;
	delete buttonLeave;
	delete backPanel;
}

qreal WidgetInfo::getMult() const
{
	return MULT;
}

const QHash<QString, QPixmap *> WidgetInfo::getPanelPixmaps() const
{
	return {{"enter", buttonEnter}, {"leave", buttonLeave}, {"back", backPanel}};
}
