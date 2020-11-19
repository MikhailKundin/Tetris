#ifndef BUTTONPANEL_H
#define BUTTONPANEL_H

#include <QWidget>

class PushLabel;
class QLabel;
class QSpacerItem;
class QSoundEffect;

namespace Ui {
class ButtonPanel;
}

class ButtonPanel : public QWidget
{
	Q_OBJECT
	
public:
	explicit ButtonPanel(QString info, QList<QString> buttons, 
						 QPair<QHash<QString, QPixmap *>, QHash<QString, QSoundEffect *> > media,
						 qreal mult, QWidget *parent = nullptr);
	explicit ButtonPanel(QList<QString> buttons, 
						 QPair<QHash<QString, QPixmap *>, QHash<QString, QSoundEffect *> > media,
						 qreal mult, QWidget *parent = nullptr);
	~ButtonPanel();
	
signals:
	void clicked(const QString &objectName);
	
private slots:
	void buttonClicked();
	
private:
	Ui::ButtonPanel *ui;
	
	void buildPanel(QList<QString> buttons, QHash<QString, QPixmap *> pixmaps, QHash<QString, 
					QSoundEffect *> sounds);
	
	QList<PushLabel *> m_buttons;
	std::unique_ptr<QLabel> infoLbl;
	std::unique_ptr<QSpacerItem> spacer;
	
	quint16 ELEMENT_HEIGHT;
	quint16 ELEMENT_WIDTH;
	quint16 BORDER;
	
	const quint16 BASE_HEIGHT = 30;
	const quint16 BASE_WIDTH = 200;
	const quint16 BASE_ELEMENT_HEIGHT = 30;
	const quint16 BASE_ELEMENT_WIDTH = 180;
	const quint16 BASE_BORDER = 20;
	const quint8 BASE_FONT = 16;
	const quint16 BASE_SPACE = 30;
	const qreal MULT;
};

#endif // BUTTONPANEL_H
