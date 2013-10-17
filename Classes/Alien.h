#ifndef __ALIEN_H__
#define __ALIEN_H__

#include "cocos2d.h"

USING_NS_CC;

class AlienLayer : public Layer
{
public:
	CREATE_FUNC(AlienLayer);
    virtual bool init();

	void removeMyself(float dt);
	Rect getRect();
	bool containsTouchLocation(Touch* touch);

	int posX;	
	SpriteFrame* sprtfrm_Alien;
	Sprite* sprt_Alien;

	// touch event
    void onEnter();
    void onExit();
	bool ccTouchBegan(Touch* touch, Event* event);
    void ccTouchMoved(Touch* touch, Event* event);
    void ccTouchEnded(Touch* touch, Event* event);

	// alien scale
	static const float cAlienScaleArea1;
	static const float cAlienScaleArea2;
	static const float cAlienScaleArea3;
	static const float cAlienScaleArea4;

	// alien gen & move area
	static const int cAlienGenPosY = 1025;
	static const int cAlienGenPosXMin = 300;
	static const int cAlienGenPosXMax = 430;

	static const int cAlienArea2StartPosY = 920;
	static const int cAlienArea2PosXMin = 200;
	static const int cAlienArea2PosXMax = 530;

	static const int cAlienArea3StartPosY = 550;
	static const int cAlienArea3PosXMin = 0;
	static const int cAlienArea3PosXMax = 720;

	static const int cAlienArea4StartPosY = 100;
	static const int cAlienArea4PosXMin = 0;
	static const int cAlienArea4PosXMax = 720;

	//void initWithTexture(const char* texture);
	bool initWithPlist(const char* plist, const char* frameName);
	void actionSequenceTopToBottom(Layer* lyr, float actualDuration);

	int adjustActualPosX(int actualPosX);
};

#endif // __ALIEN_H__