#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class MainGameScene : public Scene
{
public:
	CREATE_FUNC(MainGameScene);
	virtual bool init();
};

class MainGameLayer : public Layer
{
public:
    virtual bool init();      
    CREATE_FUNC(MainGameLayer);
	void onEnterTransitionDidFinish();

	void addBackground();
	void addAliens(float dt);

	// touch event
    void onEnter();
    void onExit();
	bool ccTouchBegan(Touch* touch, Event* event);
    void ccTouchMoved(Touch* touch, Event* event);
    void ccTouchEnded(Touch* touch, Event* event);
	bool checkTouchAlien(Rect touchRect);

	// effect
	bool isRunningEffect;
	void runDamagedEffect();
	void backToDefaultGrid(Object* pSender);
};

#endif // __MAINGAME_SCENE_H__
