#ifndef CONNECTONLINEWGT_H
#define CONNECTONLINEWGT_H

#include <QWidget>

class PushLabel;
class QLineEdit;
class QSpacerItem;
class QSoundEffect;

namespace Ui {
class ConnectOnlineWgt;
}

class ConnectOnlineWgt : public QWidget
{
	Q_OBJECT
	
public:
	explicit ConnectOnlineWgt(QPair<QHash<QString, QPixmap *>, QHash<QString, QSoundEffect *> > media, 
							  qreal mult, QWidget *parent = nullptr);
	~ConnectOnlineWgt();
	
private slots:
	void createBtnPush();
	void connectBtnPush();
	void cancelBtnPush();
	
signals:
	void createSignal();
	void connectSignal(QString ip);
	void exitSignal();
	
private:
	Ui::ConnectOnlineWgt *ui;
	
	std::unique_ptr<PushLabel> createBtn;
	std::unique_ptr<PushLabel> connectBtn;
	std::unique_ptr<PushLabel> cancelBtn;
	std::unique_ptr<QLineEdit> ipLine;
	std::unique_ptr<QSpacerItem> spacer1;
	std::unique_ptr<QSpacerItem> spacer2;
	
	quint16 ELEMENT_HEIGHT;
	quint16 ELEMENT_WIDTH;
	quint16 BORDER;
	
	const quint16 BASE_HEIGHT = 250;
	const quint16 BASE_WEIGHT = 200;
	const quint16 BASE_ELEMENT_HEIGHT = 30;
	const quint16 BASE_ELEMENT_WIDTH = 180;
	const quint16 BASE_BORDER = 10;
	const quint8 BASE_FONT = 20;
	const qreal MULT;
};

#endif // CONNECTONLINEWGT_H
