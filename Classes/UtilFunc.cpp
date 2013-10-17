#include "UtilFunc.h"


UtilFunc::UtilFunc(void)
{
}

UtilFunc::~UtilFunc(void)
{
}

float UtilFunc::getRandomRangeValue(float minVal, float maxVal)
{
	int rangeVal = maxVal - minVal;
	return (rand() % rangeVal) + minVal;	
}

Size UtilFunc::getWinSize()
{
	Size winSize = Director::getInstance()->getWinSize();
	return winSize;
}

Size UtilFunc::getVisibleSize()
{
	Size winSize = Director::getInstance()->getVisibleSize();
	return winSize;
}

EaseRateAction* UtilFunc::getRandomEaseAction(MoveTo* moveAction) 
{
	EaseRateAction* easeAction;

	int easeIndex = (rand() % 3);
	switch(easeIndex) {
		case 0:
			easeAction = EaseInOut::create(moveAction, 1.2);
			break;
		case 1:
			easeAction = EaseIn::create(moveAction, 1.2);
			break;
		case 2:
			easeAction = EaseOut::create(moveAction, 1.2);
			break;
		default:
			break;
	}

	return easeAction;
}