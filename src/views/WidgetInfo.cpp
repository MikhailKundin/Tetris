#include "WidgetInfo.h"

#include <QApplication>
#include <QScreen>
#include <QSoundEffect>

WidgetInfo::WidgetInfo(QWidget *parent) : 
	QWidget(parent)
{
	MULT = static_cast<qreal>(QApplication::screens().at(0)->geometry().height()) / BASE_SCREEN_HEIGHT;
	
	buttonEnter = new QPixmap(":/Images/Buttons/HoverEnter.png");
	buttonLeave = new QPixmap(":/Images/Buttons/HoverLeave.png");
	backPanel = new QPixmap(":/Images/Backgrounds/200x200PanelBackground.png");
	enter = new QSoundEffect;
	enter->setSource(QUrl::fromLocalFile(":Sounds/ButtonEnter.wav"));
}

WidgetInfo::~WidgetInfo()
{
	delete buttonEnter;
	delete buttonLeave;
	delete backPanel;
	enter->deleteLater();
}

qreal WidgetInfo::getMult() const
{
	return MULT;
}

const QPair<QHash<QString, QPixmap *>, QHash<QString, QSoundEffect *> > WidgetInfo::getPanelMedia() const
{
	QHash<QString, QPixmap *> imgMap = {{"enter", buttonEnter}, {"leave", buttonLeave}, {"back", backPanel}};
	QHash<QString, QSoundEffect *> soundMap = {{"enterSound", enter}};
	return {imgMap, soundMap};
}
