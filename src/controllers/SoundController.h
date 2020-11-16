#ifndef SOUNDCONTROLLER_H
#define SOUNDCONTROLLER_H

#include <QObject>
#include <QSoundEffect>

class SoundController : public QObject
{	
public:
	static void startMainMenu();
	static void stopMainMenu();
	
private:
	static QSoundEffect *channel1;
};

#endif // SOUNDCONTROLLER_H
