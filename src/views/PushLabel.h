#ifndef PUSHLABEL_H
#define PUSHLABEL_H

#include <QLabel>

class QSoundEffect;

class PushLabel : public QLabel
{
	Q_OBJECT
	
public:
	PushLabel(QString name, QWidget *parent = nullptr);
	~PushLabel() override;
	void loadPixmaps(QPixmap *enter, QPixmap *leave);
	void loadSounds(QSoundEffect *enter);
	
signals:
	void clicked();
	
private:
	bool eventFilter(QObject *obj, QEvent *e) override;
	void resizeEvent(QResizeEvent *e) override;
	void hoverEnter();
	void hoverLeave();
	
	std::unique_ptr<QLabel> imageLbl;
	
	QPixmap *imgEnter;
	QPixmap *imgLeave;
	QSoundEffect *enterSound;
};

#endif // PUSHLABEL_H
