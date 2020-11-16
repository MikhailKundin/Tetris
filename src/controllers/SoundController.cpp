#include "SoundController.h"

#include <QAudioDeviceInfo>

#include <QDebug>

QSoundEffect *SoundController::channel1 = new QSoundEffect;

void SoundController::startMainMenu()
{
	channel1->setSource(QUrl::fromLocalFile("../../etc/Sounds/MainMenu.wav"));
	channel1->setVolume(0.5);
	channel1->setLoopCount(QSoundEffect::Infinite);
	channel1->play();
}

void SoundController::stopMainMenu()
{
	channel1->stop();
}
