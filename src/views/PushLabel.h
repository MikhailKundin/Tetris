#ifndef PUSHLABEL_H
#define PUSHLABEL_H

#include <QLabel>

class PushLabel : public QLabel
{
	Q_OBJECT
	
public:
	PushLabel(QString name, QWidget *parent = nullptr);
	void loadPixmaps(QPixmap *enter, QPixmap *leave);
	
signals:
	void clicked();
	void hoverEnterSignal();
	void hoverLeaveSignal();
	
private:
	bool eventFilter(QObject *obj, QEvent *e) override;
	void resizeEvent(QResizeEvent *e) override;
	void hoverEnter();
	void hoverLeave();
	
	std::unique_ptr<QPixmap> imgEnter;
	std::unique_ptr<QPixmap> imgLeave;
	std::unique_ptr<QLabel> imageLbl;
};

#endif // PUSHLABEL_H
