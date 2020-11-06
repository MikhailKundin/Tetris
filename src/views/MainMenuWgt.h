#ifndef MAINMENUWDT_H
#define MAINMENUWDT_H

#include "WidgetInfo.h"

class PushLabel;
class QLabel;
class QSpacerItem;

namespace Ui {
class MainMenuWdt;
}

class MainMenuWgt : public WidgetInfo
{
	Q_OBJECT
	
public:
	explicit MainMenuWgt(WidgetInfo *parent = nullptr);
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
	std::unique_ptr<QSpacerItem> spacer;
	
	const quint16 BASE_BUTTON_WIDTH = 200;
	const quint16 BASE_BUTTON_HEIGHT = 50;
	const quint8 BASE_FONT = 20;
	const quint16 BASE_LOGO_WIDTH = 300;
	const quint16 BASE_LOGO_HEIGHT = 100;
	const quint16 BASE_SPACER_HEIGHT = 100;
};

#endif // MAINMENUWDT_H
