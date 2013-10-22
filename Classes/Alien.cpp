#include "Alien.h"
#include "Resource.h"
#include "UtilFunc.h"
#include "MainGameScene.h"
#include "Particle.h"
#include "Sound.h"

const int AlienLayer::cAlienGenPosX[6] = {290, 320, 350, 380, 410, 440};
const float AlienLayer::cAlienMoveSpeed[6] = {0.4f, 1.6f, 2.8f, 4.0f, 5.2f, 6.4f};
const float AlienLayer::cAlienScaleArea[5] = { 0.05f, 0.15f, 0.3f, 0.5f, 2.0f };

bool AlienLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	posX = 0;
	currentScaleIdx = 0;

	// set layer properties
	setAnchorPoint(Point(0,0));
	setScale(cAlienScaleArea[currentScaleIdx++]);

	initWithPlist(p_chorogging, s_chorogging);

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
		//posX = UtilFunc::getRandomRangeValue(cAlienGenPosXMin, cAlienGenPosXMax);
		int randXIdx = (rand() % 6);
		posX = cAlienGenPosX[randXIdx];

		int yPos = UtilFunc::getRandomRangeValue(cAlienGenPosY-100, cAlienGenPosY);
		setPosition(Point(posX, yPos));

		// Get random actualDuration
		//float actualDuration = UtilFunc::getRandomRangeValue(0.4f, 6.4f);
		float actualDuration = cAlienMoveSpeed[randXIdx];

		// Action
		actionSequenceTopToBottom(this, actualDuration);
	}

	return true;
}

void AlienLayer::removeMyself()
{
	this->stopAllActions();

	// sound
	Sound::playAlienDownEffect();

	// hide sprite
	sprt_Alien->setVisible(false);

	if(4 > currentScaleIdx)
	{
		// particle effect
		ParticleSystem* _emitter = ParticleLayer::createWithParticlePlist(ALIEN_FRAME_FILE);
		_emitter->setPosition(0, 0);
		addChild(_emitter);
	}

	scheduleOnce(schedule_selector(AlienLayer::removeMyself), 1);
}

void AlienLayer::removeMyself(float dt)
{
	this->removeFromParentAndCleanup(true);
}

Rect AlienLayer::getAlienRect()
{
	float rectWidth = sprt_Alien->getContentSize().width * cAlienScaleArea[currentScaleIdx];
	float rectHeight = sprt_Alien->getContentSize().height * cAlienScaleArea[currentScaleIdx];
	
	return Rect( this->getPosition().x - rectWidth / 2, 
		         this->getPosition().y - rectHeight / 2,
				 rectWidth,
				 rectHeight );
}

void AlienLayer::onEnter()
{
    Layer::onEnter();
}

void AlienLayer::onExit()
{
    Layer::onExit();
}

void AlienLayer::actionSequenceTopToBottom(Layer* lyr, float actualDuration)
{
	auto moveToArea2 = MoveTo::create(actualDuration, Point(posX, cAlienArea1EndPosY));
	//EaseRateAction* moveToArea2Ease = UtilFunc::getRandomEaseAction(moveToArea2);
	auto moveToArea2Ease = EaseIn::create(moveToArea2, 1.2f);
	auto scaleAtArea2 = ScaleTo::create(0, cAlienScaleArea[1], cAlienScaleArea[1]);
	auto actionToArea2 = Sequence::create(moveToArea2Ease, scaleAtArea2, NULL);

	auto actionToAreaDone = CallFuncN::create( CC_CALLBACK_1(AlienLayer::moveToAreaFinished, this) );	// common

	// process between area 
	auto setToArea2 = MoveTo::create(0, Point(posX, cAlienArea2StartPosY));
	int posX2 = adjustActualPosX(posX);

	auto moveToArea3 = MoveTo::create(actualDuration, Point(posX2, cAlienArea2EndPosY));
	//EaseRateAction* moveToArea3Ease = UtilFunc::getRandomEaseAction(moveToArea3);
	auto moveToArea3Ease = EaseInOut::create(moveToArea3, 1.2f);
	auto scaleAtArea3 = ScaleTo::create(0, cAlienScaleArea[2], cAlienScaleArea[2]);
	auto actionToArea3 = Sequence::create(moveToArea3Ease, scaleAtArea3, NULL);

	auto setToArea3 = MoveTo::create(0, Point(posX2, cAlienArea3StartPosY));
	int posX3 = adjustActualPosX(posX2);

	auto moveToArea4 = MoveTo::create(actualDuration, Point(posX3, cAlienArea3EndPosY));
	//EaseRateAction* moveToArea4Ease = UtilFunc::getRandomEaseAction(moveToArea4);
	auto moveToArea4Ease = EaseOut::create(moveToArea4, 1.2f);
	auto scaleAtArea4 = ScaleTo::create(0, cAlienScaleArea[3], cAlienScaleArea[3]);
	auto actionToArea4 = Sequence::create( moveToArea4Ease, scaleAtArea4, NULL);

	auto moveToAttack = MoveTo::create(0, Point(360, 0));
	auto scaleToAttack = ScaleTo::create(0, cAlienScaleArea[4], cAlienScaleArea[4]);
	auto actionToAttack = Sequence::create(moveToAttack, scaleToAttack, NULL);

	auto actionDone = CallFuncN::create( CC_CALLBACK_1(AlienLayer::moveFinished, this) );

	lyr->runAction( CCSequence::create(actionToArea2, actionToAreaDone, setToArea2, actionToArea3, actionToAreaDone, setToArea3, actionToArea4, actionToAreaDone, actionToAttack, actionDone, NULL) );
}

void AlienLayer::moveToAreaFinished(Object* pSender)
{
	setZOrder(getZOrder() + 2);
	currentScaleIdx++;
}

void AlienLayer::moveFinished(Object* pSender)
{
	alienAttack();
	scheduleOnce( schedule_selector(AlienLayer::removeMyself), 1);
}

void AlienLayer::alienAttack()
{
	MainGameLayer* parent = (MainGameLayer*)getParent();
	parent->runDamagedEffect();
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