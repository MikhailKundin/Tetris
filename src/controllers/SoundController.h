#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

#include <QObject>
#include <QHash>

class QSoundEffect;

class SoundController : public QObject
{
	Q_OBJECT
	
public:
	enum Mode : quint8 {MainMenu, Playground};
	
	SoundController();
	SoundController(Mode mode);
	~SoundController();
	
public slots:
	void playMainTheme();
	
	void moveDown();
	void moveRight();
	void moveLeft();
	void rotate();
	void rowDeleted();
	void defeat();
	
	void setMute(bool state);
	void mute();
	void unmute();
	
private:
	enum Name : quint8 {MainTheme, Down, Right, Left, Rotate, Defeat, RowDeleted};
	
	void makeMainMenu();
	void makePlayground();
	
	QHash<Name, QSoundEffect *> sounds;
};

#endif // SOUNDCONTROLLER_H
