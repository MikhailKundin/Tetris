#ifndef MAINMENUWDT_H
#define MAINMENUWDT_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class MainMenuWdt;
}

class MainMenuWgt : public QWidget
{
	Q_OBJECT
	
public:
	explicit MainMenuWgt(QWidget *parent = nullptr);
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
};

#endif // MAINMENUWDT_H
