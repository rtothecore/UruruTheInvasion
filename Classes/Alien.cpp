#include "Alien.h"
#include "Resource.h"
#include "UtilFunc.h"

const float AlienLayer::cAlienScaleArea1 = 0.05f;
const float AlienLayer::cAlienScaleArea2 = 0.15f;
const float AlienLayer::cAlienScaleArea3 = 0.3f;
const float AlienLayer::cAlienScaleArea4 = 0.5f;

bool AlienLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	posX = 0;

	// set layer properties
	setAnchorPoint(Point(0,0));
	setScale(cAlienScaleArea1);

	initWithPlist(p_chorogging, s_chorogging);
	//initWithTexture(s_chorogging);

	//touch
	Director* director = Director::getInstance();
    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

    return true;
}

bool AlienLayer::initWithPlist(const char* plist, const char* frameName)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
	
	if(sprtfrm_Alien = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName))
	{
		sprt_Alien = Sprite::createWithSpriteFrame(sprtfrm_Alien);
		addChild(sprt_Alien, 1);

		// Alien's Animation
		Array* animFrames = Array::createWithCapacity(3);

		for(int i = 1; i < 4; i++) 
		{
			String* strAlien = String::createWithFormat("chorogging%d.png", i);
			SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName( strAlien->getCString() );
			animFrames->addObject(frame);
		}

		auto animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
		sprt_Alien->runAction( RepeatForever::create( Animate::create(animation) ) );

		// Get random x,y pos
		posX = UtilFunc::getRandomRangeValue(cAlienGenPosXMin, cAlienGenPosXMax);
		int yPos = UtilFunc::getRandomRangeValue(cAlienGenPosY-100, cAlienGenPosY);
		setPosition(Point(posX, yPos));

		// Get random actualDuration
		float actualDuration = UtilFunc::getRandomRangeValue(0.4f, 6.4f);

		// Action
		actionSequenceTopToBottom(this, actualDuration);

		//// Dolphin's Y
		//int actualY = UtilFunc::getRandomRangeValue(getContentSize().height, UtilFunc::getWinSize().height/1.4 - getContentSize().height);

		//// Set Dolphin to the screen right edge
		//setPosition(Point(UtilFunc::getWinSize().width + (getContentSize().width / 2), actualY));

		//// Velocity
		//int actualDuration = UtilFunc::getRandomRangeValue(2.0, 4.0);

		//// Action
		//int actionIndex = (rand() % 2);
		//actionIndex>0 ? MarineLifeLayer::actionSequence(this, actualY, actualDuration) : MarineLifeLayer::actionBezier(this, actualY);

		//// bye sprite
		//SpriteFrameCache::getInstance()->addSpriteFramesWithFile(p_Bye);
		//sprt_bye = Sprite::createWithSpriteFrame( SpriteFrameCache::getInstance()->getSpriteFrameByName(s_Bye) );
		//sprt_bye->setPosition( Point(0, frm_marineLife->getOriginalSize().height/2) );
		//sprt_bye->setVisible(false);
		//addChild(sprt_bye);

		//// Collision Check sprite
		///*Sprite* sprtTest = Sprite::create();
		//sprtTest->setTextureRect(getDolphinRect());
		//sprtTest->setColor(Color3B::WHITE);
		//addChild(sprtTest);*/
	}

	return true;
}

//void AlienLayer::initWithTexture(const char* texture)
//{
//	//Sprite* sprt = Sprite::create(texture);
//	sprtAlien = Sprite::create(texture);
//	setAnchorPoint(Point(0,0));
//	setScale(0.05f);
//
//	// get random x,y pos
//	posX = UtilFunc::getRandomRangeValue(cAlienGenPosXMin, cAlienGenPosXMax);
//	int yPos = UtilFunc::getRandomRangeValue(cAlienGenPosY-100, cAlienGenPosY);
//	setPosition(Point(posX, yPos));
//
//	this->addChild(sprtAlien, 1);
//
//	// get random actualDuration
//	float actualDuration = UtilFunc::getRandomRangeValue(0.4f, 6.4f);
//
//	actionSequenceTopToBottom(this, actualDuration);
//}

void AlienLayer::removeMyself(float dt) 
{
	this->removeFromParentAndCleanup(true);
}

Rect AlienLayer::getRect()
{
	//Size s = sprtAlien->getContentSize();
	Size s = sprtfrm_Alien->getOriginalSize();
	
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

void AlienLayer::onEnter()
{
    Layer::onEnter();
}

void AlienLayer::onExit()
{
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->removeDelegate(this);
    Layer::onExit();
}

bool AlienLayer::containsTouchLocation(Touch* touch)
{
    return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool AlienLayer::ccTouchBegan(Touch* touch, Event* event)
{
    if ( !containsTouchLocation(touch) )
	{
		return false;
	}
    
	CCLog("toched!");
	removeMyself(0);

    return true;
}

void AlienLayer::ccTouchMoved(Touch* touch, Event* event)
{
}

void AlienLayer::ccTouchEnded(Touch* touch, Event* event)
{    
}

void AlienLayer::actionSequenceTopToBottom(Layer* lyr, float actualDuration)
{
	auto moveToArea2 = MoveTo::create(actualDuration, Point(posX, cAlienArea2StartPosY));
	EaseRateAction* moveToArea2Ease = UtilFunc::getRandomEaseAction(moveToArea2);
	auto scaleAtArea2 = ScaleTo::create(actualDuration, cAlienScaleArea2, cAlienScaleArea2);
	auto actionToArea2 = CCSpawn::create(moveToArea2Ease, scaleAtArea2, NULL);

	// adjust actualX
	int posX2 = adjustActualPosX(posX);

	auto moveToArea3 = MoveTo::create(actualDuration, Point(posX2, cAlienArea3StartPosY));
	EaseRateAction* moveToArea3Ease = UtilFunc::getRandomEaseAction(moveToArea3);
	auto scaleAtArea3 = ScaleTo::create(actualDuration, cAlienScaleArea3, cAlienScaleArea3);
	auto actionToArea3 = CCSpawn::create(moveToArea3Ease, scaleAtArea3, NULL);

	int posX3 = adjustActualPosX(posX2);

	auto moveToArea4 = MoveTo::create(actualDuration, Point(posX3, cAlienArea4StartPosY));
	EaseRateAction* moveToArea4Ease = UtilFunc::getRandomEaseAction(moveToArea4);
	auto scaleAtArea4 = ScaleTo::create(actualDuration, cAlienScaleArea4, cAlienScaleArea4);
	auto actionToArea4 = CCSpawn::create( moveToArea4Ease, scaleAtArea4, NULL);

	lyr->runAction( CCSequence::create(actionToArea2, actionToArea3, actionToArea4, NULL) );
}

int AlienLayer::adjustActualPosX(int actualPosX)
{
	int winWidthCenter = UtilFunc::getWinSize().width / 2;
	int centerThreshold = 20;
	int adjustVal = UtilFunc::getRandomRangeValue(100, 200);

	if( (winWidthCenter-centerThreshold) < actualPosX && 
		(winWidthCenter+centerThreshold) > actualPosX )
	{
		return actualPosX;
	} 
	else 
	{
		if(winWidthCenter < posX)
		{
			actualPosX += adjustVal;
		} 
		else 
		{
			actualPosX -= adjustVal;
		}

		return actualPosX;
	}
}