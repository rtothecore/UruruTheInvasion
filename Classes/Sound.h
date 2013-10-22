#ifndef __SOUND_H__
#define __SOUND_H__

#include "cocos2d.h"

USING_NS_CC;

class Sound
{
private:
	static float pitchVal;
    static float panVal;
    static float gainVal;

	static bool bMusic;
	static bool bEffect;

public:
	Sound(void);
	~Sound(void);

	static bool isMusicOn();
	static bool isEffectOn();
	
	static void toggleMusic();
	static void toggleEffect();

	static void playBackgroundMusic(bool loop);
	static void stopBackgroundMusic();


	static void playStartAlertEffect();
	static void playAlienAttackEffect();
	static void playAlienDownEffect();
};

#endif