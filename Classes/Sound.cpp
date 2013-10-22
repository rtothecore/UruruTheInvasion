#include "Sound.h"
#include "Resource.h"
#include "SimpleAudioEngine.h"
#include "UruruTIConfig.h"

using namespace CocosDenshion;

float Sound::pitchVal = 1;
float Sound::panVal = 0;
float Sound::gainVal = 1;

bool Sound::bMusic = true;
bool Sound::bEffect = true;

Sound::Sound(void)
{
#if (BACKGROUND_MUSIC)
	if(bMusic)
	{
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic( BGM_FILE );
		//SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
	}
#endif

#if (EFFECT_SOUND)
	if(bEffect)
	{
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic( START_ALERT_FILE );
		SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_ALIEN_ATTACK_FILE );
		SimpleAudioEngine::getInstance()->preloadEffect( EFFECT_ALIEN_DOWN_FILE );
		//SimpleAudioEngine::getInstance()->setEffectsVolume(0.5);
	}
#endif
}

Sound::~Sound(void)
{
	SimpleAudioEngine::end();
}

bool Sound::isMusicOn()
{
	return bMusic;
}

bool Sound::isEffectOn()
{
	return bEffect;
}

void Sound::toggleMusic()
{
	bMusic = !bMusic;

	if(!bMusic)
	{
		Sound::stopBackgroundMusic();
	} else {
		Sound::playBackgroundMusic(true);
	}
}

void Sound::toggleEffect()
{
	bEffect = !bEffect;
}

void Sound::playBackgroundMusic(bool loop)
{
#if (BACKGROUND_MUSIC)
	if(bMusic)
	{
		if(SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		}
		SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM_FILE, loop);
	}
#endif
}

void Sound::stopBackgroundMusic()
{
#if (BACKGROUND_MUSIC)
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
#endif
}

void Sound::playStartAlertEffect()
{
#if (EFFECT_SOUND)
	if(bEffect)
	{
		SimpleAudioEngine::getInstance()->playEffect(START_ALERT_FILE, false, pitchVal, panVal, gainVal);
	}
#endif
}

void Sound::playAlienAttackEffect()
{
#if (EFFECT_SOUND)
	if(bEffect)
	{
		SimpleAudioEngine::getInstance()->playEffect(EFFECT_ALIEN_ATTACK_FILE, false, pitchVal, panVal, gainVal);
	}
#endif
}

void Sound::playAlienDownEffect()
{
#if (EFFECT_SOUND)
	if(bEffect)
	{
		SimpleAudioEngine::getInstance()->playEffect(EFFECT_ALIEN_DOWN_FILE, false, pitchVal, panVal, gainVal);
	}
#endif
}
