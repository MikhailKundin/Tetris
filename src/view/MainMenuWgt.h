#ifndef MAINMENUWDT_H
#define MAINMENUWDT_H

#include "WidgetInfo.h"

class PushLabel;

namespace Ui {
class MainMenuWdt;
}

class MainMenuWgt : public WidgetInfo
{
	Q_OBJECT
	
public:
	explicit MainMenuWgt(WidgetInfo *parent = nullptr);
	~MainMenuWgt();
	
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
	
	std::unique_ptr<QPixmap> logoImg;
	std::unique_ptr<PushLabel> singleBtn;
	std::unique_ptr<PushLabel> onlineBtn;
	std::unique_ptr<PushLabel> exitBtn;
	
	const quint16 BASE_BUTTON_WIDTH = 200;
	const quint16 BASE_BUTTON_HEIGHT = 50;
	const quint8 BASE_FONT = 20;
};

#endif // MAINMENUWDT_H
