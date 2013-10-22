#ifndef __ALIEN_H__
#define __ALIEN_H__

#include "cocos2d.h"

USING_NS_CC;

class AlienLayer : public Layer
{
public:
	CREATE_FUNC(AlienLayer);
    virtual bool init();

	void removeMyself();
	void removeMyself(float dt);
	Rect getAlienRect();

	int posX;
	unsigned int currentScaleIdx;
	SpriteFrame* sprtfrm_Alien;
	Sprite* sprt_Alien;

    void onEnter();
    void onExit();

	// alien start position
	static const int cAlienGenPosX[6];

	static const float cAlienMoveSpeed[6];

	// alien scale
	static const float cAlienScaleArea[5];

	// alien gen & move area
	static const int cAlienGenPosY = 1025;
	static const int cAlienArea1EndPosY = 780;

	static const int cAlienArea2StartPosY = 880;
	static const int cAlienArea2PosXMin = 200;
	static const int cAlienArea2PosXMax = 530;
	static const int cAlienArea2EndPosY = 380;

	static const int cAlienArea3StartPosY = 550;
	static const int cAlienArea3PosXMin = 0;
	static const int cAlienArea3PosXMax = 720;
	static const int cAlienArea3EndPosY = 100;

	bool initWithPlist(const char* plist, const char* frameName);
	void actionSequenceTopToBottom(Layer* lyr, float actualDuration);

	void moveToAreaFinished(Object* pSender);
	void moveFinished(Object* pSender);
	int adjustActualPosX(int actualPosX);
	void alienAttack();
};

#endif // __ALIEN_H__