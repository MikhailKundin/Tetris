#ifndef MAINMENUWDT_H
#define MAINMENUWDT_H

#include "WidgetInfo.h"

class PushLabel;
class QLabel;

namespace Ui {
class MainMenuWdt;
}

class MainMenuWgt : public WidgetInfo
{
	Q_OBJECT
	
public:
	explicit MainMenuWgt(QPair<QPixmap *, QPixmap *> buttonImg, WidgetInfo *parent = nullptr);
	~MainMenuWgt();
	QString test();
	
private slots:
	void singleBtnClicked();
	void onlineBtnClicked();
	void exitBtnClicked();
	
signals:
	void singleSignal();
	void onlineSignal();
	void exitSignal();
	
private:
	Ui::MainMenuWdt *ui;
	
	std::unique_ptr<PushLabel> singleBtn;
	std::unique_ptr<PushLabel> onlineBtn;
	std::unique_ptr<PushLabel> exitBtn;
	
	const quint16 BASE_BUTTON_WIDTH = 200;
	const quint16 BASE_BUTTON_HEIGHT = 50;
	const quint8 BASE_FONT = 20;
	const quint16 BASE_LOGO_WIDTH = 300;
	const quint16 BASE_LOGO_HEIGHT = 100;
};

#endif // MAINMENUWDT_H
