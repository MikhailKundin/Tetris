#ifndef MAINMENUWDT_H
#define MAINMENUWDT_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class MainMenuWdt;
}

class MainMenuWdt : public QWidget
{
	Q_OBJECT
	
public:
	explicit MainMenuWdt(QWidget *parent = nullptr);
	~MainMenuWdt();
	
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
};

#endif // MAINMENUWDT_H
