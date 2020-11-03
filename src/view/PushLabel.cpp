#include "PushLabel.h"

#include <QEvent>
#include <QPixmap>

#include <QDebug>

PushLabel::PushLabel(QString name, QWidget *parent) : QLabel(parent)
{
	setObjectName(name);
	setAlignment(Qt::AlignCenter);
	setText(objectName());
	
	textLbl = std::make_unique<QLabel>(this);
	
	imgEnter = std::make_unique<QPixmap>();
	imgLeave = std::make_unique<QPixmap>();
	
	installEventFilter(this);
}

void PushLabel::loadPixmaps(const QString &enter, const QString &leave)
{
	imgEnter->load(enter);
	imgLeave->load(leave);
	textLbl->setPixmap(imgLeave->scaled(size()));
}

bool PushLabel::eventFilter(QObject *obj, QEvent *e)
{
	if (obj->objectName() == objectName())
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
	
	textLbl->resize(size());
	textLbl->setPixmap(imgLeave->scaled(size()));
}

void PushLabel::hoverEnter()
{
	textLbl->setPixmap(imgEnter->scaled(size()));
}

void PushLabel::hoverLeave()
{
	textLbl->setPixmap(imgLeave->scaled(size()));
}
