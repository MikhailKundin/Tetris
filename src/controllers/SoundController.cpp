#include "SoundController.h"

#include <QSoundEffect>

#include <QDebug>

SoundController::SoundController(Mode mode)
{
	
}

SoundController::~SoundController()
{
	emit stopMainThemeSignal();
	for (QHash<Name, QSoundEffect *>::ConstIterator it = m_sounds.begin(); it != m_sounds.end(); it++)
	{
		it.value()->stop();
	}
}

void SoundController::setSounds(const QHash<SoundController::Name, QSoundEffect *> &sounds)
{
	m_sounds = sounds;
}

void SoundController::playMainTheme()
{
	QSoundEffect *mainTheme = new QSoundEffect;
	mainTheme->setSource(QUrl::fromLocalFile(":Sounds/MainMenu.wav"));
	mainTheme->setLoopCount(QSoundEffect::Infinite);
	mainTheme->setVolume(0.25);
	mainTheme->play();
	
	connect(this, &SoundController::stopMainThemeSignal, mainTheme, [=]()
	{
		mainTheme->setSource(QUrl::fromLocalFile(":Sounds/null"));
		mainTheme->deleteLater();
	});
}

void SoundController::stopMainTheme()
{
	emit stopMainThemeSignal();
}

void SoundController::moveDown()
{
	for (QHash<Name, QSoundEffect *>::ConstIterator it = m_sounds.begin(); it != m_sounds.end(); it++)
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
	for (QHash<Name, QSoundEffect *>::ConstIterator it = m_sounds.begin(); it != m_sounds.end(); it++)
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
	for (QHash<Name, QSoundEffect *>::ConstIterator it = m_sounds.begin(); it != m_sounds.end(); it++)
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
	for (QHash<Name, QSoundEffect *>::ConstIterator it = m_sounds.begin(); it != m_sounds.end(); it++)
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
	for (QHash<Name, QSoundEffect *>::ConstIterator it = m_sounds.begin(); it != m_sounds.end(); it++)
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
	for (QHash<Name, QSoundEffect *>::ConstIterator it = m_sounds.begin(); it != m_sounds.end(); it++)
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
