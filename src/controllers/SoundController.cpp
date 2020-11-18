#include "SoundController.h"

#include <QSoundEffect>

#include <QDebug>

SoundController::SoundController()
{
	makeMainMenu();
	makePlayground();
}

SoundController::SoundController(Mode mode)
{
	switch (mode)
	{
	case MainMenu:
		makeMainMenu();
		break;
	case Playground:
		makePlayground();
		break;
	}
}

SoundController::~SoundController()
{
	foreach (QSoundEffect *sound, sounds)
	{
		sound->setSource(QUrl::fromLocalFile(":Sounds/null"));
		sound->deleteLater();
	}
}

void SoundController::playMainTheme()
{
	for (QHash<Name, QSoundEffect *>::ConstIterator it = sounds.begin(); it != sounds.end(); it++)
	{
		if (it.key() == Name::MainTheme)
		{
			it.value()->play();
		}
	}
}

void SoundController::stopMainTheme()
{
	for (QHash<Name, QSoundEffect *>::ConstIterator it = sounds.begin(); it != sounds.end(); it++)
	{
		if (it.key() == Name::MainTheme)
		{
			it.value()->stop();
		}
	}
}

void SoundController::moveDown()
{
	bool check = true;
	QSoundEffect *sound = nullptr;
	for (QHash<Name, QSoundEffect *>::ConstIterator it = sounds.begin(); it != sounds.end(); it++)
	{
		if (it.key() == Name::Down)
		{
			sound = it.value();
			if (sound->isPlaying())
			{
				check = false;
				break;
			}
		}
	}
	if (check && sound != nullptr)
	{
		sound->play();
	}
}

void SoundController::moveRight()
{
	bool check = true;
	QSoundEffect *sound = nullptr;
	for (QHash<Name, QSoundEffect *>::ConstIterator it = sounds.begin(); it != sounds.end(); it++)
	{
		if (it.key() == Name::Right)
		{
			sound = it.value();
			if (sound->isPlaying())
			{
				check = false;
				break;
			}
		}
	}
	if (check && sound != nullptr)
	{
		sound->play();
	}
}

void SoundController::moveLeft()
{
	bool check = true;
	QSoundEffect *sound = nullptr;
	for (QHash<Name, QSoundEffect *>::ConstIterator it = sounds.begin(); it != sounds.end(); it++)
	{
		if (it.key() == Name::Left)
		{
			sound = it.value();
			if (sound->isPlaying())
			{
				check = false;
				break;
			}
		}
	}
	if (check && sound != nullptr)
	{
		sound->play();
	}
}

void SoundController::rotate()
{
	bool check = true;
	QSoundEffect *sound = nullptr;
	for (QHash<Name, QSoundEffect *>::ConstIterator it = sounds.begin(); it != sounds.end(); it++)
	{
		if (it.key() == Name::Rotate)
		{
			sound = it.value();
			if (sound->isPlaying())
			{
				check = false;
				break;
			}
		}
	}
	if (check && sound != nullptr)
	{
		sound->play();
	}
}

void SoundController::rowDeleted()
{
	for (QHash<Name, QSoundEffect *>::ConstIterator it = sounds.begin(); it != sounds.end(); it++)
	{
		if (it.key() == Name::RowDeleted)
		{
			qDebug() << 1;
			it.value()->play();
		}
		else
		{
			it.value()->stop();
		}
	}
}

void SoundController::defeat()
{
	for (QHash<Name, QSoundEffect *>::ConstIterator it = sounds.begin(); it != sounds.end(); it++)
	{
		if (it.key() == Name::Defeat)
		{
			it.value()->play();
		}
		else
		{
			it.value()->stop();
		}
	}
}

void SoundController::mute()
{
	foreach (QSoundEffect *sound, sounds)
	{
		sound->setMuted(true);
	}
}

void SoundController::unmute()
{
	foreach (QSoundEffect *sound, sounds)
	{
		sound->setMuted(false);
	}
}

void SoundController::makeMainMenu()
{
	QSoundEffect *sound = new QSoundEffect(this);
	sound->setSource(QUrl::fromLocalFile(":Sounds/MainMenu.wav"));
	sound->setVolume(0.25);
	sound->setLoopCount(QSoundEffect::Infinite);
	sounds.insert(Name::MainTheme, sound);
}

void SoundController::makePlayground()
{
	QSoundEffect *sound;
	sound = new QSoundEffect(this);
	sound->setSource(QUrl::fromLocalFile(":Sounds/MoveDown.wav"));
	sound->setVolume(0.4);
	sounds.insert(Name::Down, sound);
	sound = new QSoundEffect(this);
	sound->setSource(QUrl::fromLocalFile(":Sounds/MoveRight.wav"));
	sounds.insert(Name::Right, sound);
	sound = new QSoundEffect(this);
	sound->setSource(QUrl::fromLocalFile(":Sounds/MoveLeft.wav"));
	sounds.insert(Name::Left, sound);
	sound = new QSoundEffect(this);
	sound->setSource(QUrl::fromLocalFile(":Sounds/Rotate.wav"));
	sound->setVolume(0.5);
	sounds.insert(Name::Rotate, sound);
	sound = new QSoundEffect(this);
	sound->setSource(QUrl::fromLocalFile(":Sounds/RowDeleted.wav"));
	sound->setVolume(0.25);
	sounds.insert(Name::RowDeleted, sound);
	sound = new QSoundEffect(this);
	sound->setSource(QUrl::fromLocalFile(":Sounds/Defeat.wav"));
	sounds.insert(Name::Defeat, sound);
}
