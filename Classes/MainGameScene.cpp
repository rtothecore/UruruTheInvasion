#include "MainGameScene.h"
#include "UtilFunc.h"
#include "Resource.h"
#include "Alien.h"
#include "Tags.h"
#include "Sound.h"

//------------------------------------------------------------------
//
// MainGameScene
//
//------------------------------------------------------------------
bool MainGameScene::init()
{
	MainGameLayer *mainGameLayer = MainGameLayer::create();
    addChild(mainGameLayer);

	return true;
}

//------------------------------------------------------------------
//
// EffectAction
//
//----------------------------------------------------------------

class Shaky3DDemo : public Shaky3D 
{
public:
    static ActionInterval* create(float t)
    {
        return Shaky3D::create(t, Size(15,10), 5, false);
    }
};

class LiquidDemo : public Liquid
{
public:
    static ActionInterval* create(float t)
    {
        return Liquid::create(t, Size(16,12), 4, 20);
    }
};

ActionInterval* createEffect(int nIndex, float t)
{
    Director::getInstance()->setDepthTest(false);

    switch(nIndex)
    {
        case 0: return Shaky3DDemo::create(t);
       /* case 1: return Waves3DDemo::create(t);
        case 2: return FlipX3DDemo::create(t);
        case 3: return FlipY3DDemo::create(t);
        case 4: return Lens3DDemo::create(t);
        case 5: return Ripple3DDemo::create(t);*/
        case 6: return LiquidDemo::create(t);
        /*case 7: return WavesDemo::create(t);
        case 8: return TwirlDemo::create(t);
        case 9: return ShakyTiles3DDemo::create(t);
        case 10: return ShatteredTiles3DDemo::create(t);
        case 11: return ShuffleTilesDemo::create(t);
        case 12: return FadeOutTRTilesDemo::create(t);
        case 13: return FadeOutBLTilesDemo::create(t);
        case 14: return FadeOutUpTilesDemo::create(t);
        case 15: return FadeOutDownTilesDemo::create(t);
        case 16: return TurnOffTilesDemo::create(t);
        case 17: return WavesTiles3DDemo::create(t);
        case 18: return JumpTiles3DDemo::create(t);
        case 19: return SplitRowsDemo::create(t);
        case 20: return SplitColsDemo::create(t);
        case 21: return PageTurn3DDemo::create(t);*/
    }

    return NULL;
}

ActionInterval* getAction()
{
    ActionInterval* pEffect = createEffect(0, 0.25f);

    return pEffect;
}

//------------------------------------------------------------------
//
// MainGameLayer
//
//------------------------------------------------------------------
bool MainGameLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	isRunningEffect = false;

	//touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

	addBackground();

    return true;
}

void MainGameLayer::onEnterTransitionDidFinish()
{
	addAliens(0);
	schedule( schedule_selector(MainGameLayer::addAliens), 0.1f );

	// play start sound
	Sound::playStartAlertEffect();
	Sound::playBackgroundMusic(true);
}

void MainGameLayer::addBackground()
{
	// Background TOP (z-index:0)
	Sprite* sprt = Sprite::create(s_BgT);
	sprt->setPosition(Point(UtilFunc::getWinSize().width / 2, UtilFunc::getWinSize().height / 2));
	this->addChild(sprt, 0, kTagBackground);

	// Background MIDDLE (z-index:2)
	sprt = Sprite::create(s_BgM);
	sprt->setPosition(Point(UtilFunc::getWinSize().width / 2, UtilFunc::getWinSize().height / 2));
	this->addChild(sprt, 2, kTagBackground);

	// Background BOTTOM (z-index:4)
	sprt = Sprite::create(s_BgB);
	sprt->setPosition(Point(UtilFunc::getWinSize().width / 2, UtilFunc::getWinSize().height / 2));
	this->addChild(sprt, 4, kTagBackground);
}

void MainGameLayer::addAliens(float dt)
{
	AlienLayer* alienL = AlienLayer::create();
	addChild(alienL, 1, kTagAlienLayer);	
}

void MainGameLayer::onEnter()
{
    Layer::onEnter();
}

void MainGameLayer::onExit()
{
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->removeDelegate(this);
    Layer::onExit();
}

bool MainGameLayer::checkTouchAlien(Rect touchRect)
{
	Object* pObj = NULL;
	Array *arrChildren = getChildren();
	AlienLayer* alienL;

	CCARRAY_FOREACH(arrChildren, pObj)
	{
		if( kTagAlienLayer == ((Node*)pObj)->getTag() )
		{
			alienL = static_cast<AlienLayer*>(pObj);

			if(!alienL)
				break;

			//// TEST
			//Rect alienRect = alienL->getAlienRect();
			//CCLog("alien pos(%f, %f)", alienL->getPositionX(), alienL->getPositionY());
			//CCLog("alienRect(%f, %f, %f, %f)", alienRect.origin.x, alienRect.origin.y, alienRect.size.width, alienRect.size.height);
			//// TEST

			if(alienL->getAlienRect().intersectsRect(touchRect))
			{
				alienL->removeMyself();
				//return true;
			}
		}
	}

	return false;
}

bool MainGameLayer::ccTouchBegan(Touch* touch, Event* event)
{
	Rect touchRect = UtilFunc::getTouchRect(touch->getLocation(), 40);

	///////////////////// sprite for touch check test
	//Sprite* sprtTest = Sprite::create();
	//sprtTest->setPosition(touch->getLocation());

	//CCLog("touchRect pos(%f, %f)", touch->getLocation().x, touch->getLocation().y);
	//CCLog("touchRect(%f, %f, %f, %f)", touchRect.origin.x, touchRect.origin.y, touchRect.size.width, touchRect.size.height);

	//sprtTest->setTextureRect(touchRect);
	//sprtTest->setColor(Color3B::WHITE);
	//addChild(sprtTest, 2);
	////////////////////

	if( !checkTouchAlien(touchRect) )
	{
		return false;
	}
    
	CCLog("toched!");

    return true;
}

void MainGameLayer::ccTouchMoved(Touch* touch, Event* event)
{
}

void MainGameLayer::ccTouchEnded(Touch* touch, Event* event)
{    
}

void MainGameLayer::runDamagedEffect()
{
	if(!isRunningEffect)
	{
		isRunningEffect = true;

		ActionInterval* effect = getAction();
		auto repEffect = Repeat::create(effect, 1);
		auto backToDefault = CallFuncN::create( CC_CALLBACK_1(MainGameLayer::backToDefaultGrid, this) );

		runAction(Sequence::create(repEffect, backToDefault, NULL));

		// sound
		Sound::playAlienAttackEffect();
	}
}

void MainGameLayer::backToDefaultGrid(Object* pSender)
{
	setGrid(NULL);
	isRunningEffect = false;
}

