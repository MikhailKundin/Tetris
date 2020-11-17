#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

#include <QObject>
#include <QHash>

class QSoundEffect;

class SoundController : public QObject
{
	Q_OBJECT
	
public:
	enum Name : quint8 {/*MainTheme, */Down, Right, Left, Rotate, Defeat, RowDeleted};
	
	SoundController();
	SoundController(const QHash<Name, QSoundEffect *> &sounds);
	~SoundController();
	
	void setSounds(const QHash<Name, QSoundEffect *> &sounds);
	
public slots:
	void playMainTheme();
	void stopMainTheme();
	
	void moveDown();
	void moveRight();
	void moveLeft();
	void rotate();
	void rowDeleted();
	void defeat();
	
signals:
	void stopMainThemeSignal();
	
private:
	QHash<Name, QSoundEffect *> m_sounds;
};

#endif // SOUNDCONTROLLER_H
