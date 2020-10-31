#include "PushLabel.h"

#include <QEvent>

#include <QDebug>

PushLabel::PushLabel(QString name, QString hoverEnter,QString hoverLeave) : OBJECT_NAME(name)
{
	setObjectName(OBJECT_NAME);
	//setAlignment(Qt::AlignVCenter);
	//setAlignment(Qt::AlignHCenter);
	setAlignment(Qt::AlignCenter);
	
	imgEnter = std::make_unique<QPixmap>(hoverEnter);
	imgLeave = std::make_unique<QPixmap>(hoverLeave);
	
	setPixmap(imgLeave->scaled(size()));
}

bool PushLabel::eventFilter(QObject *obj, QEvent *e)
{
	if (obj->objectName() == OBJECT_NAME)
	{
		switch (e->type())
		{
		case QEvent::MouseButtonPress:
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
	
	setPixmap(pixmap(Qt::ReturnByValue).scaled(size()));
}

void PushLabel::hoverEnter()
{
	setPixmap(imgEnter->scaled(size()));
}

void PushLabel::hoverLeave()
{
	setPixmap(imgLeave->scaled(size()));
}
