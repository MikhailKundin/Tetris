#ifndef PUSHLABEL_H
#define PUSHLABEL_H

#include <QLabel>

class PushLabel : public QLabel
{
	Q_OBJECT
	
public:
	PushLabel(QString name, QString hoverEnter,QString hoverLeave);
	
signals:
	void clicked();
	void hoverEnterSignal();
	void hoverLeaveSignal();
	
private:
	bool eventFilter(QObject *obj, QEvent *e) override;
	void resizeEvent(QResizeEvent *e) override;
	void hoverEnter();
	void hoverLeave();
	
	const QString OBJECT_NAME;
	std::unique_ptr<QPixmap> imgEnter;
	std::unique_ptr<QPixmap> imgLeave;
};

#endif // PUSHLABEL_H
