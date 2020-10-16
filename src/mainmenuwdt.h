#ifndef MAINMENUWDT_H
#define MAINMENUWDT_H

#include <QWidget>

namespace Ui {
class MainMenuWdt;
}

class MainMenuWdt : public QWidget
{
	Q_OBJECT
	
public:
	explicit MainMenuWdt(QWidget *parent = nullptr);
	~MainMenuWdt();
	
private:
	Ui::MainMenuWdt *ui;
};

#endif // MAINMENUWDT_H
