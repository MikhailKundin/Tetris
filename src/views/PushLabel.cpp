#include "PushLabel.h"

#include <QEvent>
#include <QPixmap>

#include <QDebug>

PushLabel::PushLabel(QString name, QWidget *parent) : QLabel(parent)
{
	setObjectName(name);
	setAlignment(Qt::AlignCenter);
	setText(objectName());
	
	imageLbl = std::make_unique<QLabel>(this);
	
	imgEnter = std::make_unique<QPixmap>();
	imgLeave = std::make_unique<QPixmap>();
	
	installEventFilter(this);
}

void PushLabel::loadPixmaps(QPixmap *enter, QPixmap *leave)
{
	imgEnter = std::make_unique<QPixmap>(*enter);
	imgLeave = std::make_unique<QPixmap>(*leave);
	imageLbl->setPixmap(imgLeave->scaled(size()));
}

bool PushLabel::eventFilter(QObject *obj, QEvent *e)
{
	if (obj->objectName() == objectName())
	{
		switch (e->type())
		{
		case QEvent::MouseButtonRelease:
			emit clicked();
			return true;
		case QEvent::Enter:
			hoverEnter();
			emit hoverEnterSignal();
			return true;
		case QEvent::Leave:
			hoverLeave();
			emit hoverLeaveSignal();
			return true;
		default:
			return false;
		}
	}
	
	return false;
}

void PushLabel::resizeEvent(QResizeEvent *e)
{
	Q_UNUSED(e)
	
	imageLbl->resize(size());
	imageLbl->setPixmap(imgLeave->scaled(size()));
}

void PushLabel::hoverEnter()
{
	imageLbl->setPixmap(imgEnter->scaled(size()));
}

void PushLabel::hoverLeave()
{
	imageLbl->setPixmap(imgLeave->scaled(size()));
}