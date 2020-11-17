#include "SoundController.h"

#include <QSoundEffect>

#include <QDebug>

SoundController::SoundController(Mode mode)
{
	if (mode == MainMenu)
	{
		QSoundEffect *sound = new QSoundEffect;
		sound->setSource(QUrl::fromLocalFile(":Sounds/MainMenu.wav"));
		sound->setVolume(0.25);
		sound->setLoopCount(QSoundEffect::Infinite);
		sounds.insert(Name::MainTheme, sound);
	}
	else
	{
		QSoundEffect *sound;
		sound = new QSoundEffect;
		sound->setSource(QUrl::fromLocalFile(":Sounds/MoveDown.wav"));
		sounds.insert(Name::Down, sound);
		sound = new QSoundEffect;
		sound->setSource(QUrl::fromLocalFile(":Sounds/MoveRight.wav"));
		sounds.insert(Name::Right, sound);
		sound = new QSoundEffect;
		sound->setSource(QUrl::fromLocalFile(":Sounds/MoveLeft.wav"));
		sounds.insert(Name::Left, sound);
		sound = new QSoundEffect;
		sound->setSource(QUrl::fromLocalFile(":Sounds/Rotate.wav"));
		sounds.insert(Name::Rotate, sound);
		sound = new QSoundEffect;
		sound->setSource(QUrl::fromLocalFile(":Sounds/RowDeleted.wav"));
		sounds.insert(Name::RowDeleted, sound);
		sound = new QSoundEffect;
		sound->setSource(QUrl::fromLocalFile(":Sounds/Defeat.wav"));
		sounds.insert(Name::Defeat, sound);
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
		else
		{
			it.value()->stop();
		}
	}
}

void SoundController::moveDown()
{
	for (QHash<Name, QSoundEffect *>::ConstIterator it = sounds.begin(); it != sounds.end(); it++)
	{
		if (it.key() == Name::Down)
		{
			it.value()->play();
		}
		else
		{
			it.value()->stop();
		}
	}
}

void SoundController::moveRight()
{
	for (QHash<Name, QSoundEffect *>::ConstIterator it = sounds.begin(); it != sounds.end(); it++)
	{
		if (it.key() == Name::Right)
		{
			it.value()->play();
		}
		else
		{
			it.value()->stop();
		}
	}
}

void SoundController::moveLeft()
{
	for (QHash<Name, QSoundEffect *>::ConstIterator it = sounds.begin(); it != sounds.end(); it++)
	{
		if (it.key() == Name::Left)
		{
			it.value()->play();
		}
		else
		{
			it.value()->stop();
		}
	}
}

void SoundController::rotate()
{
	for (QHash<Name, QSoundEffect *>::ConstIterator it = sounds.begin(); it != sounds.end(); it++)
	{
		if (it.key() == Name::Rotate)
		{
			it.value()->play();
		}
		else
		{
			it.value()->stop();
		}
	}
}

void SoundController::rowDeleted()
{
	for (QHash<Name, QSoundEffect *>::ConstIterator it = sounds.begin(); it != sounds.end(); it++)
	{
		if (it.key() == Name::RowDeleted)
		{
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
