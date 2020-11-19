#include "PushLabel.h"

#include <QEvent>
#include <QPixmap>
#include <QSoundEffect>

PushLabel::PushLabel(QString name, QWidget *parent) : QLabel(parent)
{
	setObjectName(name);
	setAlignment(Qt::AlignCenter);
	setText(objectName());
	
	imageLbl = std::make_unique<QLabel>(this);
	
	//imgEnter = std::make_unique<QPixmap>();
	//imgLeave = std::make_unique<QPixmap>();
	
	installEventFilter(this);
}

PushLabel::~PushLabel()
{
	imgEnter = nullptr;
	imgLeave = nullptr;
	enterSound = nullptr;
}

void PushLabel::loadPixmaps(QPixmap *enter, QPixmap *leave)
{
	imgEnter = enter;
	imgLeave = leave;
	imageLbl->setPixmap(imgLeave->scaled(size()));
}

void PushLabel::loadSounds(QSoundEffect *enter)
{
	enterSound = enter;
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
			enterSound->play();
			hoverEnter();
			return true;
		case QEvent::Leave:
			hoverLeave();
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
	if (imgLeave != nullptr)
	{
		imageLbl->setPixmap(imgLeave->scaled(size()));
	}
}
